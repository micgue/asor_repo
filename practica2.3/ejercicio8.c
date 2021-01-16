#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
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
printf("Proceso hijo. PID = %i, PPID = %i, PGID = %i\n", pid, getppid(), getpgid(pid));
int fd_out = open("/tmp/daemon.out",O_WRONLY|O_CREAT|O_TRUNC,0666);
int fd_outerr = open("/tmp/daemon.err",O_WRONLY|O_CREAT|O_TRUNC,0666);
int fd_in = open("/dev/null",O_WRONLY|O_CREAT|O_TRUNC,0666);

//redirigir los flujos estándar asociados al terminal
int fd1 = dup2(fd_out, 2);
int fd2 = dup2(fd_outerr, 1);
int fd3 = dup2(fd_in, 0); 

if(execvp(argv[1],argv+1)== -1){
printf("Error execvp\n");
return -1;
}
printf("El comando termino de ejecutarse\n");

//sleep(10);
 break;

 default:
 printf("Proceso padre. PID = %i, PPID = %i, PGID = %i\n", pid, getppid(), getpgid(pid));

// aux();
   break;
  }
 
  return 0;
   }
  
