#ifndef INC_LOG_H_
#define INC_LOG_H_

// PA2 for TX, PA3 for RX
void log_init(unsigned int baud);
void log_print(char* msg);
void log_write_ch(char msg);
char log_read(void);

#endif /* INC_LOG_H_ */
