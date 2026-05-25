#ifndef SRC_DRIVERS_SYSTICK_H_
#define SRC_DRIVERS_SYSTICK_H_

void systick_init();
uint32_t millis();
void delay(uint32_t ms);

#endif /* SRC_DRIVERS_SYSTICK_H_ */
