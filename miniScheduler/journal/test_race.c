#include<stdio.h>
#include<pthread.h>

int count = 0;

void *increment(void* arg){
	for(int i =0;i<1000;i++){
		count++;
	}
	return NULL;
}

int main(){
	pthread_t p1,p2;

	pthread_create(&p1,NULL,increment,NULL);
	pthread_create(&p2,NULL,increment,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	printf("counter: %d\n",count);

	return 0;
}
