#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdatomic.h>

#define MAX_ITERATIONS 100

typedef struct{
	atomic_int flag;
	pthread_mutex_t m;
	pthread_cond_t cond;
} twolock_t;

void twolock_init(twolock_t* lock){
	atomic_init(&lock->flag,0);
	pthread_mutex_init(&lock->m,NULL);
	pthread_cond_init(&lock->cond,NULL);
}

void twolock_lock(twolock_t* lock){
	for(int i =0;i<MAX_ITERATIONS;i++){
		int expected =0;
		if(atomic_compare_exchange_strong(&lock->flag,&expected,1))
			return ;
		asm volatile("pause");
	}
	pthread_mutex_lock(&lock->m);
	while(atomic_load(&lock->flag)==1)
		pthread_cond_wait(&lock->cond,&lock->m);
	atomic_store(&lock->flag,1);
	pthread_mutex_unlock(&lock->m);
}

void twolock_unlock(twolock_t* lock){
	atomic_store(&lock->flag,0);

	pthread_mutex_lock(&lock->m);
	pthread_cond_signal(&lock->cond);
	pthread_mutex_unlock(&lock->m);
}

twolock_t lock;
int counter = 0;

void* increment(void* arg){
	for(int i =0;i<1000000;i++){
		twolock_lock(&lock);
		counter++;
		twolock_unlock(&lock);
	}
	return NULL;
}

int main(){
	twolock_init(&lock);

	pthread_t t1,t2,t3;

	pthread_create(&t1,NULL,increment,NULL);
	pthread_create(&t2,NULL,increment,NULL);
	pthread_create(&t3,NULL,increment,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	printf("value: %d \n", counter);
	return EXIT_SUCCESS;
}
