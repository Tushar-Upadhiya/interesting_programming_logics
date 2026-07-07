#include<stdio.h>
#include<pthread.h>
i
#define buffer_size 5

int buffer[buffer_size];
int count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;


void* producer(void* arg){
	for(int i =0;i<10;i++){
		pthread_mutex_lock(&lock);
		while(count==buffer_size){
			pthread_cond_wait(&not_empty,&lock);
		}
			buffer[count]=i;
			count++;
			printf("produced: %d\n" ,i);
			pthread_cond_signal(&not_empty);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void* consumer(void* arg){
	for(int i =0;i<10;i++){
		pthread_mutex_lock(&lock);
		while(count==0){
			pthread_cond_wait(&not_full,&lock);
		}
			int item = buffer[count-1];
			count--;
			printf("consumed: %d\n",item);
			pthread_cond_signal(&not_full);
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}

int main(){
	pthread_t prod,cons;

	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);



	return 0;
}
