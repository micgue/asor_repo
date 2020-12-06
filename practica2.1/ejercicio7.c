
#include <stdio.h>
#include <unistd.h>

int main(){
char* path = "/";
printf("Numero maximo de enlaces: %li.\n", pathconf(path, _PC_LINK_MAX));
printf("Tamaño maximo de una ruta: %li.\n", pathconf(path, _PC_PATH_MAX));
printf("Tamaño maximo de un nombre de fichero: %li.\n", pathconf(path, _PC_NAME_MAX));
return 1;
}
