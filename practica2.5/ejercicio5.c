#include <stdio.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char **argv){
if(argc < 2){
printf("Error de argumentos\n");
return -1;
}
char buf[2];
struct addrinfo hints; //estructura de filtrado
struct addrinfo *res;  //lista de direcciones de sockets

memset(&hints, 0, sizeof(struct addrinfo)); // espacio para hints
hints.ai_family = AF_UNSPEC; // para ambos protocolos ipv4 e ipv6
hints.ai_socktype= SOCK_DGRAM; // transporte UDP
hints.ai_protocol = 0; //Specifying hints as NULL
hints.ai_flags = AI_PASSIVE; // direcciones
//hints.ai_addr = NULL; //y ai_addrlen: Puntero a la dirección y tamaño en bytes
//hints.ai_canonname = NULL; //Nombre oficial del host
//hints.ai_next = NULL; // Puntero al siguiente resultado (lista enlazada)

int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
if (rc != 0){
printf("[Error] getaddrinfo: %s\n", gai_strerror(rc));
return -1;
}
//crear socket
int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
if(sd == -1){
("[Error] socket\n");
return -1;
}
//enlazar el socket 
if(bind(sd,res->ai_addr, res->ai_addrlen)== -1){
("[Error] bind\n");
return -1;
}
freeaddrinfo(res);

//Datos:
char hbuf[NI_MAXHOST];
char sbuf[NI_MAXSERV];
struct sockaddr_storage cliente_addr;
socklen_t addrlen = sizeof(cliente_addr);

int i;
// procesos:
for(i = 0; i < 2; i++){
pid_t pid = fork(); //creamos el proceso 
int status;
switch(pid){
case -1:
perror("fork");
return -1; break;
case 0: // proceso hijo
while(1){
size_t bytes = recvfrom(sd, buf, 2, 0, (struct sockaddr *)&cliente_addr, &addrlen);
buf[1] = '\0';
getnameinfo((struct sockaddr *)&cliente_addr, addrlen, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("%i bytes de %s:%s\n", bytes, hbuf, sbuf);

time_t t = time(NULL); //Hora del sistema;
struct tm *stm = localtime(&t); //para mostar el dia 
ssize_t len = 20;
char out[len];
switch(buf[0]){
case 't': 
len = strftime(out, len, "%I:%M:%S %p", stm);
out[len] = '\0';
sendto(sd, out, len, 0, (struct sockaddr *)&cliente_addr, addrlen);
break;
case 'd':
len = strftime(out, len, "%Y-%m-%d", stm);
out[len] = '\0';
sendto(sd, out, len, 0, (struct sockaddr *)&cliente_addr, addrlen);
break;
case 'q':
printf("Saliendo...\n");
return -1;
break;
default:
printf("Comando no soportado %c\n", buf[0]);
break;
}
}
break;
default: //proceso padre
// esperar a que termine
wait(&status);
break;
}
}
return 0;
}
