#include "task.h"

Task *task_create(int id,char* name,void* (*func)(void* ),void * arg,int priority ){
	Task* task = malloc(sizeof(Task));
	if(task == NULL){
	perror("Task failed");
		return NULL;
	}
	task-> id = id;
	task->function = func;
	task-> arg = arg;
	task-> priority = priority;
	task->state = READY;
	strncpy (task-> name,name,22);
	return task;
}

void task_destroy(Task* task){
	if(task!=NULL){
		free(task);
	}
}

int main(){
	return EXIT_SUCCESS;
}
