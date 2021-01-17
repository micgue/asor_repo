#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
const int MSG_MAX_LENGTH = 100;
int main(){
char flag;
// crear tuberia bidireccional
int p_h[2]; //extremo de escritura fd[1], extremo de lectura fd[0]
int h_p[2];
if(pipe(p_h) == -1){
printf("Error: %s\n", strerror(errno));
return -1;
}
if(pipe(h_p) == -1){
printf("Error: %s\n", strerror(errno));
return -1;
}
// crear proceso
pid_t pid = fork();

switch(pid){
case -1:
perror("fork\n");
exit(1);
case 0:
printf("Proceso hijo...\n");
//Cerrar descriptores de lectura y escritura en una dirección
close(p_h[1]); 
close(h_p[0]);
//El hijo leerá de la tubería p_h
char* pMensaje = malloc(MSG_MAX_LENGTH*sizeof(char));
size_t i;
for(i = 0; i < 10; i++){
size_t length = read(p_h[0], pMensaje, MSG_MAX_LENGTH);
pMensaje[length] = '\0';
printf("Mensaje [HIJO]: %s\n", pMensaje);
sleep(1);
//Después de 10 mensajes enviará el carácter ‘q’ para indicar al padre que finalice
if(i == 9){
flag = 'q';
}
//escribirá el mensaje por la salida estándar
write(h_p[1], &flag, 1);
}
free(pMensaje);
 break;
 default:
printf("Proceso padre...\n");
//cierre de los descriptores de lectura y escritura en una direccion
close(h_p[1]);
close(p_h[0]);
char* hMensaje = malloc(MSG_MAX_LENGTH*sizeof(char));
while(flag!= 'q'){
printf("Mensaje [PADRE]: ");
size_t length = read(0, hMensaje, MSG_MAX_LENGTH);
hMensaje[length] = '\0';
write(p_h[1], hMensaje, MSG_MAX_LENGTH);
read(h_p[0], &flag, 1);
}
free(hMensaje);
break;
 }
  close(h_p[0]);
    close(h_p[1]);
    close(p_h[0]);
    close(p_h[1]);
return 0;
}

