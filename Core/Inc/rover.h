#ifndef INC_ROVER_H_
#define INC_ROVER_H_

#include <stdint.h>

void rover_init(void);
void rover_stop(void);
void rover_set_speed(uint8_t speed);
void rover_forward(void);
void rover_backward(void);
void rover_left(void);
void rover_right(void);

#endif /* INC_ROVER_H_ */
