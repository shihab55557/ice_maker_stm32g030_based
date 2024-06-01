#include "stm32g030xx.h"
#include "serial.h"
#include "adc.h"
#include "timer.h"
#include "ntc.h"
#include "icemaker.h"



volatile int16_t timer_value = -7;

void TIM1_BRK_UP_TRG_COM_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;
			timer_value++;
			uart_send_num(timer_value);
			uart_send_char("    ");
			uart_send_num(temperature());
			uart_send_char("\r\n");
    }
}






int main(void) {
    uart_Init(38400);    // Initialize UART with desired baud rate
	  uart_send_char("\r\nDebug Started\r\n");
		timer_Init(0xFFF, 0xF43);
		adc_init();
    while (1) {
			motor_control(1);
			delay(10000);
			motor_control(2);
			delay(10000);
			motor_control(3);
			delay(10000);
    }
}

