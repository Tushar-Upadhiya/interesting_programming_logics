#include<stdio.h>
#include "my_allocator.h"

int main(void){

    printf("Assigning 100 bytes of memory.....\n");
    int *arr = (int*)my_malloc(100*sizeof(int));
    if(arr==NULL){
        return -1;
    }

    for(int i =0;i<100;i++){
        arr[i]=2*i;
    }

    printf("arr[50]=%d\n",arr[50]);

    printf("Freeing the memory......\n");
    my_free(arr);
    printf("Memory successfully created and freed.\n");
    
    return 0;
}