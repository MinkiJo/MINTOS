#include "STM32FDiscovery.h"
#include "hal.h"

void uart_init(void){
    //USART PA2, PA3 
    RCC_AHB1ENR |= 1<<0; // PORT CLOCK 
    GPIOA_MODER |=(1<<5) | (1<<7); // alternate function using
    GPIOA_AFRL  |=(7<<8) | (7<<12); //AF7 USING 
   
    //seg USART2
    RCC_APB1ENR |=(1<<17); // UART2 CLK ENABLE 
    USART2_CR1  |=(0<<12); //
    USART2_CR2  |=(0<<13) | (0<<12);

    USART2_BRR  = (unsigned int)(42000000/115200); //115200 = baud rate

    USART2_CR1  |= (1<<3) | (1<<2); // TX RX ENABLE
    USART2_CR1  |= (1<<5); // Using flag to catch interrupt
    USART2_CR1  |= (1<<13); // USART ENABLE

    //USART interrupt enable
    NVIC_ISER1  |= 1<<6; //
}

void sendStr(char buf[], int max){
    int cnt = 0;

    while(cnt < max){
        USART2_DR = buf[cnt++]; 
        while( !(USART2_SR & (1<<7)) ); 
        while( !(USART2_SR & (1<<6)) ); 
    }
}

void sendChar(char a){
      USART2_DR = a; // echo 1byte 
      while( !(USART2_SR & (1<<7)) ); 
      while( !(USART2_SR & (1<<6)) ); 
}
