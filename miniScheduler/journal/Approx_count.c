#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NUMCPU 4
#define THRESHOLD 5

typedef struct {
	pthread_mutex_t glock;
	int global;
	 pthread_mutex_t llock[NUMCPU];
	int local[NUMCPU];
	int threshold;

}approx_counter_t;

void counter_init(approx_counter_t* c,int threshold){
	c->global = 0;
	c->threshold = threshold;
	pthread_mutex_init(&c->glock,NULL);
	for(int i =0;i<NUMCPU;i++){
		 c->local[i]=0;
		pthread_mutex_init(&c->llock[i],NULL);
	}
}

void counter_increment(approx_counter_t* c, int cpu_id){
	pthread_mutex_lock(&c->llock[cpu_id]);
	c->local[cpu_id]++;

	if(c->local[cpu_id]>=c->threshold){
		pthread_mutex_lock(&c->glock);
		c->global+=c->local[cpu_id];
		pthread_mutex_unlock(&c->glock);
		c->local[cpu_id]=0;
	}
	pthread_mutex_unlock(&c->llock[cpu_id]);
}

int counter_get(approx_counter_t* c){
	pthread_mutex_lock(&c->glock);
	int val=c->global;
	pthread_mutex_unlock(&c->glock);
	return val;
}

approx_counter_t counter;

void* increment(void* arg){
	int cpu_id = *(int*)arg;
	for(int i =0;i<1000000;i++){
		counter_increment(&counter,cpu_id);
	}
	return NULL;
}

int main(){
	counter_init(&counter,THRESHOLD);

	pthread_t threads[NUMCPU];
	int ids[NUMCPU];

	for(int i =0;i<NUMCPU;i++){
		ids[i]=i;
		pthread_create(&threads[i],NULL,increment,&ids[i]);
	}

	for(int i =0;i<NUMCPU;i++){
		pthread_join(threads[i],NULL);
	}

	printf("value: %d\n",counter_get(&counter));

	return EXIT_SUCCESS;
}
