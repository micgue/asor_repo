#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
const int BUFF_SIZE = 256;
int main(){
char *pipe[BUFF_SIZE + 1];

//Crear dos tuberias:
mkfifo("pipe1", 0644);
mkfifo("pipe2", 0644);

//Abrir descriptor tuberia
int fd1 = open("pipe1", O_RDONLY | O_NONBLOCK);
int fd1 = open("pipe2", O_RDONLY | O_NONBLOCK);

//Falta el desarrollo del ejercicio.

//cerrar descriptores
close(fd1);
close(fd2);
return 0;
}
