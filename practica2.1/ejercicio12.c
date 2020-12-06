#include <stdio.h>
#include <time.h>

int main(){
time_t t = time(NULL); 
printf("Tiempo en segundos desde el Epoch: %ld.\n",t);
return 1;
}
