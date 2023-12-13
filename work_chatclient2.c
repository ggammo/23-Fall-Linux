#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define MAXLINE 256

int fd3, fd4,fd9, n,nn;
char inmsg[MAXLINE];

void *TaskCode(void *argument)
{
	while(1)
	{
		n=read(fd3,inmsg,MAXLINE);
		printf("[Client1] -> %s\n",inmsg);
	}
		
}

void *TaskCode2(void *argument)
{
	while(1)
	{
		printf("[Client2] : ");
		fgets(inmsg,MAXLINE,stdin);
		write(fd4,inmsg,strlen(inmsg)+1);
	}
}

void *TaskCode3(void *argument)
{
	while(1)
	{
		nn=read(fd9,inmsg,MAXLINE);
		printf("[Client3] -> %s\n",inmsg);
	}
}

int main(){
	int i;
	pthread_t tid, tid2,tid3;
	fd3=open("./chatfifo3",O_RDONLY);
	fd4=open("./chatfifo4",O_WRONLY);
	fd9=open("./chatfifo9",O_RDONLY);

	if(fd3==-1||fd4==-1||fd9==-1){
		perror("open");
		exit(1);
	}

	printf("*Client2 starts\n");

	pthread_create(&tid,NULL,TaskCode,NULL);
	pthread_create(&tid2,NULL,TaskCode2,NULL);
	pthread_create(&tid3,NULL,TaskCode3,NULL);

	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	return 0;
	
}


