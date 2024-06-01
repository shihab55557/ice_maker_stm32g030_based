#include "stm32g030xx.h"
#include "timer.h"
#include "serial.h"
#include "icemaker.h"

/////// Steps for driving the ice maker ////////
/*
A.configure the motor pins 
	1.1 configure a function for MOTOR1 CW rotation
			P1(+), P2(GND)
	1.2 configure another function for MOTOR1 CCW rotation
			P1(GND), P2(+)
	1.3 Configure another function for MOTOR1 STOP operation
	

check whether icebox and ice container is empty if((IB=0) and (IC=0))

B. Fill water in ice box
	2. Turn ON the valve
	   2.1 if(vtime >= 6)
			 2.1.2 turn OFF the valve
			 2.1.3 Make the VALVE_FLAG = 1;
		 2.2 else if
				VALVE_FLAG = 0;






check if (VALVE_FLAG = 1) and 

C.Check whether ice is ready or not
	2. check the ice
	2.1 if(temp < -15)      // Ice is made; should be dispensed
		2.1.1 make the ICE_OPERATION flag =1
	2.2 else if(temp >= -15)
		2.2.1 make the ICE_OPERATION flag =0
		
		
	
	
Check whether icebox made ice if(ICE_OPERATION flag =1)

D.Rotate the motor
	2 Run the motor (CW initially)
			2.1 if(time>=3)         
					2.1.1 if(hall = 0)                	// check for hall feedback, Write a function for this , should be written 
																								 outside with a certain time interval (i.e from 3 to 5 sec)
						Run the motor (CW as before)      // run normally
					2.1.1.1 if (time>=7)
						STOP the motor 
					
					2.1.1.2 else if (time >= 9)
						Rotate the motor CCW
					
					2.1.1.3 else if (time >= 16)
						Stop the motor 
						MAKE THE COUNT FLAG = 0 (time = 0)
						MAKE THE ICE_OPERATION FLAG = 0
						MAKE IB = 0
						MAKE IC = 0
						VALVE_FLAG = 0
					
				2.1.2 else if (hall = 1)
					Run the motor CCW
					
					2.1.2.1 if (time >= 6)
						Stop the motor 
						MAKE THE COUNT FLAG = 0 (time = 0)
						MAKE THE ICE_OPERATION FLAG = 0
						MAKE IC = 1;
						MAKE IB = 1;
						VALVE_FLAG = 1
					
					
*/




// Function for driving motor

void motor_control(int dir){            	// dir= direction of rotation
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;    	//GPIOA clock En
	GPIOA->MODER  &=~ GPIO_MODER_MODE2_1; 
	GPIOA->MODER  |= GPIO_MODER_MODE2_0;  	//make PA2 as GPIO output
	GPIOA->MODER  &=~ GPIO_MODER_MODE3_1; 
	GPIOA->MODER  |= GPIO_MODER_MODE3_0;  	//make PA3 as GPIO output
	GPIOA->MODER  &=~ GPIO_MODER_MODE4_1; 
	GPIOA->MODER  |= GPIO_MODER_MODE4_0;  	//make PA4 as GPIO output
	GPIOA->MODER  &=~ GPIO_MODER_MODE5_1; 
	GPIOA->MODER  |= GPIO_MODER_MODE5_0;  	//make PA5 as GPIO output
	
	if(dir == 1){              // M1 forward
		GPIOA -> ODR |= (1<<2);
		GPIOA ->BSRR |= (1<<2);  // PB2 high
		
		GPIOA -> ODR &=~ (1<<3);
		GPIOA ->BSRR &=~ (1<<3); // PA3  low
	}
	
	else if(dir == 2){         // M1 reverse
		GPIOA -> ODR &=~ (1<<2);
		GPIOA ->BSRR &=~ (1<<2); // PB2 low
		
		GPIOA -> ODR |= (1<<3);
		GPIOA ->BSRR |= (1<<3);  // PA3 high
	}
	
	else if (dir == 3){        // M1 stop
		GPIOA -> ODR &=~ (1<<2);
		GPIOA ->BSRR &=~ (1<<2); // PB2 low
		
		GPIOA -> ODR &=~ (1<<3);
		GPIOA ->BSRR &=~ (1<<3); // PA3  low
	}
}
	


















