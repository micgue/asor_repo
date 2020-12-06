
#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>
#include <string.h>

int main(){
struct utsname info;
int errno;
if(uname(&info) == -1){
printf("Error: %s\n", strerror(errno));
}
printf("Nombre del SO: %s\n", info.sysname);
printf("Nombre del host: %s\n", info.nodename);
printf("Release del SO: %s\n", info.release);
printf("Version del SO: %s\n", info.version);
printf("Hardware: %s\n", info.machine);
//printf("Nombre del dominio: %s\n", info.domainname);

return 1;
}
