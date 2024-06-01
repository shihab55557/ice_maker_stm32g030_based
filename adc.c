#include "stm32g030xx.h"
#include "adc.h"

void adc_init(void);


void adc_enable_vreg(void){
	if(ADC1->CR & ADC_CR_ADEN){           //Disable ADC
		ADC1->CR |= ADC_CR_ADDIS;
		while(ADC1->CR & ADC_CR_ADEN);      //Wait until ADC is disabled
	}
	
	ADC1->CR   |= ADC_CR_ADVREGEN;        //Enable ADC voltage regulator
	for(uint32_t i=0;i<1000;i++){         //Wait until ADVREG is stabilized
		__NOP(); 
	}
}

void adc_init(){
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;    //GPIOA clock En
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;    //GPIOB clock En
	RCC->APBENR2|= RCC_APBENR2_ADCEN;     //ADC clock En
	RCC->CCIPR  &=~RCC_CCIPR_ADCSEL_Msk;  //ADC clock->SysClk
	
	if((RCC->APBENR2 & RCC_APBENR2_SYSCFGEN)!=RCC_APBENR2_SYSCFGEN){
	   RCC->APBENR2|= RCC_APBENR2_SYSCFGEN;
	}
	SYSCFG->CFGR1|=SYSCFG_CFGR1_PA12_RMP; //PA12 Remapped-> PA10
	
	GPIOA->MODER|= GPIO_MODER_MODE0_Msk;  //PA0 analog input
	GPIOA->MODER|= GPIO_MODER_MODE1_Msk;  //PA1 analog input
	GPIOA->MODER|= GPIO_MODER_MODE2_Msk;  //PA2 analog input
	GPIOA->MODER|= GPIO_MODER_MODE3_Msk;  //PA3 analog input
	GPIOA->MODER|= GPIO_MODER_MODE4_Msk;  //PA4 analog input
	GPIOA->MODER|= GPIO_MODER_MODE5_Msk;  //PA5 analog input
	GPIOA->MODER|= GPIO_MODER_MODE6_Msk;  //PA6 analog input
	GPIOA->MODER|= GPIO_MODER_MODE7_Msk;  //PA7 analog input
	GPIOA->MODER|= GPIO_MODER_MODE10_Msk; //PA10 analog input
	GPIOB->MODER|= GPIO_MODER_MODE7_Msk;  //PB7 analog input
	
	ADC1->CFGR2 &=~ADC_CFGR2_CKMODE_Msk;  //ADC Async Clock
	
	adc_enable_vreg();
	
	ADC1->ISR  |= ADC_ISR_ADRDY;          //Clear ADRDY Flag
	ADC1->CR   |= ADC_CR_ADEN;            //Enable ADC
	while((ADC1->ISR & ADC_ISR_ADRDY)==0);//Wait until ADC is ready
	
	if(ADC1->CFGR1 & ADC_CFGR1_CHSELRMOD){
	  ADC1->ISR  |= ADC_ISR_CCRDY;          //Clear CCRDY Flag
	  ADC1->CFGR1&=~ADC_CFGR1_CHSELRMOD;    //Single input mode
	  while((ADC1->ISR & ADC_ISR_CCRDY)==0);//Wait until change is applied
	}
	
	ADC1->CFGR1&=~ADC_CFGR1_RES_Msk;      //Resolution 12Bits
	ADC1->CFGR1&=~ADC_CFGR1_ALIGN;        //LSB allign
	ADC1->CFGR1&=~ADC_CFGR1_CONT;         //Single conversion mode
	
	ADC1->SMPR |= ADC_SMPR_SMP1_Msk;      //160.5 Clock cycle sampling
	ADC1->SMPR |= ADC_SMPR_SMP2_Msk;      //160.5 Clock cycle sampling
	
	ADC->CCR   |= ADC_CCR_VREFEN;         //Enable Vref
	
	ADC1->ISR  |= ADC_ISR_CCRDY;          //Clear CCRDY Flag
	ADC1->CHSELR = (1<<0);                //Set Channel 0
	while((ADC1->ISR & ADC_ISR_CCRDY)==0);//Wait until change is applied
}

uint16_t adc_read(uint8_t channel){
	if(ADC1->CHSELR & (1<<channel)){
		ADC1->CR |= ADC_CR_ADSTART;
		while((ADC1->ISR & ADC_ISR_EOC)==0);
		return (uint16_t)ADC1->DR;
	}else{
		ADC1->ISR  |= ADC_ISR_CCRDY;          //Clear CCRDY Flag
	  ADC1->CHSELR = (1<<channel);          //Set Channel 0
	  while((ADC1->ISR & ADC_ISR_CCRDY)==0);//Wait until change is applied
		ADC1->CR |= ADC_CR_ADSTART;
		while((ADC1->ISR & ADC_ISR_EOC)==0);
		return (uint16_t)ADC1->DR;
	}
}

uint16_t adc_read_filtered(uint8_t channel){
	adc_read(channel);
	return adc_read(channel);
}


uint16_t adc_read_Sx(uint8_t sensor){
	uint8_t index[10]={16,7,6,5,4,11,1,0,2,3};      // default index {16,7,6,5,0,2,3,4,11,1};
	return adc_read_filtered(index[sensor]);
}

		