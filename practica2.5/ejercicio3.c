#include <stdio.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv){
if(argc < 4){
printf("Error de argumentos\n");
return -1;
}
//char buf[3];
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
freeaddrinfo(res);

char hbuf[NI_MAXHOST];
char sbuf[NI_MAXSERV];
struct sockaddr_storage cliente_addr;
socklen_t addrlen = sizeof(cliente_addr);

sendto(sd, argv[3], 2, 0, res->ai_addr, res->ai_addrlen);
time_t t = time(NULL); //Hora del sistema;
struct tm *stm = localtime(&t); //para mostar el dia 
char out[20];

if(*argv[3] == 't'){
size_t bytes = recvfrom(sd, out, 20, 0, (struct sockaddr *)&cliente_addr, &addrlen);
out[bytes] = '\0';
printf("%I:%M:%S %p", stm);
}
else if (*argv[3] == 'd'){
size_t bytes = recvfrom(sd, out, 20, 0, (struct sockaddr *)&cliente_addr, &addrlen);
out[bytes] = '\0';
printf("%Y-%m-%d", stm);
}
else{
printf("Comando no soportado %c\n", &argv[3]);
}

return 0;
}
