#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
int main(){
struct timeval tv1, tv2;
gettimeofday(&tv1, NULL);
int i;
for( i = 0; i< 1000000; i++);
gettimeofday(&tv2,NULL);
printf("Microsegundos: %ld.\n",( tv2.tv_usec- tv1.tv_usec));


return 1;
}

