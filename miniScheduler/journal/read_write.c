#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int reader_count = 0;
int writer_count=0;
pthread_mutex_t mutex;
pthread_rwlock_t rwlock= PTHREAD_RWLOCK_INITIALIZER;

void read_lock(){
	pthread_rwlock_rdlock(&rwlock);
}


void read_unlock(){
	pthread_rwlock_unlock(&rwlock);
}

void write_lock(){
	pthread_rwlock_wrlock(&rwlock);
}

void write_unlock(){
	pthread_rwlock_unlock(&rwlock);
}

void* reader(void* arg){
	pthread_mutex_lock(&mutex);
	reader_count++;
	if(reader_count==1){
		write_lock();
	}
	pthread_mutex_unlock(&mutex);

	//read
	
	printf("Reader %d is reading!",*(int*)arg);
	sleep(1);

	pthread_mutex_lock(&mutex);
	reader_count--;
	if(reader_count==0){
		write_unlock();
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}

void* writer(void* arg){
	pthread_mutex_lock(&mutex);
	writer_count++;
	if(writer_count==1){
		read_lock();
	}
	pthread_mutex_unlock(&mutex);

	printf("Writer %d is writing",*(int*)arg);
	sleep(1);

	pthread_mutex_lock(&mutex);
	writer_count--;
	if(writer_count==0){
		read_unlock();
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(){
	return EXIT_SUCCESS;
}


