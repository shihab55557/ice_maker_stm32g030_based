#include "stm32g030xx.h"


void timer_Init(uint16_t presclaller, uint16_t arr);
uint32_t timer1_ouput(void);
uint16_t TIM1_IRQHandler(void);
//uint16_t TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void Time_count(void);
void timer3_Init(void);
void delay(uint16_t ind);