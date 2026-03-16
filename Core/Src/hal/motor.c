#include "stm32f401xe.h"
#include "gpio.h"
#include "pwm.h"
#include "motor.h"

typedef struct{
	uint8_t EN;		// GPIOA pins
	uint8_t IN1;	// GPIOC pins for both
	uint8_t IN2;
}MOTOR;

MOTOR motors[4] = {
		{0, 0, 1},
		{1, 2, 3},
		{2, 10, 12},
		{3, 13, 14},
};

// -1 for channels everywhere because api is 1 indexed
void motor_init(int channel, uint16_t freq){
	channel--;

	/* CONFIGURE THE PWM PIN */
	gpio_config_alternate('A', motors[channel].EN, 1);
	pwm_init(channel + 1, freq);	// +1 because pwm_init also subtracts it

	/* CONFIGURE THE DIRECTION PINS */
	gpio_config_output('C', motors[channel].IN1);
	gpio_config_output('C', motors[channel].IN2);
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


