/*
 * Filename: LED.h
 * File description : This file contains the supporting libraries, prototypes, macros etc. for the LED.c implementation.
 * Toolchain: GCC, MCUXpresso IDE
 * Author: Sudarshan Jagannathan
 * Credits for code : Howdy Pierce (Lecture Slides) and Alexander Dean
 * Alexander Dean (Github) - https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code
*/


#ifndef LED_H_
#define LED_H_

/*Function prototypes. */
/* Descriptions in .c file. */
void LED_Off();
uint32_t Color_Computation(uint32_t Previous_color, uint32_t Next_color, uint32_t counter);
void color_control(void);
void LED_Blinker(void);
void color_control_switch(int calibration_factor);
#endif /* LED_H_ */
