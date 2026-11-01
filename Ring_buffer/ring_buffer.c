#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//we changed the BUFFER_SIZE to 8, so that we can use bit masking instead of modulo operation
#define BUFFER_SIZE 8
uint8_t buffer[BUFFER_SIZE];
uint32_t head = 0;
uint32_t tail = 0;

bool push(uint8_t data){
    //uint32_t next_head = (head+1)%BUFFER_SIZE;

    //using bit masking to avoid modulo operation
    //lets first change the BUFFER_SIZE to 8, so that we can use bit masking
    uint8_t next_head = (head+1)&(BUFFER_SIZE-1);
    //buffer full condition
    if(next_head==tail){
        return false;
    }
    
    buffer[head]=data;
    head = next_head;

    return true;
}

bool pop(uint8_t* data){
    ///uint32_t next_tail = (tail+1)%BUFFER_SIZE;
    uint32_t next_tail = (tail+1)&(BUFFER_SIZE-1);
    if(head==tail){
        return false;
    }
    *data = buffer[tail];
    tail= next_tail;
    return true;
}

int main(){
    push('A');
    push('B');
    push('C');
    push('D');
    
    return 0;
}