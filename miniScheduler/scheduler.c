#include "task.h"
#define MAX_TASKS 10

Task* task_list[MAX_TASKS];
int task_count = 0;

void scheduler_add(Task* task){
	if(task_count>MAX_TASKS){
	printf("Scheduler full!");
	}
		task_list[task_count]=task;
     		task_count++;
}

void scheduler_run(){
	for(int i =0;i<task_count;i++){
		task_list[i]->state = RUNNING;
		pthread_create(&task_list[i]->thread,NULL,task_list[i]->function,task_list[i]->arg);
		 pthread_join(task_list[i]->thread,NULL);
		task_list[i]->state= DONE;
	}
}

int main(){

	return EXIT_SUCCESS;
}
