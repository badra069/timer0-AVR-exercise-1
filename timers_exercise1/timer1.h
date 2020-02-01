 /******************************************************************************
 *
 * Module: dc_motor
 *
 * File Name: dc_motor.h
 *
 * Description: dc motor header file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
#ifndef _TIMER1_H_
#define _TIMER1_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"micro_config.h"
#include"common_macros.h"
#include"std_types.h"
/*********************************************************************************
* 								Types Declarations							 *
 *********************************************************************************/
extern volatile uint8 g_t1tick;
typedef enum
{
	TIMER1_NORMAL = 0x00 ,
	TIMER1_PWM_PHASE_CORRECT = 0x40 ,
	TIMER1_CTC = 0x08 ,
	TIMER1_FAST_PWM = 0x48 ,
}TIMER1_mode;

typedef enum
{
	TIMER1_NORMAL_OUTPUT ,
	TIMER1_TOGGLE_OUTPUT,
	TIMER1_CLEAR_OUTPUT ,
	TIMER1_SET_OUTPUT ,
}TIMER1_Compare_output_mode;

typedef enum
{
	TIMER1_NON ,
	TIMER1_F_CPU ,
	TIMER1_F_CPU_8 ,
	TIMER1_F_CPU_64 ,
	TIMER1_F_CPU_256 ,
	TIMER1_F_CPU_1024 ,
	TIMER1_PIN_FALLING_EDGE ,
	TIMER1_PIN_RAISING_EDGE ,
}TIMER1_clock;
/**************************************************
	 * [name] : TIMER1_configType
	 * [Type] : Structure
	 * [Function] : TIMER1 Module Dynamic configuration
	 * [Members] :
	 * 			mode TIMER1_NORMAL or TIMER1_CTC (16bit only so it's not a conig for me)
	 * 			output_mode TIMER1_NORMAL_OUTPUT or TIMER1_TOGGLE_OUTPUT etc..
	 * 			clock TIMER0_NON , F_CPU , 8 , 64 , 256 , 1024
	 * 			compare_interrupt enable or disable
	 * 			overflow_interrupt enable or disable
	 * 			compare_value 0 -> 65535
	 * 			initial_value 0 -> 65535
	 ***************************************************/
typedef struct
{
	TIMER1_mode mode;
	TIMER1_Compare_output_mode output_mode;
	TIMER1_clock clock;
	uint8 compare_interrupt;
	uint8 overflow_interrupt;
	uint8 compare_value;
	uint8 initial_value;
}TIMER1_configType;

/*********************************************************************************
* 								Function Declarations							 *
 *********************************************************************************/
void TIMER1_init(const TIMER1_configType * config_ptr);
/**********************************************************
 * [FUNCTION NAME] : TIMER1_init
 * [FUNCTION TYPE] : void
 * [TASK] :
 * 		1.setting the FOC0 bit according to the mode selected
 * 		2.initiating the counter value with a selected init value
 * 		3.setting a compare value in the OCR1
 * 		4.setting the mode of the OC1 pin as selected in the config structure
 * 		5.setting OC1 as output pin if a pwm mode selected in the config struct
 * 		6.setting OVF interrupt or COM interrupt as selected in the config struct
 * 		7.finally starting the timer
 * [ARGS] :
 *	pointer to the configuration structure :
 *		indicating a constant configurations from the user in the main application
 ***********************************************************/
void TIMER1_setCompareValue(uint8 value);
/**********************************************************
 * [FUNCTION NAME] : TIMER1_setCompareValue
 * [FUNCTION TYPE] : void
 * [TASK] : setting a new compare value in the OCR0
 * [ARGS] :
 * 	an unsigned character value :
 * 		indicating the compare value to be set in the OCR0
 ***********************************************************/

void TIMER1_start(TIMER1_clock clk);
/**********************************************************
 * [FUNCTION NAME] : TIMER1_start
 * [FUNCTION TYPE] : void
 * [TASK] : starting the timer with a certain clock (PRESCALER) and initiating the TCNT0
 * [ARGS] :
 * 	unsigned character value :
 * 		indicating the value to be set in the TCCR0 register to set the selected prescaler
 ***********************************************************/
void TIMER1_stop(void);
/**********************************************************
 * [FUNCTION NAME] : TIMER1_stop
 * [FUNCTION TYPE] : void
 * [TASK] : settingg the prescaler of the timer clock as NON
 * 			thus No clock provided(STOPPING)
 ***********************************************************/
void TIMER1_setCallBackCompareMode(void (*a_ptr)(void));
/**********************************************************
 * [FUNCTION NAME] : TIMER1_setCallBackCompareMode
 * [FUNCTION TYPE] : void
 * [TASK] : setting the code of the compare match interrupt service routine (ISR)
 * [ARGS] :
 * 	pointer to void function which takes void arguments :
 * 		indicating the code that will be executed in the ISR of the compare match
 ***********************************************************/
void TIMER1_setCallBackOverflowMode(void (*a_ptr)(void));
/**********************************************************
 * [FUNCTION NAME] : TIMER1_setCallBackOverflowMode
 * [FUNCTION TYPE] : void
 * [TASK] : setting the code of the overflow interrupt service routine (ISR)
 * [ARGS] :
 * 	pointer to void function which takes void arguments :
 * 		indicating the code that will be executed in the ISR of the overflow
 ***********************************************************/
#endif /* _TIMER1_H_ */
