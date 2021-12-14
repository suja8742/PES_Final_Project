/*Filename: DigitalAngle.c
 *File Description: The main file of the project. Implements the state machine for the project.
 *Credit: Alexander Dean and Howdy Pierce
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


/* TODO: insert other include files here. */
#include "I2C.h"

#include "mma8451.h"
#include "math.h"
#include "TPM.h"
#include "systick.h"
#include "switch.h"
#include "LED.h"
#include "calibrate.h"
#include "statemachine.h"
#include "test.h"

int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	switch_init();
	Init_Blue_LED_PWM(PWM_PERIOD);
	Init_Green_LED_PWM(PWM_PERIOD);  /*PWM Init */
	Init_Red_LED_PWM(PWM_PERIOD);
	i2c_init();		/* init i2c	*/
	init_mma();		/* init mma peripheral */
	Init_Systick();



	while (1)
	{
#ifdef TEST_ALL			/*Uncomment this macro in test.h */
		i2c_test();
		MMA_range_test(pitch);
		MMA_color_test(pitch);
		Target_Angle_test(pitch);
#else
		state_machine();
#endif
	}
}
