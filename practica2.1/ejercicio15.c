#include <stdio.h>
#include <time.h>

int main(){
const time_t t = time(NULL);
struct tm *tmInfo= localtime(&t);
//printf("%s, Anio: %i.\n", (1900 + tmInfo->tm_year));
char buf[100];
strftime(buf, 100, "%A,%d de %B, %H:%M", tmInfo);

printf("%s del anio %i.\n",buf, (1900 + tmInfo->tm_year));
return 1;
}

