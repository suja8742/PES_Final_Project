/*
 * Filename: switch.h
 * File description : This file containts the prototypes of the functions for the switch GPIO.
 * Toolchain: GCC, MCUXpresso IDE
 * Author: Sudarshan Jagannathan
 * Credits for code : Howdy Pierce (Lecture Slides) and Alexander Dean
 * Alexander Dean (Textbook)
*/



#ifndef SWITCH_H_
#define SWITCH_H_

/*Includes*/
#include <stdbool.h>
#include "MKL25Z4.h"

/*Function prototypes */

/* Function descriptions present in .c file. */
void switch_init();
bool get_status_switch();
bool clear_switch_flag();



#endif /* SWITCH_H_ */
