/******************************************************************************
 *
 * Module: timer0
 *
 * File Name: application.h
 *
 * Description: app src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"timer0.h"
#include"timer1.h"
/*********************************************************************************
 * 									APPLICATION									 *
 *********************************************************************************/
uint8 DELAY_DONE;
void toggle(void)
{
	// toggle the led
	g_t1tick--;
	if(!g_t1tick)
	{
		DELAY_DONE = TRUE;
	}

}
void TIMER1_delay_init(void)
{

/******************************************************
 * [name] : TIMER1_configType
 * [Type] : Structure
 * [Function] : TIMER1 Module Dynamic configuration
 * [Members] :
 * 			mode TIMER1_NORMAL or TIMER1_CTC (16bit only so it's not a conig for me)
 * 			output_mode TIMER1_NORMAL_OUTPUT or TIMER1_TOGGLE_OUTPUT etc..
 * 			compare_interrupt enable or disable
 * 			overflow_interrupt enable or disable
 * 			compare_value 0 -> 65535
 * 			initial_value 0 -> 65535
 ***************************************************/



	TIMER1_configType TIMER1_configStruct = { 	TIMER1_CTC ,
												TIMER0_F_CPU_1024 ,
												ENABLE ,
												DISABLE ,
												7812 ,
												0	};
		TIMER1_init(&TIMER1_configStruct);
		TIMER1_setCallBackCompareMode(toggle);

}
void TIMER1_delay(uint8 seconds)
{
	DELAY_DONE = FALSE;
	g_t1tick =seconds;
	TIMER1_start(TIMER0_F_CPU_1024);
	while(!DELAY_DONE){}
}
int main(void)
{
	/*initializaiton code*/


	SET_BIT(DDRD , 0);
	CLEAR_BIT(PORTD , 0);
	TIMER1_delay_init();
	GLOBAL_INTERRUPT_ENABLE();
	while(TRUE)
	{
		/* Application code*/
		TIMER1_delay(3);
		PORTD ^=(1 << PD0);
	}
}
