#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct node_t{
	int val;
	struct node_t*next;
} node_t;

typedef struct queue_t{
	node_t* head;
	node_t* tail;

	pthread_mutex_t head_lock;
	pthread_mutex_t tail_lock;
} queue_t;

void queue_init(queue_t* q){
	node_t* dummy = malloc(sizeof(node_t));

	dummy->next = NULL;

	q->head = dummy;
	q->tail = dummy;

	pthread_mutex_init(&q->head_lock,NULL);
	pthread_mutex_init(&q->tail_lock,NULL);
	
}

void enqueue(queue_t* q, int value){
	node_t* node = malloc(sizeof(node_t));
	
	node->val = value;
	node->next = NULL;

	pthread_mutex_lock(&q->tail_lock);

	q->tail->next = node;
	q->tail = node;

	pthread_mutex_unlock(&q->tail_lock);
}

int dequeue(queue_t* q , int * value){
	pthread_mutex_lock(&q->head_lock);

	node_t* node = q->head;
	node_t* new_head = node->next;

	if(new_head == NULL){
		pthread_mutex_unlock(&q->head_lock);
		return -1;
	}

	*value = new_head->val;
	q->head = new_head;
	pthread_mutex_unlock(&q->head_lock);

	free(node);
	return 0;
}

queue_t q;

void* producer(void* arg){
	for(int i =0;i<10;i++){
		enqueue(&q,i);
		printf("Enqueued : %d\n",i);
	}
	return NULL;
}

void * consumer(void * arg){
	int val;
	for(int i = 0;i<10;i++){
		while(dequeue(&q,&val)==-1)
		;
		printf("Dequeued: %d\n",val);
	}
	return NULL;
}

int main(){
	queue_init(&q);

	pthread_t prod,cons;

	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);

	return EXIT_SUCCESS;
}
