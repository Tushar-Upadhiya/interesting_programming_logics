#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>

static void* pool_start = NULL;
static size_t total_pool_size = 0;

static int init_heap_pool(void){
	long page_size = sysconf(_SC_PAGESIZE);
	if(page_size<0){
	return -1;
	}

	total_pool_size = (size_t)page_size*16;

	pool_start = mmap(
		NULL,
		total_pool_size,
		PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS,
		-1,
		0
	);

	if(pool_start == MAP_FAILED){
		pool_start = NULL;
		return -1;
	}
	return 0;
}

void* my_malloc(size_t size){
	
	return NULL;
}

void my_free(void* ptr){

}
int main()
{
	return 0;
}
