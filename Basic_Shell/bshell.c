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

//LOOP
int main(void){
	char *line;
	while(1){
	p(BGREEN"bshell"RST CYAN" > "RST); 
	fflush(stdout);
		line = read_line();
		if(line==NULL) break;

	
	free(line);
	}
	return EXIT_SUCCESS;
}
