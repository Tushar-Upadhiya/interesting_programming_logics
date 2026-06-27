#include "cell.h"
char * cell_read_line(void){
	char* buf;
	size_t buf_size;
	buf = NULL;
	if(getline(&buf,&buf_size,stdin)==-1){
		buf = NULL;
		if(feof(stdin))
			p(RED"[EOF]"RST);
		else
			p(RED"Getline failed!"RST);
		p("%s\n",buf);
	}
	return buf;
}
int main(int argc, char **argv){
	char * line;
	while(1){

	line = cell_read_line();
	p("%s\n",line);
	pause();

	}
	
	return EXIT_SUCCESS;
}
