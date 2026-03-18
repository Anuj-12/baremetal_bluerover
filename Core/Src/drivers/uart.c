// Don't like how the buffer is handled...
// Buffer overflow is also a problem
#include "stm32f401xe.h"
#include "uart.h"
#include "gpio.h"

#define PERIPH_CLK			16000000

// buffer for storing data
volatile char data[5] = {};
int count = 0;
int read_count = 0;

// Using USART2
void usart_init(unsigned int baud){
	/* CONFIGURE GPIO PINS FOR RX TX */
	gpio_config_alternate('A', 2, 7);	// set PA2 for TX
	gpio_config_alternate('A', 3, 7);	// set PA3 for RX

	/* USART CONFIGURATION */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART2->BRR = (PERIPH_CLK + (baud / 2U)) / baud;	// 16x oversampling

	RCC->CFGR &= ~(7 << 10);

	// USART RX CONFIG
	USART2->CR1 &= ~USART_CR1_M_Msk;	// Word length = 8
	USART2->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);	// 1 stop bit

	/* ENABLE INTERRUPT FOR RX */
	// RXNE is SET when there is unread data in RDR
	// RESET by reading it
	USART2->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);

	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	USART2->CR1 |= USART_CR1_UE;
}

void usart_write(char* msg){
	// SHIT... SO MUCH BETTER;
	while(*msg){
	    while(!(USART2->SR & USART_SR_TXE));
	    USART2->DR = *msg++;
	}
}

void usart_write_ch(char msg){
    while(!(USART2->SR & USART_SR_TXE));
    USART2->DR = msg;
}

void usart_read_reg(void){
	// RESET RXNE by reading it
	char curr = USART2->DR;
	data[count] = curr;

	count = (count + 1) % 5;
}

char usart_read(void){
	if(read_count > 4) read_count = 0;

	if(read_count != count){
		return data[read_count++];
	}
	return '\0';
}

void USART2_IRQHandler(void){
	if(USART2->SR & USART_SR_RXNE){
		usart_read_reg();
	}
}
