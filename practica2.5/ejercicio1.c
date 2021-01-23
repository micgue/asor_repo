#include <stdio.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
int main(int argc, char **argv){
if(argc < 2){
printf("Error de argumentos\n");
return -1;
}
struct addrinfo hints; //estructura de filtrado
struct addrinfo *res;  //lista de direcciones de sockets

memset(&hints, 0, sizeof(struct addrinfo)); // espacio para hints
hints.ai_family = AF_UNSPEC; // para ambos protocolos ipv4 e ipv6
hints.ai_socktype= 0; hints.ai_protocol = 0; //Specifying hints as NULL
hints.ai_flags = AI_PASSIVE; // direcciones
hints.ai_addr = NULL; //y ai_addrlen: Puntero a la dirección y tamaño en bytes
hints.ai_canonname = NULL; //Nombre oficial del host
hints.ai_next = NULL; // Puntero al siguiente resultado (lista enlazada)

int rc = getaddrinfo(argv[1], NULL, &hints, &res);
if (rc != 0){
printf("Error de getaddrinfo: %s\n", gai_strerror(rc));
return -1;
}
//imprimir la lista de direcciones de sockets
struct addrinfo *i = res;
for(i; i != NULL; i = i->ai_next){
char hbuf[NI_MAXHOST];
//Las familias 2 y 10 son AF_INET y AF_INET6
getnameinfo(i->ai_addr, i->ai_addrlen, hbuf, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
printf("%s %i	%i\n",hbuf, i->ai_family, i->ai_socktype); 
//if(i->ai_family == AF_INET){
}
freeaddrinfo(res);
return 0;
}
