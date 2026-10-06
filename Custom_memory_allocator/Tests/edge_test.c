#include<stdio.h>
#include"my_allocator.h"
#include<assert.h>
#include<stdint.h>

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

//alignment test
void test_alignment(void){
    void* p1 = my_malloc(1);
    void* p2 = my_malloc(3);
    void* p3 = my_malloc(13);

    assert(p1!=NULL);
    assert(p2!=NULL);
    assert(p3!=NULL);

    assert(((uintptr_t)p1%8)==0);
    assert(((uintptr_t)p2%8)==0);   
    assert(((uintptr_t)p3%8)==0);

    my_free(p1);
    my_free(p2);
    my_free(p3);

    printf("[PASS] Memory allocation is aligned to 8 bytes. \n");
}

//excessive memory allocation test
void test_excessive_alloc(void){
    void* ptr = my_malloc(1024*1024*100);
    assert(ptr==NULL);
    printf("[PASS] Excessive memory allocation returns NULL. \n");
}

//coalescing test
void test_coalescing(void){
    void* a = my_malloc(128);
    void* b = my_malloc(128);
    void* c = my_malloc(128);

    my_free(b);
    my_free(a);
    my_free(c);
    void* Big = my_malloc(384);
    assert(Big!=NULL);

    my_free(Big);
    printf("[PASS] Coalescing of free blocks works correctly. \n");
}

int main(void){
    //zero_alloc_test();
    //test_null_free();
    //test_alignment();
    //test_excessive_alloc();
    test_coalescing();
    return 0;
}
