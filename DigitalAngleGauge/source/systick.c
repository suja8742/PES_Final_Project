

/*
 * Filename: systick.c
 * File description : This file containts the custom API implementations and IRQ handler
 * for the ARM systick timer.
 * Toolchain: GCC, MCUXpresso IDE
 * Author: Sudarshan Jagannathan
 * Credits for code : Howdy Pierce (Lecture Slides) and Alexander Dean
 * Alexander Dean (Textbook)
 */

#ifndef SYSTICK_C_
#define SYSTICK_C_

/* Includes and defines */

#include <stdint.h>
#include <stdio.h>
#include "systick.h"

/* Global variables */
#define TOP_LOAD_VALUE (3000000/16)		/* SysTick Load value */

static volatile ticktime_t ticktime=0;
static volatile ticktime_t reset_tick_timer=0;
static volatile bool interrupt_status_flag = 0;

/* Function name: Init_Systick()
 * Return: Void
 * Param: void
 Function description: This function initializes the SysTick timer. The Initialization code
 is accredited to Alexander Dean's textbook.
 */

void Init_Systick()
{
	SysTick->LOAD = TOP_LOAD_VALUE;		/*Initializes Systick with the load register counts for our application */
	NVIC_SetPriority(SysTick_IRQn, 3);  /*Set Systick Interrupt priority to 3 on NVIC. */
	SysTick->VAL = 0;
	SysTick->CTRL = (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);	/*Enables the Systick. */
}

/* Function name: SysTick_Handler()
 * Return: Void
 * Param: void
 Function description: IRQ handler for the SysTick interrupts.
 */


void SysTick_Handler()
{
	reset_tick_timer++;
	ticktime++;
	interrupt_status_flag = 1;

}

/* Function name: now()
 * Return: ticktime_t
 * Param: void
 Function description: returns time since startup, in sixteenths of a second.
 */


ticktime_t now()
{
	return ticktime;
}

/* Function name: reset_timer()
 * Return: void
 * Param: void
 Function description: Returns the number of interrupts triggered since last reset.
 */

void reset_timer()
{
	reset_tick_timer=0;
}

/* Function name: get_timer()
 * Return: void
 * Param: void
 Function description: returns tickssince the last call to reset_timer().
 */

ticktime_t get_timer()
{
	return reset_tick_timer;
}

/* Function name: get_systick_interrupt_status()
 * Return: bool
 * Param: void
 Function description: Gives status of the interrupt flag and clear pending IRQ bits in the NVIC.
 */

bool get_systick_interrupt_status()
{
	static volatile bool return_value;
	NVIC_DisableIRQ(SysTick_IRQn);
	if(interrupt_status_flag == 1)
	{

		return_value = 1;		/*Interrupt status flag is toggled. */
	}

	if(interrupt_status_flag == 0)
	{
		return_value = 0;
	}

	interrupt_status_flag = 0;
	NVIC_EnableIRQ(SysTick_IRQn);	/* NVIC_Enable Systick IRQ */
	return (return_value);

}


/* Function name: delay_systick()
 * Return: void
 * Param: ticktime_t
 Function description: Delay based on systick timer.
 */

void delay_systick(ticktime_t systick_delay_ms)
{
	volatile ticktime_t counter = 0;
	counter = ( (16 * systick_delay_ms) / (1000) );
	reset_timer();
	while(get_timer() < counter);
}

#endif /* SYSTICK_C_ */
