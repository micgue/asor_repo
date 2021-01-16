#include<stdio.h>
#include<errno.h>

#include<string.h>
#include<sys/types.h>
#include <unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<stdlib.h>

void aux(){
pid_t pid= getpid();
printf("Identificador de proceso: %i\n", pid);
pid_t ppid = getppid();
printf("Identificador de proceso padre: %i\n", ppid);
pid_t pgid = getpgid(pid);
printf("Identificador de grupo de procesos: %i\n", pgid);
pid_t psid = getsid(pid);
printf("Identificador de la sesion: %i\n", psid);
struct rlimit rlim;
int err = getrlimit(RLIMIT_FSIZE, &rlim);
if(err == -1){
printf("Error\n");
}
printf("Numero maximo de ficheros que puede abrir el proceso: %i\n", rlim.rlim_max);
size_t size = 1000;
char *buffer = malloc(sizeof(char) * size);
printf("Path: %s\n", getcwd(buffer, size));
free(buffer);
}


int main(){
pid_t pid = fork(); // creación del nuevo proceso 
switch (pid) {
case -1:
perror("Error fork\n");
exit(1);
case 0: /* ejecutando proceso hijo, se crea una nueva sesion, nueva ruta a /tmp*/
;pid_t child_sid = setsid(); 
if(chdir("/tmp") == -1){
printf("Error cambio directorio\n");
return -1;
}
printf("Proceso hijo....\n");
aux();
//sleep(10);
 break;

default:
printf("Proceso padre...\n");
aux();
  break;
}
return 0;
}

