#include<stdio.h>
#include<pthread.h>
#include<sched.h>
#include<stdlib.h>

void * mythread(void * arg){
	printf("This thread is running with special scheduling.\n");
return NULL;
}

int main(){
	pthread_t p;
	pthread_attr_t attr;
	struct sched_param param;

	pthread_attr_init (&attr);
	
	//ignoring default settings
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	
	//set the policy to round robin(SCHED_RR)
	pthread_attr_setschedpolicy(&attr,SCHED_RR);

	//set the priority(1-99 for SCHED_RR)
	param.sched_priority=10;
pthread_attr_setschedparam(&attr,&param);
	
	//passing the custom attribute object
	pthread_create(&p,&attr,mythread,NULL);
	pthread_join(p,NULL);

	pthread_attr_destroy(&attr);

return 0;
}


//while execution it is necessary to use "sudo ./vip_sched" because running command without sudo will not work as in the code we have set the policy (ScHED-RR)  and that is a system level policy change from default policy for execution of threads

