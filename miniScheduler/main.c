#include "task.h"

void * task1_func(void* arg){
	printf("Task 1 running! \n");
	return NULL;
}

void * task2_func(void* arg){
	printf("Task 2 running! \n");
	return NULL;
}

void * task3_func(void* arg){
	printf("Task 3 running! \n");
	return NULL;
}


int main(){

	Task *t1 = task_create(1, "Task1", task1_func, NULL, 1);
	Task *t2 = task_create(2, "Task2", task2_func, NULL, 1);
	Task *t3 = task_create(3, "Task3", task3_func, NULL, 1);

	scheduler_add(t1);
	scheduler_add(t2);
	scheduler_add(t3);

	scheduler_run();

	task_destroy(t1);
	task_destroy(t2);
	task_destroy(t3);

	return EXIT_SUCCESS;
}
