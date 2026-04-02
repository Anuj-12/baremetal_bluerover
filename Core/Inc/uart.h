#ifndef INC_UART_H_
#define INC_UART_H_

// USART2 for debugging communication
// PA2 for TX, PA3 for RX
void uart2_init(unsigned int baud);
void uart2_write(char* msg);
void uart2_write_ch(char msg);
char uart2_read(void);

// USART1 for peripheral communication
// PA9 for TX, PA10 for RX
void uart1_init(unsigned int baud);
void uart1_write(char* msg);
void uart1_write_ch(char msg);
char uart1_read(void);

#endif /* INC_UART_H_ */
