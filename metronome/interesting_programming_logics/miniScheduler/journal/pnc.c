//Producer and consumer problem
#include<stdio.h>
#include<pthread.h>

#define buffer_size 5

int buffer[buffer_size];
int count = 0;

pthread_mutex_t lock  = PTHREAD_MUTEX_INITIALIZER;

//producer
void * producer(void* arg){
	for (int i =0;i<10;i++){
		pthread_mutex_lock(&lock);
		if(count<buffer_size){
			buffer[count] = i;
			count++;
			printf("produced: %d(buffer size: %d)\n",i,count);
		}
		pthread_mutex_unlock(&lock);

	}
	return NULL;
}

//consumer
void* consumer(void* arg){
	for(int i=0;i<10;i++){
		pthread_mutex_lock(&lock);
		if(count>0){
			int item = buffer[count-1];
			count--;
			printf("consumed: %d(bufffer size: %d)\n",item,count);
		}
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
