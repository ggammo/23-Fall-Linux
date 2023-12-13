#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define MAXLINE 256

int fd1, fd2, fd3, fd4, fd5, fd6, fd7, fd8,fd9, n, nn;
char msg[MAXLINE];

void *TaskCode(void *argument)
{	
	int *pipe=(int *)argument;
	while(1)
	{
		n=read(*pipe,msg,MAXLINE);
		if(*pipe==fd2){
			write(fd3,msg,strlen(msg)+1);
			write(fd5,msg,strlen(msg)+1);
		}
		if(*pipe==fd4){
			write(fd1,msg,strlen(msg)+1);
			write(fd7,msg,strlen(msg)+1);
		}
		if(*pipe==fd6){
			write(fd8,msg,strlen(msg)+1);
			write(fd9,msg,strlen(msg)+1);
		}
	}
}
int main(){
	pthread_t tid1,tid2, tid3;
	if(mkfifo("./chatfifo1",0660)==-1){
		perror("mkfifo");
		exit(1);
	}
	if(mkfifo("./chatfifo2",0666)==-1){
		perror("mkfifo");
		exit(2);
	}
	if(mkfifo("./chatfifo3",0660)==-1)
	{
		perror("mkfifio");
		exit(3);
	}
	if(mkfifo("./chatfifo4",0666)==-1){
		perror("mkfifo");
		exit(4);
	}
	if(mkfifo("./chatfifo5",0660)==-1){
		perror("mkfifo");
		exit(5);
	}
	if(mkfifo("./chatfifo6",0666)==-1){
		perror("mkfifo");
		exit(6);
	}
	if(mkfifo("./chatfifo7",0660)==-1){
		perror("mkfifo");
		exit(7);
	}
	if(mkfifo("./chatfifo8",0660)==-1){
		perror("mkfifo");
		exit(8);
	}
	if(mkfifo("./chatfifo9",0660)==-1){
		perror("mkfifo");
		exit(9);
	}

	fd1=open("./chatfifo1",O_WRONLY);
	fd2=open("./chatfifo2",O_RDONLY);
	fd3=open("./chatfifo3",O_WRONLY);
	fd4=open("./chatfifo4",O_RDONLY);
	fd5=open("./chatfifo5",O_WRONLY);
	fd6=open("./chatfifo6",O_RDONLY);
	fd7=open("./chatfifo7",O_WRONLY);
	fd8=open("./chatfifo8",O_WRONLY);
	fd9=open("./chatfifo9",O_WRONLY);

	if(fd1==-1||fd2==-1||fd3==-1||fd4==-1||fd5==-1||fd6==-1||fd7==-1||fd8==-1||fd9==-1){
		perror("open");
		exit(10);
	}

	pthread_create(&tid1,NULL,TaskCode,&fd2);
	pthread_create(&tid2,NULL,TaskCode,&fd4);
	pthread_create(&tid3,NULL,TaskCode,&fd6);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	printf("*Server starts\n");
}

