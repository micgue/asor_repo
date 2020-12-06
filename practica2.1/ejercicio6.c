#include <stdio.h>
#include <unistd.h>

int main(){
printf("Longitud maxima de los argumentos: %li.\n", sysconf(_SC_ARG_MAX));
printf("Numero maximo de hijos: %li.\n", sysconf(_SC_CHILD_MAX));
printf("Numero maximo de ficheros: %li.\n", sysconf(_SC_OPEN_MAX));
return 1;
}
