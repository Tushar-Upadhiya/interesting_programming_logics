#include<stdatomic.h>
#include<pthread.h>
#include<stdio.h>

#define NUM_THREADS 8
#define INCREMENTS_PER_THREAD 2000000

typedef struct __lock_t{
	atomic_int flag;
}lock_t;

void init(lock_t* lock){
	atomic_init(&lock->flag ,0);
}

void lock(lock_t* lock){
	while(atomic_exchange(&lock->flag,1)==1); //spin wait
}

void unlock(lock* t lock){
	atomic_store(&lock->flag,0);
}

lock_t counter_lock;
int counter = 0;

void* worker(void* arg) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        lock(&counter_lock);
        counter++;              // critical section
        unlock(&counter_lock);
    }
    return NULL;
}

int main(){
	init (&counter_lock);
	return EXIT_SUCCESS;
}
