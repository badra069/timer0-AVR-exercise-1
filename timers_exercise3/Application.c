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
	g_t0tick--;
	if(!g_t0tick)
	{
		DELAY_DONE = TRUE;
	}

}
void TIMER0_delay_init(void)
{

	/**************************************************
	 * [name] : TIMER0_configType
	 * [Type] : Structure
	 * [Function] : TIMER0 Module Dynamic configuration
	 * [Members] :
	 * 			mode TIMER0_NORMAL or TIMER0_PWM_PHASE_CORRECT or TIMER0_CTC etc..
	 * 			output_mode TIMER0_NORMAL_OUTPUT or TIMER0_TOGGLE_OUTPUT etc..
	 * 			clock TIMER0_NON , F_CPU , 8 , 64 , 256 , 1024
	 * 			compare_interrupt enable or disable
	 * 			overflow_interrupt enable or disable
	 * 			compare_value 0 -> 255
	 * 			initial_value 0 -> 255
	 ***************************************************/



	TIMER0_configType TIMER0_configStruct = { 	TIMER0_CTC ,
												TIMER0_NORMAL_OUTPUT ,
												TIMER0_F_CPU_64 ,
												ENABLE ,
												DISABLE ,
												125 ,
												0	};
		TIMER0_init(&TIMER0_configStruct);
		TIMER0_setCallBackCompareMode(toggle);

}
void TIMER0_delay_ms(sint32 milliseconds)
{
	DELAY_DONE = FALSE;
	g_t0tick = milliseconds; // till 65 second
	TIMER0_start(TIMER0_F_CPU_64);
	while(!DELAY_DONE){}
}
int main(void)
{
	/*initializaiton code*/


	SET_BIT(DDRD , 0);
	CLEAR_BIT(PORTD , 0);
	TIMER0_delay_init();
	while(TRUE)
	{
		/* Application code*/
		TIMER0_delay_ms(3000);

		PORTD ^=(1 << PD0);
	}
}
