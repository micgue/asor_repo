
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
int MAX_ERRS = 255;
int i;
for(i = 0; i < MAX_ERRS; i++){

printf("Mensaje de error %i: %s\n", i, strerror(i));
}
return 1;
}
