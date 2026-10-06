#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<stdbool.h>
#include "my_allocator.h"

typedef struct BlockHeader{
	size_t size;
	bool isfree;
	struct BlockHeader* next;
}BlockHeader;

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

	BlockHeader* firstBlock = (BlockHeader* )pool_start;
	firstBlock->size = total_pool_size - sizeof(BlockHeader);
	firstBlock->next = NULL;
	firstBlock->isfree = true;
	return 0;
}

void* my_malloc(size_t size){

	if (size==0) return NULL;

	if(pool_start == NULL){
		if(init_heap_pool()!=0){
			return NULL;
		}
	}

	BlockHeader* curr = (BlockHeader* )pool_start;
	size_t aligned_size = (size+7)&~7;

	while(curr!=NULL){
		if(curr->isfree&&curr->size>=aligned_size){
			if(curr->size>= aligned_size+sizeof(BlockHeader)+8){
				BlockHeader* new_block = (BlockHeader*)((char*)curr+sizeof(BlockHeader)+aligned_size);
				new_block->size = curr->size - aligned_size-sizeof(BlockHeader);
				new_block->isfree = true;
				new_block->next = curr->next;

				curr->size = aligned_size;
				curr->isfree=false;
				curr->next = new_block;
			}else{
				curr->isfree=false;
			}
				return (void*)(curr+1);
			}
		curr=curr->next;

	}
	return NULL;
}

void my_free(void* ptr){
	if(ptr==NULL) return;
	BlockHeader* header = (BlockHeader*)ptr -1;

		header->isfree = true;
	if(header->next!=NULL&&header->next->isfree){
		header->size = header->size+sizeof(BlockHeader)+header->next->size;
		header->next = header->next->next;
	}

	BlockHeader* prev = (BlockHeader*)pool_start;
	while(prev!=NULL&&prev->next!=header){
		prev=prev->next;
	}

	if(prev!=NULL && prev->isfree){
		prev->size = prev->size+sizeof(BlockHeader)+header->size;
		prev->next = header->next;
	}

}

