#include<stdatomic.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

atomic_flag spin_lock=ATOMIC_FLAG_INIT;

int shared_resource =0;

void* increment(void* arg){
	
	for(int i =0;i<100000;i++){
		while(atomic_flag_test_and_set(&spin_lock)){
		}
		shared_resource++;
		atomic_flag_clear(&spin_lock);
	}
	return NULL;
}

int main(){
	pthread_t p1,p2;
	
	pthread_create(&p1,NULL,increment,NULL);
	pthread_create(&p2,NULL,increment,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	printf("counter: %d\n",shared_resource);
	return EXIT_SUCCESS;
}
