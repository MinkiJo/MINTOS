#include <stdio.h>
#include <math.h>
#include "STM32FDiscovery.h"
#include "hal/hal.h"
#include "kernel/kernel.h"



unsigned char uart_rec, adc_val;
int tim2tick = 0;
int foo = 100;

void TIM2_IRQHandler(){
   TIM2_SR &= 0x00000000;
   //tim2tick++;     
   //ADC1_CR2    |= 1<<30; //interrupt reset 
}

void USART2_IRQHandler(){
    if(USART2_SR & (1<<5)){ //Interrupt check
        uart_rec = USART2_DR;
        
        USART2_DR = uart_rec; // echo 1byte 
        while( !(USART2_SR & (1<<7)) ); // usart2_sr resigter 6,7 bit is 
        while( !(USART2_SR & (1<<6)) ); // checking process
       
        GPIOD_ODR ^= 1<<12;
	Kernel_send_events(KernelEventFlag_Uart | KernelEventFlag_Uart);
	
	switch(uart_rec){
	 case 27:
	 	Kernel_send_events(KernelEventFlag_SIGINT);
	}
        USART2_CR1 |=(1<<5); //interrupt reset	
    }    
}

void EXTI0_IRQHandler()  {
    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;
    
    EXTI_PR |= 1<<0; //clear pending bit for EXTI0
}



void task0(void);
void task1(void);
void task2(void);

static void kernel_init(){

    //char buf[32];
    //int len;
   uint32_t taskId1, taskId2, taskId3;
    Kernel_task_init();
    Kernel_event_flag_init();
   taskId1 = Kernel_task_create(task0);
 //sprintf(buf,"%d", taskId1);
  
   taskId2 = Kernel_task_create(task1);
   taskId3 = Kernel_task_create(task2);
   //sprintf(buf,"%d %d %d", taskId1, taskId2, taskId3);
   //sendStr(buf,5);

   Kernel_start();

}
    
int main (void)
{
	
   clock_init();
   
   gpio_init();
   //adc_init();
   uart_init();
   timer_init(); 
   kernel_init();
   sendStr("hi",3);
   //ADC1_CR2 |= 1<<30;

 
    while(1) {               

    }
}

void task0(){
          while(1){
        sendStr("task0\n",6);
          KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_SIGINT);
          switch(handle_event)
          {
            case KernelEventFlag_SIGINT:
                sendStr("program exit!",13);
                break;
          }                 
          Kernel_yield();    
      }
}

void task1(){
    while(1){
   sendStr("task1\n",6);
   Kernel_yield();
    }
}
void task2(){
    while(1){
   sendStr("task2\n", 6);
    Kernel_yield();
    }
}



