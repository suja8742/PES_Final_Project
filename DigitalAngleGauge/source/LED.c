
/*
 * Filename: LED.c
 * File description : This file contains the implementation using the PWM functionality to
 * change color with pitch angles.
 * Toolchain: GCC, MCUXpresso IDE
 * Author: Sudarshan Jagannathan
 * Credits for code : Howdy Pierce (Lecture Slides) and Alexander Dean
 * Alexander Dean (Github) - https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code
 */

/* Includes and defines */

#include "tpm.h"
#include "systick.h"
#include "LED.h"
#include "mma8451.h"
#include <math.h>
#include <stdlib.h>
#include "fsl_debug_console.h"

#define RED_COLOR_COMPOSITION   (TPM2->CONTROLS[0].CnV)
#define GREEN_COLOR_COMPOSITION (TPM2->CONTROLS[1].CnV)		/* Macroing the CnV bit for convenience */
#define BLUE_COLOR_COMPOSITION 	(TPM0->CONTROLS[1].CnV)
#define DUTY_CALC(n) ((n)*(PWM_PERIOD))/(255u)  /*Calculate duty cycle for RGB PWM functionality. */
#define MAX_STEP_SIZE (180)
#define PWM_TIME (255u)
#define DELAY_TIME (350u)
#define REF_ANGLE (135u)

/* Function name: LED_Off()
 * Return: Void
 * Param: void
 Function description: This function feeds the composition to the TPM2 register to turn off the LED.
 */

void LED_Off()
{
	RED_COLOR_COMPOSITION   = 0;
	GREEN_COLOR_COMPOSITION = 0;
	BLUE_COLOR_COMPOSITION  = 0;
}


/* Function name: Color_Computation()
 * Return: uint32_t
 * Param: uint32_t Previous_color, uint32_t Next_color, uint32_t counter
 Function description: This function computes the colours to transition from one state to the other with a color transition every 1/16th of a ms.
 */


uint32_t Color_Computation(uint32_t Previous_color, uint32_t Next_color, uint32_t counter)
{
	static volatile uint32_t Formula;
	Formula = (((((int32_t)(Next_color) - (int32_t)(Previous_color)) * (int32_t)(counter)/MAX_STEP_SIZE)) + (uint32_t)(Previous_color));
	return (Formula);
}

/* Function name: LED_Blinker()
 * Return: void
 * Param: void
 Function description: This function blinks the LED at the maximum intensity of green to indicate the target angle of 45 has been reached.
*/

void LED_Blinker(void)
{
	/* Blink green at max intensity to indicate that target angle is reached. */
	RED_COLOR_COMPOSITION = DUTY_CALC(0);
	GREEN_COLOR_COMPOSITION = DUTY_CALC(PWM_TIME);
	BLUE_COLOR_COMPOSITION = DUTY_CALC(0);

	//Delay(DELAY_TIME);
	delay_systick(DELAY_TIME);

	RED_COLOR_COMPOSITION = 0;
	GREEN_COLOR_COMPOSITION = 0;
	BLUE_COLOR_COMPOSITION = 0;
	delay_systick(DELAY_TIME);
	RED_COLOR_COMPOSITION = DUTY_CALC(0);
	GREEN_COLOR_COMPOSITION = DUTY_CALC(PWM_TIME);
	BLUE_COLOR_COMPOSITION = DUTY_CALC(0);

	delay_systick(DELAY_TIME);

	RED_COLOR_COMPOSITION = 0;
	GREEN_COLOR_COMPOSITION = 0;
	BLUE_COLOR_COMPOSITION = 0;
	delay_systick(DELAY_TIME);

}

/* Function name: color_control()
 * Return: void
 * Param: void
 Function description: Controls color based on the pitch of the accelerometer output.
*/


void color_control(void)
{
	/* Initialized only once. */
	static uint8_t red = 0, green = 0, blue = 0;
	/* Compute a reference angle based on the pitch. */
	volatile int angle = (REF_ANGLE + pitch);
	PRINTF("PITCH = %f,  ANGLE = %d\n\r", pitch, angle);

	/* If the pitch matches the target of 45, blink LED twice to indicate the target. */
	if(((int)(angle) == MAX_STEP_SIZE) || ((int)(angle) == ((-1) * (MAX_STEP_SIZE) )))
	{

		LED_Blinker();
	}

	/* If the target angle is under the maximum on the top, resolve from Red to Green as the target is neared. */
	else if( (int)(angle) < MAX_STEP_SIZE)
	{
		/* Angle is between 0 to 180. */
		if( (angle >= 0) &&(angle <= MAX_STEP_SIZE))
		{
			/* All 3 components are computed based on the angle. */
			red = Color_Computation(PWM_TIME, 0, abs(angle));
			green = Color_Computation(0, PWM_TIME, abs(angle));
			blue = Color_Computation(0, 0, abs(angle));

			RED_COLOR_COMPOSITION = DUTY_CALC(red);
			GREEN_COLOR_COMPOSITION = DUTY_CALC(green);
			BLUE_COLOR_COMPOSITION = DUTY_CALC(blue);
		}

	}

	else
	{
		/* If the angle is outside the 0-180 range, then implement this case. */
		/* Color resolves from Green to red indicating user is moving further from target. */
		red = Color_Computation(0, PWM_TIME, abs(angle));
		green = Color_Computation(PWM_TIME, 0, abs(angle));
		blue = Color_Computation(0, 0, abs(angle));

		RED_COLOR_COMPOSITION = DUTY_CALC(red);
		GREEN_COLOR_COMPOSITION = DUTY_CALC(green);
		BLUE_COLOR_COMPOSITION = DUTY_CALC(blue);
	}

}


