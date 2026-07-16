#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdatomic.h>
#include<pthread.h>

typedef struct __spinlock_t{
	atomic_int ticket;
	atomic_int turn;
} spinlock_t;

void spinlock_init(spinlock_t* lock){
	atomic_init(&lock->ticket,0);
	atomic_init(&lock->turn,0);
}

void spinlock_lock(spinlock_t* lock){
	int my_ticket = atomic_fetch_add(&lock->ticket,1);

	while(atomic_load(&lock->turn)!=my_ticket);
}

void spinlock_unlock(spinlock_t* lock){
	atomic_fetch_add(&lock->turn,1);
}

spinlock_t lock;
int counter = 0;

void * increment(void* arg){
	int id = *(int *)arg;
	for(int i =0;i<1000000;i++){
		spinlock_lock(&lock);
		printf("Thread %d got lock!\n",id);
		counter++;
		spinlock_unlock(&lock);
	}
	return NULL;
}

int main(){
	pthread_t t1,t2,t3;
	
	int id1=1,id2=2,id3=3;

	pthread_create(&t1,NULL,increment,&id1);
	pthread_create(&t2,NULL,increment,&id2);
	pthread_create(&t3,NULL,increment,&id3);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);


	printf("value: %d\n",counter);

	return EXIT_SUCCESS;
}
