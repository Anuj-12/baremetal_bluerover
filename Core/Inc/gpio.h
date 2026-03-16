#ifndef INC_GPIO_H_
#define INC_GPIO_H_

void gpio_config_output(char port, int pin);
void gpio_config_alternate(char port, int pin, uint8_t fxn);

#endif /* INC_GPIO_H_ */
