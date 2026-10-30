#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 5
uint8_t buffer[BUFFER_SIZE];
uint32_t head = 0;
uint32_t tail = 0;

bool push(uint8_t data){
    uint32_t next_head = (head+1)%BUFFER_SIZE;

    //buffer full condition
    if(next_head==tail){
        return false;
    }
    
    buffer[head]=data;
    head = next_head;

    return true;
}

bool pop(uint8_t* data){
    uint32_t next_tail = (tail+1)%BUFFER_SIZE;
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