#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<assert.h>
#include<stdlib.h>

typedef struct __myarg_t{
	int a;
	int b;
} myarg_t;

typedef struct __myret_t{
	int x;
	int y;
} myret_t;

void* mythread(void* arg){
	myarg_t* args = (myarg_t*)arg;
	printf("%d %d \n", args->a,args->b);
	myret_t* rvals = malloc(sizeof(myret_t));
	rvals->x = 1;
	rvals->y = 2;
	return (void*)rvals;
}

int main(){
	pthread_t p;
	myret_t* rvals;
	myarg_t args = {10,20};
	pthread_create(&p,NULL,mythread,&args);
	pthread_join(p,(void**)rvals);
	printf("returned %d %d \n",rvals->x,rvals->y);
	free(rvals);
	return EXIT_SUCCESS;
}
