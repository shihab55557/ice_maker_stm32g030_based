#include "stm32g030xx.h"

void adc_init(void);


void adc_enable_vreg(void);

void adc_init();
uint16_t adc_read(uint8_t channel);

uint16_t adc_read_filtered(uint8_t channel);


uint16_t adc_read_Sx(uint8_t sensor);

		