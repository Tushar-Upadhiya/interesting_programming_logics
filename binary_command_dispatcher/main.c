#include "cmd_dispatcher.h"
int main(void){
    uint8_t rx_stream[][2] = {
        {CMD_PING, 1},
        {CMD_GET_PWM, 75},
        {CMD_READ_TEMP, 2},
        {CMD_SYS_RESET, 0x04}
    };

    for(int i =0;i<5;i++){
        dispatch_packet(rx_stream[i][0], rx_stream[i][1]);
    }
    return 0;
}