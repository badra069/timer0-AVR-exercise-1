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

/*********************************************************************************
 * 									APPLICATION									 *
 *********************************************************************************/
void toggle(void)
{
	// toggle the led
	g_t0tick--;
	if(!g_t0tick)
	{
		PORTD ^=(1<<0);
		g_t0tick = 30;
	}

}
int main(void)
{
	/*initializaiton code*/



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


	g_t0tick = 30; // for 30 overflow that will exit the timing after tick 30
	SET_BIT(DDRD , 0);
	CLEAR_BIT(PORTD , 0);

	TIMER0_configType TIMER0_configStruct = { 	TIMER0_NORMAL ,
												TIMER0_NORMAL_OUTPUT ,
												TIMER0_F_CPU_1024 ,
												DISABLE ,
												ENABLE ,
												0 ,
												0};
	TIMER0_init(&TIMER0_configStruct);
	TIMER0_setCallBackOverflowMode(toggle);
	//TIMER0_start(TIMER0_F_CPU_1024);
	while(TRUE)
	{
		/* Application code*/
		/*_delay_ms(500);
		PORTD ^=(1<<0);*/
	}
}
