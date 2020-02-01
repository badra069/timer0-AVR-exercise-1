 /******************************************************************************
 *
 * Module: timer1
 *
 * File Name: timer1.c
 *
 * Description: timer1 src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"timer1.h"
/*********************************************************************************
 * 								Global variables								 *
 *********************************************************************************/

static void (*volatile g_T0CompareInterruptFunc_ptr)(void) = NULL;

static void (*volatile g_T0OverflowInterruptFunc_ptr)(void) = NULL;

volatile uint8 g_t1tick = 0;

/*********************************************************************************
 * 								Function Definitions							 *
 *********************************************************************************/

void TIMER0_setCallBackCompareMode(void (*a_ptr)(void))
{
	g_T0CompareInterruptFunc_ptr = a_ptr;
}

void TIMER0_setCallBackOverflowMode(void (*a_ptr)(void))
{
	g_T0OverflowInterruptFunc_ptr = a_ptr;
}

void TIMER1_init(const TIMER1_configType * config_ptr)
{
	/* setting the mode -> ctc , normal or pwm */
	TCCR0 = config_ptr->mode | ((config_ptr->output_mode) << COM00);

	/* setting the initial values selected in the compare reg and counting reg (first of all)*/
	TCNT0 = config_ptr->initial_value;
	OCR0 = config_ptr->compare_value;

	/* setting the force compare bit 0 according  to the mode of the timer*/
	if(config_ptr->mode == TIMER0_NORMAL || config_ptr->mode == TIMER0_CTC)
	{
		/* in case of non-pwm mode */
		SET_BIT(TCCR0 , FOC0);
	}
	else
	{
		/* in case of a pwm mode */
		CLEAR_BIT(TCCR0 , FOC0);
	}
	if(config_ptr->output_mode != TIMER0_NORMAL_OUTPUT )
	{
		/* for the signal pwm output pin (if pwm mode configured only) */
		SET_BIT(DDRB , 3);
		CLEAR_BIT(PORTB , 3);
	}
	/* setting the interrupt modes */
	TIMSK |= (config_ptr->overflow_interrupt << TOIE0) | ((config_ptr ->compare_interrupt)<<OCIE0);

	/* starting the timer NOW after all settings is done*/
	TCCR0 |=config_ptr ->clock;

	/* enabling the global interrupt */
	GLOBAL_INTERRUPT_ENABLE();
}

void TIMER1_start(TIMER0_clock clk)
{
	/* setting the prescaler thus enabling the clock then initializing the counter */
	TCCR0 |= clk;
	TCNT0 = 0;
}


void TIMER1_setCompareValue(uint8 value)
{
	OCR0 = value;
}

void TIMER1_stop(void)
{
	CLEAR_BIT(TCCR0 , 0);
	CLEAR_BIT(TCCR0 , 1);
	CLEAR_BIT(TCCR0 , 2);
}


/*********************************************************************************
 * 								interrupt service routines						 *
 *********************************************************************************/

ISR(TIMER0_COMP_vect)
{
	/* the corresponding interrupt service routine function (IF EXIST) will be executed*/
	if(g_T0CompareInterruptFunc_ptr != NULL)
	{
		g_T0CompareInterruptFunc_ptr();
	}
}


ISR(TIMER0_OVF_vect)
{
	/* the corresponding interrupt service routine function (IF EXIST) will be executed*/
	if(g_T0OverflowInterruptFunc_ptr != NULL)
	{
		g_T0OverflowInterruptFunc_ptr();
	}
}
