/*
 * systick.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Sudarshan
 */

/*
 * Filename: systick.h
 * File description : This file contains relevant macros and function prototypes for the systick.c APIs.
 * Toolchain: GCC, MCUXpresso IDE
 * Author: Sudarshan Jagannathan
 * Credits for code : Howdy Pierce (Lecture Slides) and Alexander Dean
 * Alexander Dean (Textbook)
*/

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <MKL25Z4.H>
#include <stdbool.h>

typedef uint32_t ticktime_t;			/* ticktime_t is the default type for systick based counters. */

ticktime_t get_timer();
void reset_timer();
ticktime_t now();
void Init_Systick();
void delay_systick(ticktime_t systick_delay_ms);

bool get_systick_interrupt_status();

#endif /* SYSTICK_H_ */
