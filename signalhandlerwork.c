#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int child_id;

void intHandler();
void intHandler2();
void intHandler3();

void intHandler(int signo)
{
	kill(child_id,SIGINT);
}

void intHandler2(int signo){
		printf("종료불가\n");
}

void intHandler3(int signo){
	kill(-getppid(),SIGKILL);
}

int main(){
	int pid;

	if((pid=fork())==0){ //child
		signal(SIGINT,intHandler2);

		for(int i=1;i<=20;i++){
			for(int j=1;j<=19;j++){
				printf("%d * %d = %d\n",i,j,i*j);
			}

			if(i==9)
				signal(SIGINT,intHandler3);

			sleep(1);
		}

		pause();
	}else{
		child_id=pid;
		signal(SIGINT,intHandler);
		wait();
	}
	
}

