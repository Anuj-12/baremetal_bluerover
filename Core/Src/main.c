#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"
#include "log.h"
#include "uart_reader.h"
#include "rover.h"
#include "gpio.h"
#include "parser.h"

volatile char msg[50] = {};

int main(){
    log_init(115200);

    rover_init();
    log_print("[ROVER] Starting all the motors\r\n");
    rover_set_speed(50);
    log_print("[ROVER] Set speed = 50\r\n");
    log_print("[MAIN] Entering the while loop for msg parsing\r\n");

    // superloop for main, interrupt driven for USART
    while(1){
    	if(uart1_getline(msg)){
    		// Parse only when full command received
    		parse_uart(msg);
    	}
    }
}
