#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
int main(){
struct passwd *pwd;
uid_t uid = getuid();
printf("UID real: %d.\n", uid);
printf("UID efectivo: %d.\n", geteuid());
pwd = getpwuid(uid);
printf("Nombre de usuario: %s.\n", pwd->pw_name);
printf("Directorio home: %s.\n", pwd->pw_dir);
printf("Descripcion del usuario: %s.\n", pwd->pw_gecos);
return 1;
}

