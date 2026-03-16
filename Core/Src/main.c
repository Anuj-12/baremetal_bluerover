#include "stm32f401xe.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h"

int main(){
	motor_init(1, 4000);
	motor_set_speed(1, 5);

	while(1){
		motor_forward(1);
		for(int i = 0; i < 1000000; i++);
		motor_stop(1);
		for(int i = 0; i < 1000000; i++);
		motor_backward(1);
		for(int i = 0; i < 1000000; i++);
		motor_stop(1);
		for(int i = 0; i < 1000000; i++);
	}

	return 0;
}
