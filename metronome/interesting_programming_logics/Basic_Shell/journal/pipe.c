#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc , char* argv[]){
	int fd[2];
	if(pipe(fd)==-1){
		perror("pipe error");
		exit(1);
	}
	int id = fork();
	if(id==0){
		int x;
		printf("Enter a number: ");
		scanf("%d",&x);
		write(fd[1],&x,sizeof(int));
		close(fd[1]);
	}
	else{
		close(fd[1]);
		int y;
		read(fd[0],&y,sizeof(int));
		close(fd[0]);
		printf("got from child process: %d\n",y);

	}
	return 0;
}
