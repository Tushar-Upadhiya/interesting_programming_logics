#include<stdio.h>
#include"my_allocator.h"
#include<assert.h>

void zero_alloc_test(void){
    void* ptr = my_malloc(0);
    assert(ptr==NULL);
    printf("[PASS] Zero memory allocation returns NULL. \n");
}

int main(void){
    zero_alloc_test();
    return 0;
}
