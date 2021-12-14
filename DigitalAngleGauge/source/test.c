/*
 * Filename: test.c
 * File description:
 *  Created on: Dec 13, 2021
 *      Author: Sudarshan
 */

#include "stdint.h"
#include "i2c.h"
#include "mma8451.h"
#include "fsl_debug_console.h"
#include "systick.h"
#include "assert.h"
#include "statemachine.h"
#include "math.h"
#include "stdlib.h"

#define TARGET_ANGLE (45u)
#define STEP_SIZE (135u)
#define MAX_ANGLE (360u)
#define TIMEOUT_TEST (12u * 62u)
#define SUCCESS (1u)


/*Function Name: i2c_test()
 *Function Description: Function to test i2c functionality. Reads the WHOAMI regster for the device ID.
 *Return uint8_t
 *Param: void
 */

uint8_t i2c_test(void)
{
	static uint8_t ret_val = 0;
	ret_val = i2c_read_byte(MMA_ADDR, 0x0D);
	delay_systick(100);
	assert(ret_val == WHOAMI);
	return SUCCESS;
}


/*Function Name: MMA_range_test()
 *Function Description: Function to test accelerometer in free range. Runs for a minute.
 *Return uint8_t
 *Param: float
 */
uint8_t MMA_range_test(float pitch_val)
{
	reset_timer();
	while(get_timer() < TIMEOUT_TEST)
	{
		{
			if((fabs(pitch_val) ) <= (MAX_ANGLE))
			{
				assert(abs(pitch_val) < MAX_ANGLE);
			}
		}
	}


	return SUCCESS;
}


/*Function Name: MMA_color_test()
 *Function Description: Function to test the accelerometer in colors. Returns 1 if successful. Runs for a minute.
 *Return uint8_t
 *Param: float
 */

uint8_t MMA_color_test(float pitch_val)
{
	reset_timer();
	if((fabs(pitch_val) ) <= (MAX_ANGLE))
	{

		assert(abs(pitch_val) < MAX_ANGLE);
		state_machine();
	}
	return SUCCESS;
}


/*Function Name: Target_Angle_test()
 *Function Description: Function to test the accelerometer in colors and resolve to the target angle. Returns 1 if successful. Runs for a minute.
 *Return uint8_t
 *Param: float
 */

uint8_t Target_Angle_test(float pitch_val)
{
	reset_timer();
	if((fabs(pitch_val) ) != (TARGET_ANGLE))
	{
		assert(abs(pitch_val) < MAX_ANGLE);
		state_machine();
	}
	return SUCCESS;
}


