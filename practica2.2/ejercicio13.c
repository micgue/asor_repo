#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main (int argc, char** argv){
int errno;
if(argc < 2){
printf("Error de argumentos \n");
return -1;}
int file = open(argv[1], O_CREAT | O_RDWR, 00777);
if(file== -1){
printf("Error: %s\n", strerror(errno));
}
int fd1 = dup2(file,1);
if(fd1== -1){
printf("Error: %s\n", strerror(errno));
}
int fd2 = dup2( fd1, file);
printf("Redirigiendo fichero\n");
dup2(fd2,fd1);
return 0;
}


