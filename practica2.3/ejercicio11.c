#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(){
sigset_t sigset;
//conjuntos de señales:
sigemptyset(&sigset); // inicializa un conjunto como vacío, excluyendo todas las señales
sigaddset(&sigset, SIGINT); // añade SIGINT  al conjunto
sigaddset(&sigset, SIGTSTP); // añade SIGTSTP  al conjunto
// delimitamos el conjunto de señales
sigprocmask(SIG_BLOCK, &sigset, NULL);
//obtener la variable de entorno y detenerlo
int sleep_secs = atoi(getenv("SLEEP_SECS"));
printf("Proceso dormido durante %i segundos...\n", sleep_secs);
sleep(sleep_secs);
//Comprobar señales pendientes:
sigset_t sigsetpending;
sigpending(&sigsetpending);


if (sigismember(&sigsetpending, SIGINT)) {
printf("Se recibió una señal SIGINT\n");
sigdelset(&sigset, SIGINT);
}
if (sigismember(&sigsetpending, SIGTSTP)) {
printf("Se recibió una señal SIGTSTP\n");
sigdelset(&sigset, SIGTSTP);
}
sigprocmask(SIG_UNBLOCK, &sigset, NULL);


return 0;
}
