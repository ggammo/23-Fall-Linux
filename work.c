#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#define N 4
#include<unistd.h>
#define MAXLINE 100
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>


void sinx_taylor(int num_elements, int terms, double* x,double* result){
	int fd[2*N],length;
	char message[MAXLINE],line[MAXLINE];
	for(int i=0;i<num_elements;i++){
		int* p_fd=&fd[2*i];
		pipe(fd);
	}


	int pid;

	for(int i=0;i<num_elements; i++){
		int* p_fd=&fd[2*i];

		if((pid=fork())==0){
			close(p_fd[0]);
			int my_id=i;
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
			sprintf(message,"%lf",result[i]);
			length=strlen(message)+1;
			write(p_fd[1],message,length);
			exit(my_id);
		}
		else{
			close(p_fd[1]);
		}
	}

	int status;
	for(int i=0;i<num_elements;i++){
		wait(&status);
		int child_id=status>>8;
		read(fd[2*child_id],line,MAXLINE);

		double res = atof(line);
		printf("%d %lf %s\n",child_id,res,line);
		result[child_id] = res;
	}

}

int main(){
	double x[N]={0,M_PI/6.,M_PI/2.,0.134};
	double res[N];
	sinx_taylor(N,3,x,res);
	for(int i=0;i<N;i++){
		printf("sin(%.2f) by taylor series=%f\n",x[i],res[i]);
		printf("sin(%.2f)=%f\n",x[i],sin(x[i]));
	}
	return 0;
}
