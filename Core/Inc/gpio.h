#ifndef INC_GPIO_H_
#define INC_GPIO_H_

typedef enum{
	false, true
} bool;

void gpio_config_output(char port, int pin);
void gpio_config_alternate(char port, int pin, uint8_t fxn);
void gpio_digital_write(char port, int pin, bool state);

#endif /* INC_GPIO_H_ */
