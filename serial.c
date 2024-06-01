#include "stm32g030xx.h"
#include "serial.h"

#define Baud9600        48000000/9600   // Baud rate calculation
#define Baud115200      48000000/115200 // Baud rate calculation

///////// FOLLOWING FUNCTION CONFIGURES USART1 LOCATED IN PB6 //////////

void uart_Init(uint32_t Baud_rate) {
		RCC->IOPENR   |= RCC_IOPENR_GPIOBEN;      /// enable GPIOB clock   
    RCC->APBENR2  |= RCC_APBENR2_USART1EN;    // Enable USART1 clock
	  

    //Configure PB6 (USART1_TX) as alternate function
	  GPIOB->MODER &=~(1<<12);    
	  GPIOB->MODER |= (1<<13);    

    // Choose AF1 for PB6 (USART1_TX)
    GPIOB->AFR[1] &= ~GPIO_AFRL_AFSEL6_Msk;
    GPIOB->AFR[1] |= (1 << GPIO_AFRL_AFSEL6_Pos);
    
    // Configure USART1
	  
    RCC->CCIPR &=~RCC_CCIPR_USART1SEL_Msk;
    RCC->CCIPR |=  RCC_CCIPR_USART1SEL_0;  
	
    USART1->BRR  = (16000000/Baud_rate);    // Set Baud rate
    USART1->CR1 |= USART_CR1_TE;            // Enable transmission
    USART1->CR1 |= USART_CR1_UE;            // Enable USART1
}

void uart_char(char ch) {
    //while (!(USART1->ISR & USART_ISR_TXE_TXFNF)); // Wait until transmit data register is empty
    USART1->TDR = ch;                             // Transmit data
	  while((USART1->ISR & USART_ISR_TC)==0);
}

void uart_send_char(char *data){
    
    while(*data){
        uart_char(*data++);
    }
    
}



int32_t uart_send_num(int32_t num) {
    char arr[10] = "0123456789";
    char num_arr[10];
    
    int ni=0;
    int i;
    int ind=0;
    int neg_checker=0;
    if (num < 0){  //to check negative number
        num = -num;// -1*num;
        ni=ni+1;
        neg_checker=1;
    }
    
    // Calculate the number of digits
    int32_t tnum=num;
    for (i = ni; i < 10; i++) {   // to find the number of digit in the number
				if ((num==0)){
						uart_char('0');
						break;
				}
        if (tnum == 0){
            break;
        }
        tnum = tnum / 10;
    }
    // Convert digits to characters and store in num_arr
    for (int ii = i-1; ii >= 0; ii--) {
        ind =  num%10;
        num_arr[ii] = arr[ind];
        num = num / 10;
    }
    
    if (neg_checker==1){
        num_arr[0]='-';
    }
    num_arr[i] = '\0'; // Null-terminate the string
    
    // Send the string through UART
    //uart_char(num_arr);
		uart_send_char(num_arr);

  //  return i; // Return the number of digits sent
}


void uart_send_num_arr(int32_t arr[10]){
	for (int i=0; i<10; i++){
		uart_send_num(arr[i]);
		uart_send_char("aa");
	}
}



void uart_flush(void) {
    while (!(USART1->ISR & USART_ISR_TC)); // Wait until transmission complete
}


void uart_send_num_bin(uint16_t num){
	int div = 512;
	uint16_t bin_store[10];
	for (int i=0; i<10; i++){
		bin_store[9-i] = (num%2);
		num = (num >> 1);
	}
	for (int i=0; i<10; i++){
		uart_send_num(bin_store[i]);
	}
}





void uart_send_num_float(float fnum) {
	  int64_t num;
	  fnum = fnum * 1000;
	  num = (int)fnum;
    char arr[10] = "0123456789";
    char num_arr[10];
    
    int ni=0;
    int i;
    int ind=0;
    int neg_checker=0;
    if (num < 0){  //to check negative number
        num = -num;// -1*num;
        ni=ni+1;
        neg_checker=1;
    }
    
    // Calculate the number of digits
    int32_t tnum=num;
    for (i = ni; i < 10; i++) {   // to find the number of digit in the number
				if ((num==0)){
						uart_char('0');
						break;
				}
        if (tnum == 0){
            break;
        }
        tnum = tnum / 10;
    }
    // Convert digits to characters and store in num_arr
    for (int ii = i-1; ii >= 0; ii--) {
        ind =  num%10;
        num_arr[ii] = arr[ind];
        num = num / 10;
    }
    
    if (neg_checker==1){
        num_arr[0]='-';
    }
    num_arr[i] = '\0'; // Null-terminate the string
    

		//uart_send_char(num_arr);
		for(int it=0; it<i; it++){
			uart_char(num_arr[it]);
			if(it==(i-4)){
				uart_char('.');
			}
		}
}