#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define MAXLINE 256

int fd5, fd6,fd7, n, nn;
char inmsg[MAXLINE];

void *TaskCode(void *argument)
{
	while(1)
	{
		n=read(fd5,inmsg,MAXLINE);
		printf("[Client1] -> %s\n",inmsg);
	}
		
}

void *TaskCode2(void *argument)
{
	while(1)
	{
		printf("[Client3] : ");
		fgets(inmsg,MAXLINE,stdin);
		write(fd6,inmsg,strlen(inmsg)+1);
	}
}

void *TaskCode3(void *argument)
{
	while(1)
	{
		nn=read(fd7,inmsg,MAXLINE);
		printf("[Client2]-> %s\n",inmsg);
	}
}

int main(){
	int i;
	pthread_t tid, tid2, tid3;
	fd5=open("./chatfifo5",O_RDONLY);
	fd6=open("./chatfifo6",O_WRONLY);
	fd7=open("./chatfifo7",O_RDONLY);
	if(fd5==-1||fd6==-1||fd7==-1){
		perror("open");
		exit(1);
	}

	printf("*Client3 starts\n");

	pthread_create(&tid,NULL,TaskCode,NULL);
	pthread_create(&tid2,NULL,TaskCode2,NULL);
	pthread_create(&tid3,NULL,TaskCode3,NULL);

	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	return 0;
	
}
