#include "tm4c123gh6pm.h"
#include "SysTick.h"


#define PASENSOR (*((volatile unsigned long *) 0x40004070))		//Pedestrian(PA4), west(PA3), and south sensor(PA2)
#define PBLED (*((volatile unsigned long *) 0x400050FC))			//Traffic light LEDs on PB5-PB3(west lights) and PB2-PB0 (south lights)
#define PF1 (*((volatile unsigned long *) 0x40025008))				//Don't walk LED
#define PF3 (*((volatile unsigned long *) 0x40025020))				//Walk LED


void Init_Clock(void);											// Sets clock to 80MHz
void Init_PortA(void);											// Initializes Port A
void Init_PortB(void);											// Initializes Port B
void Init_PortF(void);											// Initializes Port F


struct state {
	unsigned long output;
	unsigned long delay;	//total_delay = delay * 100ms
	unsigned long next[8];
} typedef state_t;

/*Struct array which holds all the possible states*/
const state_t FSM[6] = {
	{0x42, 30, {0, 1, 0, 1, 1, 1, 1, 1}},		//GoWest
	{0x22, 15, {2, 2, 2, 2, 4, 2, 2, 2}},		//YellowWest
	{0x18, 30, {2, 2, 3, 3, 3, 3, 3, 3}},		//GoSouth
	{0x14, 15, {0, 0, 0, 0, 4, 4, 4, 4}},		//YellowSouth
	{0x13, 30, {4, 5, 5, 5, 4, 5, 5, 5}},		//Walk
	{0x13, 2, {0, 2, 0, 0, 0, 2, 0, 0}}			//WalkFast
};

int main(void)
{
	unsigned long in;
	unsigned long output;
	unsigned long walkLight;
	unsigned long noWalk;
	unsigned long currentState;
	unsigned long i;
	
	Init_Clock();
	Init_PortA();
	Init_PortB();
	Init_PortF();
	SysTick_Init();
 
	/*Initializing variables*/
  currentState = 0;
	in = 0;
	PF1 = 0x2;
	
  while(1)
	{	
		if(currentState == 5)
		{
			PF3 = 0;
			
			/*Flashing don't walk light on and off*/
			for(i = 0; i < 30; i++)
			{
				PF1 ^= 0x02;
				SysTick_Wait100ms(FSM[currentState].delay);
			}		
		}
		else
		{
			output = FSM[currentState].output;	//Getting output of current state
			
			walkLight = 0x1 & output;	//Pedestrian walk light
			walkLight <<= 3;					//Moving to correct bit position
			noWalk = ~(0x1 & output);	//Getting not of first bit in output
			noWalk <<= 1;							//Moving to correct bit position
			
			output >>= 1;							//Removing pedestrian walk light bit from output
			
			/*Setting outputs*/
			PBLED = output;	
			PF1 = noWalk;
			PF3 = walkLight;
			
			SysTick_Wait100ms(FSM[currentState].delay);	//Waiting in state for designated amount of time
		}
		
		in = PASENSOR;						//Read next inputs
		in >>= 2;									//Shifting the bits to get the correct index
		
		currentState = FSM[currentState].next[in];	//Getting next state
  }
}

void Init_Clock(void)
{
	SYSCTL_RCC2_R |= 0x80000000;		//Use RCC2
	SYSCTL_RCC2_R |= 0x00000800;	//Bybass PLL
	SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) + 0x00000540;	//Clear XTAL field and configure for 16 MHz clock
	SYSCTL_RCC2_R &= ~0x00000070;	//Configure for main oscillator source
	SYSCTL_RCC2_R &= ~0x00002000;	//Activate PLL by clearing PWRDWN
	SYSCTL_RCC2_R |= 0x40000000;	//Use 400MHz PLL
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (4 << 22);	//Clear system clock divider and configure for 80MHz clock
	while((SYSCTL_RIS_R & 0x00000040) == 0)
	{
		//Wait for PLLRIS bit
	}
	SYSCTL_RCC2_R &= ~0x00000800;	//Enable use of PLL by clearing BYPASS
}

void Init_PortA(void)
{
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x00000001;				//Activates the clock
	delay = SYSCTL_RCGC2_R;							//Allowing time to start up the clock
	GPIO_PORTA_AMSEL_R = 0x00000000;		//Disabling analog function
	GPIO_PORTA_PCTL_R = 0x00000000;			//Regular digital function
	GPIO_PORTA_DIR_R = 0x00000000;			//Setting direction register
	GPIO_PORTA_AFSEL_R = 0x00000000;		//Disabling alternate function
	GPIO_PORTA_DEN_R = 0xFF;						//Enabling digital port
}

void Init_PortB(void)
{
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x00000002;				//Activates the clock
	delay = SYSCTL_RCGC2_R;							//Allowing time to start up the clock
	GPIO_PORTB_AMSEL_R = 0x00000000;		//Disabling analog function
	GPIO_PORTB_PCTL_R = 0x00000000;			//Regular digital function
	GPIO_PORTB_DIR_R = 0x3F;			//Setting direction register
	GPIO_PORTB_AFSEL_R = 0x00000000;		//Disabling alternate function
	GPIO_PORTB_DEN_R = 0x3F;						//Enabling digital port
}

void Init_PortF(void)
{
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x00000020;				//Activates the clock
	delay = SYSCTL_RCGC2_R;							//Allowing time to start up the clock
	GPIO_PORTF_AMSEL_R = 0x00000000;		//Disabling analog function
	GPIO_PORTF_PCTL_R = 0x00000000;			//Regular digital function
	GPIO_PORTF_DIR_R = 0xA;							//Setting direction register
	GPIO_PORTF_AFSEL_R = 0x00000000;		//Disabling alternate function
	GPIO_PORTF_DEN_R = 0xA;							//Enabling digital port
}

