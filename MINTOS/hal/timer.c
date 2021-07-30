#include "STM32FDiscovery.h"
#include "hal.h"

void timer_init(void){
    RCC_APB1ENR |= 1<<0;
    TIM2_CR1 = 0; //initialize
    TIM2_PSC = 84 -1;
    TIM2_ARR = 1000 - 1;
    TIM2_DIER |= 1<<0;
    TIM2_EGR |= 1<<0;
    TIM2_CR1 |= 1<<0;

    NVIC_ISER0 |= 1<<28;
}

