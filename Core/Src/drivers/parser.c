// Could use DMA for data transfer
#include "rover.h"
#include "string.h"
#include "log.h"

void parse_uart(volatile char* msg){
	// log_init(115200)

	// returns 0 if matches
	if(strcmp("F\r\n", msg) == 0){
		rover_forward();
		log_print("[ROVER] Set direction forward\r\n");
	}else if(strcmp("B\r\n", msg) == 0){
		rover_backward();
		log_print("[ROVER] Set direction backward\r\n");
	}else if(strcmp("L\r\n", msg) == 0){
		rover_left();
		log_print("[ROVER] Set direction to the left\r\n");
	}else if(strcmp("R\r\n", msg) == 0){
		rover_right();
		log_print("[ROVER] Set direction to the right\r\n");
	}else if(strcmp("S\r\n", msg) == 0){
		rover_stop();
		log_print("[ROVER] Stop rover movement\r\n");
	}
}

