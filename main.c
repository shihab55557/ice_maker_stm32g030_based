#include "stm32g030xx.h"
#include "serial.h"
#include "adc.h"
#include "timer.h"
#include "ntc.h"
#include "icemaker.h"










int main(void) {
    uart_Init(38400);    // Initialize UART with desired baud rate
	  uart_send_char("\r\nDebug Started\r\n");
		timer_Init(0xFFF, 0xF43);
		adc_init();
    while (1) {
			ice_box_rotation();
			delay(100);
    }
}

