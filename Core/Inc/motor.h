#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

void motor_init(int channel, uint16_t freq);
void motor_init_all(uint16_t freq);
void motor_stop(int channel);
void motor_set_speed(int channel, uint8_t speed);
void motor_forward(int channel);
void motor_backward(int channel);

#endif /* INC_MOTOR_H_ */
