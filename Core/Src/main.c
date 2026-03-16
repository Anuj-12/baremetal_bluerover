#include "stm32f401xe.h"
#include "pwm.h"

int main(){

	pwm_init(1, 4000);
	pwm_set_duty(1, 50);
	return 0;
}
