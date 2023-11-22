#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void intHandler();
void intHandler2();

void intHandler(int signo){
	alarm(10);
	printf("10 sec reset\n");
}

void intHandler2(){
	printf("Fire!\n");
	exit(0);
}

int main(){
	int correct=0;
	alarm(10);
	signal(SIGINT,intHandler);
	signal(SIGALRM,intHandler2);
	
	while(!correct){
		if(getchar()=='1'){
			if(getchar()=='2'){
				if(getchar()=='3'){
					if(getchar()=='\n'){
						correct=1;
					}
				}
			}
		}
	}
	printf("correct\n");
}
