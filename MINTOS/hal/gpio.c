#include "STM32FDiscovery.h"
#include "hal.h"
   
void gpio_init(void){
 /* PORT A */
    RCC_AHB1ENR  |= 1<<0; //RCC clock enable register	
    GPIOA_MODER  |= 0<<0; // input mode
    GPIOA_OTYPER |= 0<<0; // output push-pull
    GPIOA_PUPDR  |= 0<<0; // no pull-up, pull-down
	
	/*button intr set*/
    SYSCFG_EXTICR1 |= 0<<0; // EXTI0 connect to PA0
    EXTI_IMR       |= 1<<0; // Mask EXTI0
    EXTI_RTSR      |= 1<<0; // rising edge trigger enable
    EXTI_FTSR      |= 0<<0; // falling edge trigger disable
    NVIC_ISER0     |= 1<<6; // enable EXTI0 Interrupt
    
    
    /* PORT D */
    RCC_AHB1ENR  |= 1<<3;		// PORTD enable
    GPIOD_MODER  |= 1<<24;		// PORTD 12 general output mode
    GPIOD_MODER  |= 1<<26;		// PORTD 13 general output mode
    GPIOD_MODER  |= 1<<28;		// PORTD 14 general output mode
    GPIOD_MODER  |= 1<<30;		// PORTD 15 general output mode
    GPIOD_OTYPER |= 0x00000000;
    GPIOD_PUPDR	 |= 0x00000000;
}


