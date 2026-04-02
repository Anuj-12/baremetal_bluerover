// Could use DMA for data transfer
#include "rover.h"
#include "string.h"

void parse_uart(char* msg){

	if(strcmp("F\n", msg)) rover_forward();
	else if(strcmp("B\r\n", msg)) rover_backward();
	else if(strcmp("L\r\n", msg)) rover_left();
	else if(strcmp("R\r\n", msg)) rover_right();
	else if(strcmp("S\r\n", msg)) rover_stop();
}

