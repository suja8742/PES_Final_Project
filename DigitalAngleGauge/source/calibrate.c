/*
 * Filename: calibrate.c
 * File description: calibration routine. The calibration routine in this file is based on a nintendo wii remote.
 * It is placed on a flat surface reference, at 0*.
 *      Author: Sudarshan J
 */

/* Includes */
#include "stdint.h"
#include "switch.h"
#include "mma8451.h"
#include "fsl_debug_console.h"
#include "calibrate.h"
#include <stdlib.h>
#include "systick.h"

/* Macros/ */
#define SUCCESS (1u)
#define FAILURE (0u)
#define DELAY_500 (500u)
#define PITCH_TOLERANCE (2u)

uint8_t calibration_sequeunce()
{

	volatile uint8_t counter = 3;
	volatile int pitch_calib = (int)(pitch);

	PRINTF("Entering calibration mode \n\r");


	if( (abs(pitch_calib) >= 0) && ( abs(pitch_calib) <= PITCH_TOLERANCE) )
	{
		while(counter != 0)
		{
			counter --;
			PRINTF("%d...\n\r", counter);

		}
		PRINTF("CALIBRATION SEQUENCE SUCCESSFUL\n\r");
		delay_systick(DELAY_500);

	}

	else
	{
		PRINTF("CALIBRATION FAILED, PLACE ON A FLAT SURFACE\n\r");
		clear_switch_flag();
		delay_systick(DELAY_500);
		return (FAILURE);
	}

	clear_switch_flag();

	return SUCCESS;
}
