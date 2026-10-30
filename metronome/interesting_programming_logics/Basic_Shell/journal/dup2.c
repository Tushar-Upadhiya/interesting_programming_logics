#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){
	int redirect_fd = open("output_1.txt", O_WRONLY | O_TRUNC | O_CREAT,0644);
	if(redirect_fd<0){
		perror("Failure opening file");
		exit(1);
	}
	dup2(redirect_fd,STDOUT_FILENO);
	close(redirect_fd);
	printf("This goes to output_1.txt");
	return 0;
}
