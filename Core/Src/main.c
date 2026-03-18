#include "stm32f401xe.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h"
#include "uart.h"

int main(){
	usart_init(115200);
	while(1){
	    char c = usart_read();
	    if(c != '\0'){
	        usart_write_ch(c);
	    }
	}
}
