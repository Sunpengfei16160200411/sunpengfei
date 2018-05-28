#include "LPC11XX.H"

#define LED (1<<0)
#define LEDOFF() LPC_GPIO2->DATA |= LED
#define LEDON() LPC_GPIO2->DATA &= ~LED

void Delay(uint32_t Time)
{
	uint32_t i;
	i = 0;
	while (Time--)
	{
		for(i = 0; i < 5000; i++);
	}
}

void LEDInit()
{
	LPC_SYSCON->SYSAHBCLKCTRL |=  (1<<16);
	LPC_IOCON->PIO2_0 &= ~0x07;
	LPC_IOCON->PIO2_0 |=  0x00;
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |=  (1<<6);
	LPC_GPIO2->DIR |= LED;
	LPC_GPIO2->DATA |= LED;
}

void CT32B1_Init(uint32_t interval)
{
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
		LPC_IOCON->R_PIO1_2 &= ~(0x07);
		LPC_IOCON->R_PIO1_2 |= 0x03;
		LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
		LPC_TMR32B1->TCR = 0x02;
		LPC_TMR32B1->PR = 0;
		LPC_TMR32B1->MCR = 0x02<<9;
		LPC_TMR32B1->PWMC = 0x02;
		LPC_TMR32B1->MR1 = interval/2;
		LPC_TMR32B1->MR3 = interval;
		LPC_TMR32B1->TCR = 0x01;

}

int main()
{
		uint32_t i;
		LEDInit();
	
		CT32B1_Init(SystemCoreClock/1000);
	
		while(1)
				{
				for(i=1;i<60;i++)
				{
					LPC_TMR32B1->MR1 = (SystemCoreClock/1000)/i;
					LPC_GPIO2->DATA &= LPC_TMR32B1->MR1;
					Delay(50);
				}
				for(;i>0;i--)
				{
					LPC_TMR32B1->MR1 = (SystemCoreClock/1000)/i;
					LPC_GPIO2->DATA &= LPC_TMR32B1->MR1;
					Delay(50);
				}
				
				}

}

