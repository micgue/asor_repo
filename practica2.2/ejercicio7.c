#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int main(){
int errno;
/*parte de ejercicio 7*/
mode_t nuevo = umask(027);
int file = open("prueba7",O_CREAT, 0645);
if(file == -1){
printf("Error: %s\n", strerror(errno));
}
close(file);
/*parte ejercicio7*/
printf("Valor Umask: %i\n", umask(nuevo));
return 0;
}

