#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
if(argc < 5 && argc > 5){
printf("Error de argumentos\n");
return -1;
}
// crear tuberia sin nombre
int fd[2]; //extremo de escritura fd[1], extremo de lectura fd[0]
if(pipe(fd) == -1){
printf("Error: %s\n", strerror(errno));
return -1;
}
// crear hijo
pid_t child = fork();

switch(child){
case -1:
perror("fork\n");
exit(1);
case 0:
printf("Proceso hijo...\n");
//Procesamiento descriptor de lectura
dup2(fd[0], 0);
//cierre de los descriptores de lectura y escritura
close(fd[1]);
close(fd[0]);
// ejecurar comando2 argumento2
execlp(argv[3], argv[3], argv[4], NULL);
  break;
default:
printf("Proceso padre...\n");
//Procesamiento descriptor de escritura
dup2(fd[1], 1);
//cierre de los descriptores de lectura y escritura
close(fd[1]);
close(fd[0]);
// ejecurar comando1 argumento1
execlp(argv[1], argv[1], argv[2]);
  break;
}
return 0;
} 
