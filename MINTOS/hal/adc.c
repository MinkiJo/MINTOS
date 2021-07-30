#include "STM32FDiscovery.h"
#include "hal.h"

void adc_init(void){
// ADC1, channel 1, PA1

    RCC_AHB1ENR |= 0x00000001; // RCC clock enable
    GPIOA_MODER |= 3<<2;       // PA1 analog mode
    RCC_APB2ENR |= 1<<8;       // ADC clock enable
    RCC_CFGR    |= 1<<15 | 1<<13; // Seg APB2 div4 = 42MHz

    ADC1_CR2    |= 1<<0; // ADC1 enable
    
    ADC1_SMPR2  |= 3<<0; // channel 1 sammpling cycle 56 cycle
    ADC1_CR1    |= 2<<24 | 1<<5; // 8 bit resolution , quant - divide 8bit
                                 // end-of-conversion interrupt enable
    ADC1_CCR    |= 1<<16;       // PCLK2 div4
    ADC1_SQR1   |= 0<<20;       // channel 1 : 1 conversion
    ADC1_SQR3   |= 1<<0;        // 1st conversion : channeel 1
    
    NVIC_ISER0  |= 1<<18;       // enable interrupt

}
