#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>

int main()
{
	long page_size = sysconf(_SC_PAGESIZE);
	printf("Size of one page is %ld bytes \n", page_size);
	size_t pool_size = page_size* 16;
	printf("16 page pool size is %zu bytes \n", pool_size);
	return 0;
}
