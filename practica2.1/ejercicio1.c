#include<stdio.h>
#include<errno.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	//int errno;
	if(setuid(0) == -1){
	perror("Error");
	}
	return 1;
}
