#include "stm32f401xe.h"
#include "uart.h"
#include "gpio.h"

#define PERIPH_CLK			16000000
#define BUFFER_SIZE			20

typedef struct{
	volatile char data[BUFFER_SIZE];
	volatile int head;
	int tail;
}BUFFER;

BUFFER uart2_buff;

// Using USART2 for debugging comms
void log_init(unsigned int baud){
	/* CONFIGURE GPIO PINS FOR RX TX */
	gpio_config_alternate('A', 2, 7);	// set PA2 for TX
	gpio_config_alternate('A', 3, 7);	// set PA3 for RX

	/* USART CONFIGURATION */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART2->BRR = (PERIPH_CLK + (baud / 2U)) / baud;	// 16x oversampling

//	RCC->CFGR &= ~(7 << 10);	// Sets the APB1 prescaler to 1

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

	/* RESET THE UART2 BUFFER */
	uart2_buff.head = 0;
	uart2_buff.tail = 0;
}


void log_print(char* msg){
	// SHIT... SO MUCH BETTER;
	while(*msg){
		// Wait till the data from TDR has transferred to shift reg
	    while(!(USART2->SR & USART_SR_TXE));
	    //++ has higher precedence than *
	    USART2->DR = *msg++;
	}

	// Wait till the frame has been transferred completely
	while(!(USART2->SR & USART_SR_TC));
}


void log_write_ch(char msg){
    while(!(USART2->SR & USART_SR_TXE));
    USART2->DR = msg;
}


void log_read_reg(void){
	// Fill the ring buffer on IRQ
	char curr = USART2->DR;
	uart2_buff.data[uart2_buff.head] = curr;

	uart2_buff.head = (uart2_buff.head + 1) % BUFFER_SIZE;
}

char log_read(void){
	// Actually read the buffer on command
	if(uart2_buff.tail != uart2_buff.head){
		char msg =  uart2_buff.data[uart2_buff.tail];
		uart2_buff.tail = (uart2_buff.tail + 1) % BUFFER_SIZE;
		return msg;
	}
	return '\0';
}

void USART2_IRQHandler(void){
	if(USART2->SR & USART_SR_RXNE){
		log_read_reg();
	}
}


void HardFault_Handler(void){
    while(1);
}
