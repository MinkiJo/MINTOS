#ifndef HAL_H_
#define HAL_H_

void clock_init(void);
void gpio_init(void);
void timer_init(void);
void adc_init(void);
void uart_init(void);
void sendStr(char buf[], int max);
void sendChar(char a);

#endif
