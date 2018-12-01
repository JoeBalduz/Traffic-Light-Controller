#include "SysTick.h"
#include "tm4c123gh6pm.h"

void SysTick_Init(void)
{
	NVIC_ST_CTRL_R = 0;							//Disabling systick
	NVIC_ST_RELOAD_R = 0x00FFFFFF;	//Loading maximum value into reload register
	NVIC_ST_CURRENT_R = 0;					//Clearing current register
	NVIC_ST_CTRL_R = 0x5;						//Clock selected, no interrupt, systick enabled
}

void SysTick_Wait100ms(unsigned long delay)
{
	unsigned long i;
	
	for(i = 0; i < delay; i++)
	{
		NVIC_ST_RELOAD_R = 8000000 - 1;		//For 80MHz, 80000000 cycles is about 100ms
		NVIC_ST_CURRENT_R = 0;						//Restart counter
		
		/*Empty loop to wait until time is up*/
		while((NVIC_ST_CTRL_R & 0x00010000) == 0)
		{
		}
	}
}
