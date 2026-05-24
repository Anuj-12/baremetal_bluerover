#include "uart.h"
#include "uart_reader.h"

int uart2_getline(volatile char* msg){
	static int i = 0;

	char c = uart2_read();
	if(c == '\0') return 0;

	if(c == '\n'){
		msg[i] = '\0';
		i = 0;
		return 1;
	}
	msg[i++] = c;
	return 0;
}

int uart1_getline(volatile char* msg){
	static int i = 0;

	char c = uart1_read();
	if(c == '\0') return 0;

	if(c == '\n'){
		msg[i] = '\0';
		i = 0;
		return 1;
	}
	msg[i++] = c;
	return 0;
}
