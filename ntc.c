#include "stm32g030xx.h"
#include "ntc.h"
#include "adc.h"

long adctotemp(long adc){
    long T;
    if ( adc > 3979 )	{
        //uart_send("error    ");
        T=999;
    }
    else if ( adc > 3878 ){
        T= (-1024*adc + 3664896)>>10;
    }
    else if ( adc > 3714 )	{
        T= (-625*adc + 2114809)>>10;
    }
    else if ( adc > 3470 )	{
        T= (-420*adc + 1354281)>>10	;
    }
    else if ( adc >3136 )	{
        T= (-307*adc + 961762)>>10;	
    }	
    else if ( adc > 2726 )	{
        T= (-250*adc + 783484)>>10	;	
    }
    else if ( adc > 2274 )	{
        T= (-227*adc + 720198)>>10	;
    }	
    else if ( adc > 1825 )	{
        T= (-229*adc + 723641)>>10;
    }
    else if ( adc > 1420 )	{
        T= (-253*adc + 768884)>>10	;
    }	
    else if ( adc > 1080 )	{
        T= (-302*adc + 837571)>>10	;	
    }	
    else if ( adc > 811 )	{
        T= (-381*adc + 923503)>>10	;
    }	
    else{
        //uart_send("error    ");
        T=999;
    }
    return T;
}


int temperature(void){
	int temperature = 0;
	int anaread = 0;
	anaread = adc_read_filtered(7);
	temperature = adctotemp(anaread);
	return temperature;
}