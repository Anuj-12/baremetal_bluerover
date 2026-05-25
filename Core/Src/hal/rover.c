#include "stm32f401xe.h"
#include "motor.h"
#include "rover.h"

#define FREQ		4000
/*
 * Channel to motor mapping
 * 1	3
 * 2	4
 */

void rover_init(void){
	motor_init(1, FREQ);
	motor_init(2, FREQ);
	motor_init(3, FREQ);
	motor_init(4, FREQ);
}

void rover_stop(void){
	motor_stop(1);
	motor_stop(2);
	motor_stop(3);
	motor_stop(4);
}

void rover_set_speed(uint8_t speed){
	// 0 - 100
	motor_set_speed(1, speed);
	motor_set_speed(2, speed);
	motor_set_speed(3, speed);
	motor_set_speed(4, speed);
}

void rover_forward(void){
	motor_forward(1);
	motor_forward(2);
	motor_forward(3);
	motor_forward(4);
}

void rover_backward(void){
	motor_backward(1);
	motor_backward(2);
	motor_backward(3);
	motor_backward(4);
}

void rover_left(void){
	motor_backward(1);
	motor_backward(2);
	motor_forward(3);
	motor_forward(4);
}

void rover_right(void){
	motor_forward(1);
	motor_forward(2);
	motor_backward(3);
	motor_backward(4);
}
