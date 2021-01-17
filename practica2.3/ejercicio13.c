#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include <ctype.h>
int borrar = 1;
void handler(int signal){
if(signal == SIGUSR1) borrar = 0;
}
int main(int argc, char **argv){
if(argc < 2 || isdigit(argv[1])!= 0){
printf("Error de argumentos\n");
return -1;
}
struct sigaction act;
sigset_t sigset;
// obtiene y establece la accion del proceso cuando decida el programador
sigaction(SIGUSR1,NULL, &act);//obtener
act.sa_handler = handler;
sigaction(SIGUSR1, &act,NULL); //establecer

int secs = atoi(argv[0]);
printf("Se eliminara el fichero en %i segundos...\n", secs);
sleep(secs);

if(borrar == 1){
unlink(argv[0]);
printf("El ejecutable se ha eliminado\n");
}
else{
printf("No se ha eliminado el ejecutable, se ha recibido una señal SIGUSR1\n");
}
return 0;
}

