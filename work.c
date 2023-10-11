#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#define N 4
#include<unistd.h>
#define MAXLINE 100
#include<string.h>
#include <sys/wait.h>
#include<sys/types.h>



void sinx_taylor(int num_elements, int terms, double* x,double* result){
	for(int i=0;i<num_elements; i++){
		double value=x[i];
		double number=x[i]*x[i]*x[i];
		double denom=6.;
		int sign=-1;
		for(int j=1;j<terms; j++){
			value+=(double)sign*number/denom;
			number*=x[i]*x[i];
			denom*=(2.*(double)j+2.)*(2.*(double)j+3.);
			sign*=-1;
		}
		result[i]=value;
	}
}

int main(){
	int n,length,status,fd[2];
	pid_t pid;
	double value;
	char message[MAXLINE],line[MAXLINE];

	double x[N]={0,M_PI/6.,M_PI/2.,0.134};
	double res[N];

	/*pipe(fd);

	if((pid=fork())==0){
		close(fd[0]);
		sinx_taylor(N,3,x,res);
		sprintf(message,"%f",value);
		length=strlen(message)+1;
		write(fd[1],message,length);
	}
	else{
		while(wait(&status)!=pid)
			continue;
		close(fd[1]);
		n=read(fd[0],line,MAXLINE);
		printf("%s",line);
	}*/
	sinx_taylor(N,3,x,res);
	for(int i=0;i<N;i++){
		printf("sin(%.2f) by taylor series=%f\n",x[i],res[i]);
		printf("sin(%.2f)=%f\n",x[i],sin(x[i]));
	}
	return 0;
}
