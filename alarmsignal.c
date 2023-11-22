#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void intHandler(int signo){
	printf("wake up\n");
	exit(0);
}

int main(){
	alarm(5);
	signal(SIGALRM,intHandler);
	printf("loop...\n");
	while(1){
		sleep(1);
		printf("1 sec...\n");
	}
	printf("end of Main\n");
}
