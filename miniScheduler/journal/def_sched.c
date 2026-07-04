#include<stdio.h>
#include<pthread.h>

void * mythread(void* arg){
	printf("The thread is running with default scheduling.");
	return NULL;
}

int main(){
	pthread_t p ;
	pthread_create(&p,NULL,mythread,NULL);
	pthread_join(p,NULL);
	return 0;
}
