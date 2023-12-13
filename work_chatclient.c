#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define MAXLINE 256

int fd1, fd2,fd8, n,nn;
char inmsg[MAXLINE];

void *TaskCode(void *argument)
{
	while(1)
	{

		n=read(fd1,inmsg,MAXLINE);
		printf("[Client2] -> %s\n",inmsg);
	}
		
}

void *TaskCode2(void *argument)
{
	while(1)
	{
		printf("[Client1] : ");
		fgets(inmsg,MAXLINE,stdin);
		write(fd2,inmsg,strlen(inmsg)+1);
	}
}

void *TaskCode3(void *argument)
{
	while(1)
	{
		nn=read(fd8,inmsg,MAXLINE);
		printf("[Client3] -> %s\n",inmsg);
	}
}
int main(){
	int i;
	pthread_t tid, tid2,tid3;
	fd1=open("./chatfifo1",O_RDONLY);
	fd2=open("./chatfifo2",O_WRONLY);
	fd8=open("./chatfifo8",O_RDONLY);

	if(fd1==-1||fd2==-1||fd8==-1){
		perror("open");
		exit(1);
	}
	
	printf("*Client starts\n");

	pthread_create(&tid,NULL,TaskCode,NULL);
	pthread_create(&tid2,NULL,TaskCode2,NULL);
	pthread_create(&tid3,NULL,TaskCode3,NULL);

	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	return 0;
	
}


