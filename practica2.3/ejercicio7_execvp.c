#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <unistd.h>
int main(int argc, char **argv){
if(argc < 2){
printf("Error de argumentos\n");
return -1;
}
if(execvp(argv[1],argv+1)== -1){
printf("Error execvp\n");
return -1;
}
printf("El comando termino de ejecutarse\n");
return 0;
}

