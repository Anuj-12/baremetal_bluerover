// Could use DMA for data transfer
#include "rover.h"
#include "string.h"

void parse_uart(char* msg){

	// returns 0 if matches
	if(strcmp("F\r\n", msg) == 0) rover_forward();
	else if(strcmp("B\r\n", msg) == 0) rover_backward();
	else if(strcmp("L\r\n", msg) == 0) rover_left();
	else if(strcmp("R\r\n", msg) == 0) rover_right();
	else if(strcmp("S\r\n", msg) == 0) rover_stop();
}

