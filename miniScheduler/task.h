#pragma once
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
typedef enum{
	READY,RUNNING,BLOCKED,DONE
} TaskState;

typedef struct{
	int id;
	char name[32];
	void * (*function)(void *);
	void *arg;
	pthread_t thread;
	int priority;
	TaskState state;

}Task;

Task* task_create(int id, char*name,void* (*func)(void *),void* arg,int priority);
void task_destroy(Task* task);
void scheduler_add(Task*task);
void scheduler_run();
