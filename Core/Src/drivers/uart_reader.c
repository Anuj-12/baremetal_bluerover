#include "uart.h"
#include "uart_reader.h"

#define BUFFER_SIZE 50

int uart1_getline(volatile char* msg){
	static int i = 0;

	char c = uart1_read();
	if(c == '\0') return 0;

	// Message ends with \n
	if(c == '\n' || c == '\r'){
		msg[i] = '\0';
		i = 0;
		return 1;
	}
	msg[i] = c;
	i = (i + 1) % BUFFER_SIZE;
	return 0;
}
