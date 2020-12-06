#include <stdio.h>
#include <time.h>

int main(){
const time_t t = time(NULL); 
struct tm *tmInfo= localtime(&t);
printf("Anio: %i.\n", (1900 + tmInfo->tm_year));
return 1;
}

