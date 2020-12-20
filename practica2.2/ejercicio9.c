#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <time.h>
int main() {
int errno;
struct stat sb;
int res = stat("prueba9.txt", &sb);
if(res == -1){
printf("Error: %s\n", strerror(errno));
}
//Se ha usado parte del ejemplo que hay en el manual
printf("Numero mayor:%lx; Numero minor: %lx\n", (long) major(sb.st_dev), (long) minor(sb.st_dev));
printf("Numero i-nodo:%ld\n", (long) sb.st_ino);
printf("Tipo de fichero: ");
 switch (sb.st_mode & S_IFMT) {
 case S_IFBLK:  printf("block device\n");            break;
 case S_IFCHR:  printf("character device\n");        break;
 case S_IFDIR:  printf("directory\n");               break;
 case S_IFIFO:  printf("FIFO/pipe\n");               break;
 case S_IFLNK:  printf("symlink\n");                 break;
 case S_IFREG:  printf("regular file\n");            break;
 case S_IFSOCK: printf("socket\n");                  break;
 default:       printf("unknown?\n");                break;
}
time_t t = sb.st_mtime;
struct tm *ltm = localtime(&t);
printf("Ultimo acceso:  %d:%d\n", ltm->tm_hour,ltm->tm_min);
//st_ctime muestra el ultimo cambio de estad.  Se cambia
//escribiendo o estableciendo información de inodo (es decir, propietario, grupo
//recuento de enlaces, modo, etc)
return 0;
}

