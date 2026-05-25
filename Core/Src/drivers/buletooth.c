#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"
#include "uart_reader.h"
#include "log.h"
#include "bluetooth.h"

void bluetooth_init(char* name, char* password){
	uart1_init(38400);

	uart1_write("AT+RESET\r\n");
	delay(500);	// Needs time to reset

	uart1_write("AT+NAME=");
	uart1_write(name);
	uart1_write("\r\n");
	delay(200);	// To give it time to process command

	uart1_write("AT+PSWD=");
	uart1_write(password);
	uart1_write("\r\n");
	delay(200);

	uart1_write("AT+ROLE=0\r\n");	// Slave mode
	delay(200);

	uart1_init(9600);	// Data mode baud rate
}

