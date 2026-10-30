#include<stdatomic.h>
#include<pthread.h>
#include<stdio.h>

atomic_int counter = 0;

void * increment (void * arg){
	for(int i = 0;i<100000;++i){
		atomic_fetch_add(&counter,1);
	}
	return NULL;
}

int main(){
	pthread_t p1,p2;

	pthread_create(&p1,NULL,increment,NULL);
	pthread_create(&p2,NULL,increment,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	printf("final value after increment: %d\n",atomic_load(&counter));
	return 0;
}
