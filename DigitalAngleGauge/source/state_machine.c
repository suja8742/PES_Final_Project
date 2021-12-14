/*
 * Filename: state_machine.c
 * FIle description: Runs a state machine to operate in the Angle Gauge state and calibration state
 *  Created on: Dec 13, 2021
 *      Author: Sudarshan J
 */

/* Includes */
#include "mma8451.h"
#include "switch.h"
#include "LED.h"
#include "calibrate.h"
#include "statemachine.h"

/* Enum states */
typedef enum
{
	AccelerometerState,
	Calibration,
}states_t;

/*Function name: state_machine
 * Function description: The state machine runs the two states, the accelerometer state and the calibration state.
 * The device has been calibrated akin to a Nintendo Wii remote. It is placed on a flat surface (0 degree) for a finite time.
 * Based on feedback from the UART console, it is then calibrated ot 0 degrees to achieve required accuracy.
 * param: void
 * return: void
 */

void state_machine(void)
{
	static states_t NextState = AccelerometerState;

	switch(NextState)
	{

	case AccelerometerState:

		if(!get_status_switch())
		{
			read_full_xyz();
			convert_xyz_to_roll_pitch();
			color_control();
			NextState = AccelerometerState;
		}

		else if(get_status_switch())
		{
			NextState = Calibration;
		}

		break;

	case Calibration:

		calibration_sequeunce();
		NextState = AccelerometerState;

		break;

	}
}
