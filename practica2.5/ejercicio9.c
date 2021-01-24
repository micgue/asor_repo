#include <stdio.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
/*----------------------------------
 *  * TRATAR LA CONEXION
 *   * ---------------------------------*/
void haz_conexion(int cliente_sd){
while(1){
char buf[80];
size_t bytes = recv(cliente_sd, buf, 79, 0);
if(bytes == 0){
printf("Fin de la conexion\n");
printf("[%i] Proceso hijo terminado\n", getpid());
close(cliente_sd); break;}
buf[bytes] = '\0';
send(cliente_sd, buf, bytes, 0);
}
}


int main(int argc, char **argv){
if(argc < 3){
printf("Error de argumentos\n");
return -1;
}
/*-------------------------------
 * MANEJADOR DE ZOMBIES
 * ------------------------------*/
struct sigaction sa;
sa.sa_handler = SIG_IGN;
sa.sa_flags = SA_RESTART;
sigaction(SIGCHLD, &sa, 0);
/*----------------------------
 * Inicialización del socket
 * --------------------------*/

struct addrinfo hints; //estructura de filtrado
struct addrinfo *res;  //lista de direcciones de sockets

memset(&hints, 0, sizeof(struct addrinfo)); // espacio para hints

hints.ai_family = AF_UNSPEC; // para ambos protocolos ipv4 e ipv6
hints.ai_socktype= SOCK_STREAM; // transporte TCP
hints.ai_protocol = 0; //Specifying hints as NULL
hints.ai_flags = AI_PASSIVE; // direcciones

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
/*----------------------------
 * ---------------------------*/
/* ---------------------------------------
 * PARTE ESPECIFICA PARA TCP: Gestion para la conexion
 * ---------------------------------------
 *  */
listen(sd, 16);

while(1){
char hbuf[NI_MAXHOST];
char sbuf[NI_MAXSERV];

struct sockaddr_storage cliente_addr;
socklen_t addrlen = sizeof(cliente_addr);
//descriptor del socket cliente para enviar o recibir datos de un unico cliente 
int cliente_sd = accept(sd, (struct sockaddr *)&cliente_addr, &addrlen);
if(cliente_sd  == -1){
 printf("[ERROR] accept\n"); return -1;
}
getnameinfo((struct sockaddr *)&cliente_addr, addrlen, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("Conexion desde %s %s\n", hbuf, sbuf);

//procesos:
pid_t pid = fork();

switch(pid){
case -1:
printf("[ERROR] fork\n");
 return -1;
case 0:
close(sd);
haz_conexion(cliente_sd);
return 0;
default:
close(cliente_sd);
break;
}
}
return 0;
}
