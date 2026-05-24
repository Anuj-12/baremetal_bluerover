#include "stm32f401xe.h"
#include "gpio.h"

typedef struct{
	// I like this more than the pwm style
	GPIO_TypeDef *GPIOx;
	uint32_t GPIOxEN;
}GPIO_PIN;

GPIO_PIN gpiox[5] = {
		{GPIOA, RCC_AHB1ENR_GPIOAEN},
		{GPIOB, RCC_AHB1ENR_GPIOBEN},
		{GPIOC, RCC_AHB1ENR_GPIOCEN},
		{GPIOD, RCC_AHB1ENR_GPIODEN},
		{GPIOE, RCC_AHB1ENR_GPIOEEN}
};

void gpio_config_output(char port, int pin){
	int index = port - 'A';

	RCC->AHB1ENR |= gpiox[index].GPIOxEN;

	gpiox[index].GPIOx->MODER &= ~(0x3 << (2 * pin));
	gpiox[index].GPIOx->MODER |= (1U << (2 * pin));
}

void gpio_config_alternate(char port, int pin, uint8_t fxn){
	int index = port - 'A';

	RCC->AHB1ENR |= gpiox[index].GPIOxEN;

	gpiox[index].GPIOx->MODER &= ~(0x3 << (2 * pin));
	gpiox[index].GPIOx->MODER |= (1U << ((2 * pin) + 1));

	if(pin <= 7){
		gpiox[index].GPIOx->AFR[0] &= ~(0xF << (4 * pin));
		gpiox[index].GPIOx->AFR[0] |= (fxn << (4 * pin));
	}else{
		gpiox[index].GPIOx->AFR[1] &= ~(0xF << (4 * (pin - 8)));
		gpiox[index].GPIOx->AFR[1] |= (fxn << (4 * (pin - 8)));
	}
}

void gpio_digital_write(char port, int pin, bool state){
	int index = port - 'A';

	if(state){
		gpiox[index].GPIOx->ODR |= (1U << pin);
	}else{
		gpiox[index].GPIOx->ODR &= ~(1U << pin);
	}
}


