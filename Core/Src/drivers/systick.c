#include "stm32f401xe.h"
#include "systick.h"
#include "log.h"

volatile uint32_t ticks = 0;

void systick_init(){
	/*
	 16 * 10^6 clicks = 1s
	 16 * 10^3 clicks = 1ms
	 */
	// 24 bit reg -> max val 16777215
	// So max delay 1.48s
	// Setting the max to 1s
	SysTick->LOAD = 16000 - 1;

	// Clear current value
	SysTick->VAL = 0;

	// Set the clock source to the processor clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	// Enable the interrupt when counting finishes
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	// Enable SysTick timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

uint32_t millis(){
	return ticks;
}

void delay(uint32_t ms){
	log_print("Delayed\r\n");
    uint32_t start = millis();
    while(millis() - start < ms);
}

void SysTick_Handler(void){
    ticks++;
}
