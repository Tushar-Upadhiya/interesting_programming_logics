#include<stdio.h>
#include<pthread.h>
#include<sched.h>
#include<stdlib.h>

void * mythread(void * arg){
	printf("This thread is running with special scheduling.");
return NULL;
}

int main(){
	pthread_t p;
	pthread_attr_t attr;
	struct sched_param param;

	pthread_attr_init (&attr);

	pthread_attr_setinitsched(&attr,PTHREAD_EXPLICIT_SCHED);

	pthread_attr_setschedpolicy(&attr,SCHED_RR);

	param.sched_priority=10;
	pthread_attr_setschedparameter(&attr,&param);

	pthread_create(&p,&attr,mythread,NULL);
	pthread_join(p,NULL);

	pthread_attr_destroy(&attr);

return 0;
}
