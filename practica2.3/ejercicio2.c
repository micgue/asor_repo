#include<stdio.h>
#include<sched.h>
#include<errno.h>
int main(){
pid_t pid = 0; //pid es un PID (un valor 0 se refiere al proceso actual)
int sched = sched_getscheduler(pid);
if(sched == -1){
printf("Error\n");
return -1;
}
printf("Scheduler: ");
switch(sched){
case SCHED_OTHER: printf("Other\n");break;
//case SCHED_BATCH: printf("Batch\n");break;
////case SCHED_IDLE: printf("Idl\n");break;
case SCHED_FIFO: printf("Fifo\n");break;
case SCHED_RR: printf("Round-robin\n");break;
default: printf("Error\n");break;
}
struct sched_param p;
pid = sched_getparam(pid, &p);
if(pid == -1){
printf("Error\n");
return -1;
}
printf("Prio: %i\n", p.sched_priority);
printf("Range of priority: %i - %i \n", sched_get_priority_max(sched), sched_get_priority_min(sched));

return 0;
}



