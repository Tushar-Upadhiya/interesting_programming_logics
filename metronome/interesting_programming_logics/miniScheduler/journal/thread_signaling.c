#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdatomic.h>

atomic_bool running = true;

void* worker(void* arg){
	while(atomic_load(&running)){
		printf("Worker is processing data...\n");
		usleep(500000);
	}
	printf("Worker detected shutdown signal . Cleaning up!\n");
	return NULL;
}

int main(){
	pthread_t thread;
	pthread_create(&thread,NULL,worker,NULL);
	usleep(2000000);

	atomic_store(&running,false);

	pthread_join(thread,NULL);
	printf("Main thread Exiting cleanly,\n");
	return EXIT_SUCCESS;
}

