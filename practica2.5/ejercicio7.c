#include <stdio.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/*----------------------------------
 *  * TRATAR LA CONEXION
 *   * ---------------------------------*/
void haz_conexion(int cliente_sd){
while(1){
char bufIn[256];
char bufOut[256];
size_t bytes;
 
    bytes = read(0,bufOut, 255);
    bufOut[bytes] = '\0';
    send(cliente_sd,bufOut, bytes, 0);


    if (bufOut[1] == 'q') {
      printf("Conexión terminada\n");
      break;
    }

    bytes = recv(cliente_sd, bufIn, 255, 0);
    bufIn[bytes] = '\0';
    printf("%s\n", bufIn);
}
}

int main(int argc, char **argv){
if(argc < 3){
printf("Error de argumentos\n");
return -1;
}

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
//enlazar socket
if(connect(sd,res->ai_addr, res->ai_addrlen)== -1){
("[Error] bind\n");
return -1;
}
//conectar socket
if(connect(sd,res->ai_addr, res->ai_addrlen)== -1){
("[Error] connect\n");
return -1;
}

freeaddrinfo(res);
/*----------------------------
 * ---------------------------*/
/* ---------------------------------------
 * PARTE ESPECIFICA PARA TCP: Gestion para la conexion
 * ---------------------------------------
 *  */
char hbuf[NI_MAXHOST];
char sbuf[NI_MAXSERV];
struct sockaddr_storage cliente_addr;
socklen_t addrlen = sizeof(cliente_addr);
listen(sd, 1); //solo quiero escuchar a 1 cliente

int cliente_sd = accept(sd, (struct sockaddr *)&cliente_addr, &addrlen);
if(cliente_sd  == -1){
 printf("[ERROR] accept\n"); return -1;
}
getnameinfo((struct sockaddr *)&cliente_addr, addrlen, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("Conexion desde %s %s\n", hbuf, sbuf);

haz_conexion(sd);
close(cliente_sd);
return 0;
}
