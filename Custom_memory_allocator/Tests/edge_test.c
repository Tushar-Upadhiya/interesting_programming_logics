#include<stdio.h>
#include"my_allocator.h"
#include<assert.h>

//Zero memory allocation test
void zero_alloc_test(void){
    void* ptr = my_malloc(0);
    assert(ptr==NULL);
    printf("[PASS] Zero memory allocation returns NULL. \n");
}

//Freeing NULL Pointer test
void test_null_free(void){
    my_free(NULL);
    printf("[PASS] Freeing NULL pointer does not cause any issues. \n");
}

int main(void){
    //zero_alloc_test();
    test_null_free();
    return 0;
}
