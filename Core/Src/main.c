#include "stm32f401xe.h"
#include "pwm.h"

int main(){

	pwm_init(4000);
	pwm_set_duty(100);
	return 0;
}
