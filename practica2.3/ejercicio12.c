#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
int sigint_count = 0;
int sigtstp_count = 0;

void handler(int signal){
if(signal == SIGINT) sigint_count++;
if(signal == SIGTSTP) sigtstp_count++;
}

int main(){

struct sigaction act;
//Obtener y establecer la acción asociada a una señal:
sigaction(SIGINT,NULL, &act);//obtener
act.sa_handler = handler;
sigaction(SIGINT, &act,NULL); //establecer

sigaction(SIGTSTP,NULL, &act);//obtener
act.sa_handler = handler;
sigaction(SIGTSTP, &act,NULL); //establecer

sigset_t sigset;

//bucle
while(sigint_count < 10 && sigtstp_count < 10){
sigsuspend(&sigset);
}
printf("\nSeñales SIGINT = %i.\nSeñales SIGTSTP = %i.\n", sigint_count, sigtstp_count);

return 0;
}
