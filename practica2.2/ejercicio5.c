#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int main(){
int errno;
int file = open("prueba",O_CREAT, 0645);
if(file == -1){
printf("Error: %s\n", strerror(errno));
}
close(file);
return 0;
}

