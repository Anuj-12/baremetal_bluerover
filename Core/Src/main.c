#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"
#include "uart_reader.h"
#include "rover.h"
#include "parser.h"

char msg[20] = {};

int main(){
	uart2_init(115200);
	uart1_init(115200);

	while(1){
		uart1_write_ch('Y');
		char c = uart2_read();
//		if(c != '\0'){
			uart2_write("GOT: ");
			uart2_write_ch(c);
			uart2_write("\r\n");
//		}

		for(int i = 0; i < 10000000; i++);
	}


//	uart2_write("Waiting for msg\r\n");
//	while(1){
//		if(uart1_getline(msg)){
//			uart2_write(msg);
//			break;
//		}
//	}
}
