#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(){
int errno;
struct stat sb;
char* path = "prueba11";
if(stat(path, &sb) == -1){
printf("Error:%s\n", strerror(errno));
}
if( (sb.st_mode & S_IFMT)== S_IFREG){
char* hardPath = malloc(sizeof(char)*(strlen(path) + strlen(".hard")));
char* symPath = malloc(sizeof(char)*(strlen(path) + strlen(".sym")));
hardPath = strcat(strcpy(hardPath, path), ".hard");
symPath = strcat(strcpy(symPath, path), ".sym");
int res1 = link(path,hardPath);
int res2 = symlink(path, symPath);
if(res1==-1){
printf ("Error al crear enlace rigido: %s\n", strerror(errno));
}
else{
printf ("Creado enlace rigido\n");
}
if(res2==-1){
printf ("Error al crear enlace simbolico: %s\n", strerror(errno));
}
else{
printf ("Creado enlace simbolico\n");
}
}
return 0;
}
