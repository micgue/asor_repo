#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int main(int argc, char ** argv) {
int errno;
if (argc < 2) {
     printf("Error de argumentos\n");
 return -1;
  }
    int file = open(argv[1], O_CREAT | O_RDWR, 0777);
    if (file == -1) {
        printf("Error: %s\n", strerror(errno));
    }
struct flock lock;
  lock.l_type = F_UNLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_pid = getpid();

int status = fcntl(file, F_GETLK, &lock);


// Comprobar que el cerrojo esta desbloqueado
 if (lock.l_type == F_UNLCK) {
//fijat el cerrojo 
    printf("STATUS: Cerrojo desbloqueado.\n");
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

if (fcntl(file, F_GETLK, &lock) == -1) {
printf("Error al crear el cerrojo\n");
close(file);
return -1;
}else
{printf("Cerrojo creado\n");

//Datos del cerrojo:
time_t t = time(NULL);
struct tm *tm = localtime(&t);
char buf[1024];
sprintf (buf, "Hora: %d:%d\n", tm->tm_hour, tm->tm_min);
write(file, &buf, strlen(buf));
// esperar 30 seg para liberar el cerrojo
      sleep(30);
//Valores del cerrojo para cerrarlo:
lock.l_type = F_WRLCK;
lock.l_whence = SEEK_SET;
lock.l_start = 0;
lock.l_len = 0;
lock.l_pid = getpid();

//compribar los valores del cerrojo de cierre      
if (fcntl(file, F_GETLK, &lock) == -1) {
printf("Error al crear cerrojo de cierre\n");
close(file);
return 1;
} else
//cerrar fichero
close(file);
}

} else {
    printf("Cerrojo bloqueado.\n");
    close(file);
    return 1;
  }
close(file);

return 0;
}

