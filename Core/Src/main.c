#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"
#include "log.h"
#include "uart_reader.h"
#include "rover.h"
#include "gpio.h"
#include "parser.h"
#include "bluetooth.h"

volatile char msg[50] = {};

int main(){
//    log_init(115200);
//    bluetooth_init("Rover", "0000");
//    log_print("[BLUETOOTH] Initializing bluetooth name and password\r\n");
//
//    rover_init();
//    log_print("[ROVER] Starting all the motors\r\n");
//    rover_set_speed(50);
//    log_print("[ROVER] Set speed = 50\r\n");
//    log_print("[MAIN] Entering the while loop for msg parsing\r\n");

    log_init(115200);
	uart1_init(38400);
	uart1_write("AT\r\n");
    // superloop for main, interrupt driven for USART
    while(1){
    	if(uart1_getline(msg)){
    		// Parse only when full command received
    		log_print(msg);
    	}
    }
}
