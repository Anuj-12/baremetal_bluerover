#include "stm32f401xe.h"
#include "gpio.h"
#include "pwm.h"
#include "motor.h"

typedef struct{
	// Pin structure according to L298N
	uint8_t EN;
	char EN_port;
	uint8_t IN1;
	uint8_t IN2;
}MOTOR;

MOTOR motors[4] = {
		{15, 'A', 0, 1},
		{3, 'B', 2, 3},
		{10, 'B', 10, 12},
		{11, 'B', 13, 14},
};

// -1 for channels everywhere because api is 1 indexed
void motor_init(int channel, uint16_t freq){
	channel--;

	/* CONFIGURE THE PWM PIN */
	gpio_config_alternate(motors[channel].EN_port, motors[channel].EN, 1);
	pwm_init(channel + 1, freq);	// +1 because pwm_init also subtracts it

	/* CONFIGURE THE DIRECTION PINS */
	// Always using GPIO C for direction pins
	gpio_config_output('C', motors[channel].IN1);
	gpio_config_output('C', motors[channel].IN2);
}

void motor_init_all(uint16_t freq){
	for(int i = 0; i < 4; i++){
	        gpio_config_alternate(motors[i].EN_port, motors[i].EN, 1);
	        gpio_config_output('C', motors[i].IN1);
	        gpio_config_output('C', motors[i].IN2);
	        pwm_init(i + 1, freq);
	}
}

void motor_set_speed(int channel, uint8_t speed){
	channel--;
	// duty > 100 handeled in pwm.c
	// channel - 1 handeled in pwm.c so +1
	pwm_set_duty(channel + 1, speed);
}

void motor_forward(int channel){
	channel--;

	gpio_digital_write('C', motors[channel].IN1, true);
	gpio_digital_write('C', motors[channel].IN2, false);
}

void motor_backward(int channel){
	channel--;

	gpio_digital_write('C', motors[channel].IN2, true);
	gpio_digital_write('C', motors[channel].IN1, false);
}
void motor_stop(int channel){
	channel--;

	gpio_digital_write('C', motors[channel].IN1, false);
	gpio_digital_write('C', motors[channel].IN2, false);
}


