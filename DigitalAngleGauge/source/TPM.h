/*
 *Filename: TPM.h
 *File description: Supporting header file implementation for TPM.c
 *Author: Sudarshan J
 *Credit: Howdy Pierce and Alexander Dean
 */

/* Includes */
#include "stdint.h"
#include "stdio.h"
#include "MKL25Z4.h"

#ifndef TPM_H_
#define TPM_H_

/* Macros */
/* Exposed for use by other files. */
#define PWM_PERIOD (48000u)		/*Total period for the PWM. */
#define BLUE_LED_POS (1u)		/*Blue LED pin number on PORTD */
#define RED_LED_POS (18u)		/*RED and GREEN LED pin numbers on PORTB */
#define GREEN_LED_POS (19u)

void Init_Blue_LED_PWM(uint16_t period);
void Init_Green_LED_PWM(uint16_t period);
void Init_Red_LED_PWM(uint16_t period);
void DeInit_LED(void);


#endif /* TPM_H_ */


