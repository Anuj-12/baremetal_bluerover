#include "stm32f401xe.h"
#include "pwm.h"

typedef struct {
    volatile uint32_t *CCR;
    volatile uint32_t *CCMR;
    uint8_t OCxM_Msk;
    uint8_t OCxM_2;
    uint8_t OCxM_1;
    uint8_t CCxS;
    uint8_t CCxP;
    uint8_t OCxPE;
    uint8_t CCxE;
} PWM_Channel;

PWM_Channel pwm_ch[4] = {
		{&TIM2->CCR1, &TIM2->CCMR1, TIM_CCMR1_OC1M_Msk, TIM_CCMR1_OC1M_2,
				TIM_CCMR1_OC1M_1, TIM_CCMR1_CC1S, TIM_CCER_CC1P, TIM_CCMR1_OC1PE, TIM_CCER_CC1E},

		{&TIM2->CCR2, &TIM2->CCMR1, TIM_CCMR1_OC2M_Msk, TIM_CCMR1_OC2M_2,
				TIM_CCMR1_OC2M_1, TIM_CCMR1_CC2S, TIM_CCER_CC2P, TIM_CCMR1_OC2PE, TIM_CCER_CC2E},

		{&TIM2->CCR3, &TIM2->CCMR2, TIM_CCMR2_OC3M_Msk, TIM_CCMR2_OC3M_2,
				TIM_CCMR2_OC3M_1, TIM_CCMR2_CC3S, TIM_CCER_CC3P, TIM_CCMR2_OC3PE, TIM_CCER_CC3E},

		{&TIM2->CCR4, &TIM2->CCMR2, TIM_CCMR2_OC4M_Msk, TIM_CCMR2_OC4M_2,
				TIM_CCMR2_OC4M_1, TIM_CCMR2_CC4S, TIM_CCER_CC4P, TIM_CCMR2_OC4PE, TIM_CCER_CC4E}
};

void led_init(void);

void pwm_init(int channel, uint16_t freq){
	channel = channel - 1; // since the array is 0 indexed but channels are 1 indexed

	/* CONFIGURING THE TIMER */
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	// SET PRESCALER
	TIM2->PSC = 4 - 1; 			// PRESCALER = 4
	// SET PWM TIME FREQUENCY
	TIM2->ARR = (4000000 / freq) - 1;


	// SET TO OUTPUT COMPARE MODE
	*(pwm_ch[channel].CCMR) &= ~(pwm_ch[channel].CCxS);
	// SET THE POLARITY TO ACTIVE HIGH
	TIM2->CCER &= ~(pwm_ch[channel].CCxP);
	// SELECT PWM MODE 1
	*(pwm_ch[channel].CCMR) &= ~(pwm_ch[channel].OCxM_Msk);
	*(pwm_ch[channel].CCMR) |= pwm_ch[channel].OCxM_2;
	*(pwm_ch[channel].CCMR) |= pwm_ch[channel].OCxM_1;
	// ENABLE DUTY CYCLE PRELOAD
	// TO PREVENT GLITCHES IN CURRENT PWM DUTY
	*(pwm_ch[channel].CCMR) |= pwm_ch[channel].OCxPE;
	// ENABLE PERIOD PRELOAD
	// TO PREVENT GLITCHES IN CURRENT PWM PERIOD
	TIM2->CR1 |= TIM_CR1_ARPE;
	// ENABLE EDGE ALIGNED MODE
	// DEFAULT IS UPCOUNTING
	TIM2->CR1 &= ~TIM_CR1_CMS_Msk;


	// ENABLE CAPTURE COMPARE AND COUNTER
	TIM2->CCER |= pwm_ch[channel].CCxE;
	TIM2->CR1 |= TIM_CR1_CEN;
}

void pwm_set_duty(int channel, uint8_t duty){
	if(duty > 100) duty = 100;

	*(pwm_ch[channel - 1].CCR) = (duty * (TIM2->ARR + 1)) / 100;
}

void led_init(void){
	/* CONFIGURING LED FOR TEST */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// SET PA5 TO ALTERNATE FXN
	GPIOA->MODER |= (1U << 11);
	GPIOA->MODER &= ~(1U << 10);
	// SET THE FUNcTION TYPE TO TIM2_CH1
	GPIOA->AFR[0] &= ~(0xF << 20);
	GPIOA->AFR[0] |=  (0x1 << 20);   // AF1
}
