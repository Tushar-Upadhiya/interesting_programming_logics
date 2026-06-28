#include "cell.h"

// READ
char* read_line(void){
	char* buf = NULL;
	size_t buf_size=0;
	if(getline(&buf,&buf_size,stdin)==-1){
		p(RED"[EOF]\n"RST);
		free(buf);
		return NULL;
	}
	buf[strcspn(buf,"\n")]='\0';
	return buf;
}

//Tokenization
char ** tokenize(char* line){
	int cap = 16;
	char ** tokens = malloc(cap*sizeof(char*));
	int i =0;
	char* tok = strtok(line," \t");
	while(tok!=NULL){
		tokens[i++]=tok;
		if(i>=cap-1){
			cap*=2;
			tokens = realloc(tokens,cap*sizeof(char *));
		}
		tok = strtok(NULL," \t");
	}
	
	tokens[i]=NULL;
	return tokens;
}

//EXECUTE
void execute(char** args){
	int status;
	int rc = fork();
	if(rc<0){
		fprintf(stderr,"Fork failed");
		exit(1);
	}
	else if(rc ==0){
		execvp(args[0],args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else{
		wait(&status);
	}
}

//hendling the builtins like cd , exit
int handle_builtins(char** args){
	//handling cd
	if(strcmp(args[0],"cd")==0){
		//if cd with  no arguements 
		if(args[1]==NULL){
			chdir(getenv("HOME"));
		}
		else{
			if(chdir(args[1])==-1){
				perror("cd failed");
			}
		}
		return 1;
	}

	//handling exit
	if(strcmp(args[0],"exit")==0){
		//if exit with no arguement
		if(args[1]==NULL){
			exit(0);
		}
		else{
			exit(atoi(args[1]));
		}
	}
	return 0;
}

//finding pipe
int find_pipe(char ** args){
	for(int i=0;args[i]!=NULL;i++){
		if(strcmp(args[i],"|")==0){
			return i;
		}
	}
	return -1
}

//executing pipe
void execute_pipe(char** args, int pipe_index){
	int fd[2];
	pipe(fd);
	int left = fork();
	//executing the left side of the pipe
	if (left==0){
		dup2(fd[1],1);
		close(fd[0]);
		args[pipe_index]=NULL;
		execvp(args[0],args);
		perror("execvp left");
		exit(EXIT_FAILURE);
	}
	//executing the right side of the pipe
	int right = fork();
	if(right == 0){
		dup2(fd[0],0);
		close(fd[1]);
		execvp(args[pipe_index+1],args+pipe_index+1);
		perror("execvp right");
		exit(EXIT_FAILURE);

	}

	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);

}

//LOOP
int main(void){
	char *line=NULL;
	char ** args = NULL;
	while(1){
	p(BGREEN"bshell"RST CYAN">"RST " "); 
	fflush(stdout);
		line = read_line();
		if(line==NULL) break;
		args = tokenize(line);

		if(handle_builtins(args)==0){
			execute(args);
		}


	free(args);
	free(line);
	}
	return EXIT_SUCCESS;
}
