#include "stm32f401xe.h"
#include "pwm.h"
#include "gpio.h"

int main(){
	gpio_config_alternate('A', 5, 1);
	pwm_init(1, 4000);
	pwm_set_duty(1, 25);
	return 0;
}
