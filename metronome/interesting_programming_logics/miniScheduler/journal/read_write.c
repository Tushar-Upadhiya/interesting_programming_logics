#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int reader_count = 0;
pthread_mutex_t mutex;
pthread_mutex_t write_lock= PTHREAD_MUTEX_INITIALIZER;


void* reader(void* arg){
	pthread_mutex_lock(&mutex);
	reader_count++;
	if(reader_count==1){
		pthread_mutex_lock(&write_lock);
	}
	pthread_mutex_unlock(&mutex);

	//read
	
	printf("Reader %d is reading!\n",*(int*)arg);
	sleep(1);

	pthread_mutex_lock(&mutex);
	reader_count--;
	if(reader_count==0){
		pthread_mutex_unlock(&write_lock);
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}

void* writer(void* arg){
	pthread_mutex_lock(&write_lock);

	printf("Writer %d is writing\n",*(int*)arg);
	sleep(1);

	pthread_mutex_unlock(&write_lock);

	return NULL;
}

int main(){
	pthread_mutex_init(&mutex,NULL);
	int ids[6]={1,2,3,4,5,6};
	pthread_t threads[6];

	for(int i =0;i<4;i++){
		pthread_create(&threads[i],NULL,reader,&ids[i]);
	}

	for(int i =4;i<6;i++){
		pthread_create(&threads[i],NULL,writer,&ids[i]);
	}

	for(int i =0;i<6;i++){
		pthread_join(threads[i],NULL);
		
	}
	
	pthread_mutex_destroy(&mutex);

	return EXIT_SUCCESS;
}


