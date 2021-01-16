#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc, char **argv){
if(argc < 2){
printf("Error de argumentos\n");
return -1;
}
if(system(argv[1])== -1){
printf("Error system\n");
return -1;
}
printf("El comando termino de ejecutarse\n");
return 0;
}
