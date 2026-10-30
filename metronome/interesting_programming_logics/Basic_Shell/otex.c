#include "cell.h"
int main(int argc,char*argv[]){
	int status = 0;
	(void) argc;
	int rc = fork();
	if(rc<0){
		perror("Fork Failed");
		exit(EXIT_FAILURE);
	}
	else if(rc == 0){
		execvp(argv[1],argv+1);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else{
		wait(&status);
	}
	return EXIT_SUCCESS;
}
