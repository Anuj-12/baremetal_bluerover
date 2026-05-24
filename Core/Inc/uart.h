#ifndef INC_UART_H_
#define INC_UART_H_

// USART1 for peripheral communication
// PB6 for TX, PB7 for RX
void uart1_init(unsigned int baud);
void uart1_write(char* msg);
void uart1_write_ch(char msg);
char uart1_read(void);

#endif /* INC_UART_H_ */
