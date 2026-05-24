#include "stm32f401xe.h"
#include "uart.h"
#include "gpio.h"

#define PERIPH_CLK			16000000
#define BUFFER_SIZE			20

// Implementing a ring buffer to store data
// Overwrites data instead of overflow
typedef struct{
	volatile char data[BUFFER_SIZE];
	volatile int head;
	int tail;
}BUFFER;

BUFFER uart1_buff;


// Using USART1 for peripheral comms
void uart1_init(unsigned int baud){
	/* CONFIGURE GPIO PINS FOR RX TX */
	gpio_config_alternate('B', 6, 7);	// set PB6 for TX
	gpio_config_alternate('B', 7, 7);	// set PB7 for RX

	/* USART CONFIGURATION */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = (PERIPH_CLK + (baud / 2U)) / baud;	// 16x oversampling

	// USART RX CONFIG
	USART1->CR1 &= ~USART_CR1_M_Msk;	// Word length = 8
	USART1->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);	// 1 stop bit

	/* ENABLE INTERRUPT FOR RX */
	// RXNE is SET when there is unread data in RDR
	// RESET by reading it
	USART1->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART1_IRQn);

	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;

	/* RESET THE UART1 BUFFER */
	uart1_buff.head = 0;
	uart1_buff.tail = 0;
}


void uart1_write(char* msg){
	while(*msg){
	    while(!(USART1->SR & USART_SR_TXE));
	    //++ has higher precedence than *
	    USART1->DR = *msg++;
	}
	while(!(USART1->SR & USART_SR_TC));
}


void uart1_write_ch(char msg){
    while(!(USART1->SR & USART_SR_TXE));
    USART1->DR = msg;
}


void uart1_read_reg(void){
	// RESET RXNE by reading it
	char curr = USART1->DR;
	uart1_buff.data[uart1_buff.head] = curr;

	uart1_buff.head = (uart1_buff.head + 1) % BUFFER_SIZE;
}


char uart1_read(void){
	if(uart1_buff.tail != uart1_buff.head){
			char msg =  uart1_buff.data[uart1_buff.tail];
			uart1_buff.tail = (uart1_buff.tail + 1) % BUFFER_SIZE;
			return msg;
		}
		return '\0';
}


void USART1_IRQHandler(void){
    if(USART1->SR & USART_SR_RXNE){
        uart1_read_reg();
    }
}

