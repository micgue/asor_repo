#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
const int PATH_MAX_LENGTH = 100;
int main(int argc, char **argv){

if(argc < 2){
printf("Error de argumentos\n");
return -1;
}

char path[PATH_MAX_LENGTH];
getcwd(path, sizeof(path));

char *pipe_path = strcat(path, "/pipe");
//crear tuberia con nombre
mkfifo(pipe_path, 0777);
//Abrir descriptor escritura de la tuberia
int fd = open(pipe_path, O_WRONLY);
write(fd, argv[1], strlen(argv[1])); 
// cerrar tuberia
close(fd);
return 0;
}

