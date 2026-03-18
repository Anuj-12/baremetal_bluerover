#ifndef INC_UART_H_
#define INC_UART_H_

void usart_init(unsigned int baud);
void usart_write(char* msg);
void usart_write_ch(char msg);
char usart_read(void);

#endif /* INC_UART_H_ */
