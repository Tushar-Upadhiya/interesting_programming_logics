#pragma once
#include<stdint.h>

typedef enum{
    CMD_PING = 0x00,
    CMD_GET_PWM ,
    CMD_READ_TEMP,
    CMD_SYS_RESET,
    CMD_MAX
}cmd_opcode_t;

void dispatch_packet(uint8_t opcode , uint8_t payload);
