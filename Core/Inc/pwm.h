#ifndef INC_PWM_H_
#define INC_PWM_H_

void pwm_init(int channel, uint16_t freq);
void pwm_set_duty(int channel, uint8_t duty);

#endif /* INC_PWM_H_ */
