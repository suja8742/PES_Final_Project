/*
 * Filename: mma8451.c
 * File description: This file implements the communication interface for the mma8451 accelerometer
 * Credit: Alexander Dean
 * Modified by: Sudarshan J
 */


#include <MKL25Z4.H>
#include "mma8451.h"
#include "i2c.h"
#include <math.h>
#include "LED.h"
#include "fsl_debug_console.h"
#include "systick.h"
int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

#define DELAY_100 (100u)
#define MAX_INCREMENT (180u)
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06
#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D




/*Function name: init_mma()
 *Function description: Initializes the MMA interface over i2c.
 *Return: int
 *parameter: void
 */
int init_mma()
{
	/*set active mode, 14 bit samples and 800 Hz ODR*/
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*Function name: read_full_xyz()
 *Function description: Reads xyz values for the MMA interface.
 *Return: void
 *parameter: void
 */

void read_full_xyz()
{
	int i;

	uint8_t data[6];
	int16_t temp[3];

	/* Start and setup I2C. */
	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	/* Read five bytes in repeated mode */
	for( i=0; i<5; i++)
	{
		data[i] = i2c_repeated_read(0);
	}
	/* Read last byte ending repeated mode */
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ )
	{
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	/* Align for 14 bits */
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;
}

/*Function name: read_xyz()
 *Function description: Reads a byte of data.
 *Return: void
 *parameter: void
 */
void read_xyz(void)
{
	/* sign extend byte to 16 bits - need to cast to signed since function */
	/* returns uint8_t which is unsigned */
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	delay_systick(DELAY_100);
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	delay_systick(DELAY_100);
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);
}


/*Function name: convert_xyz_to_roll_pitch()
 *Function description: The roll and pitch is calculated.
 *Return: void
 *parameter: void
 */
void convert_xyz_to_roll_pitch(void)
{
	float ax = acc_X/COUNTS_PER_G,
			ay = acc_Y/COUNTS_PER_G,
			az = acc_Z/COUNTS_PER_G;

	roll = atan2(ay, az)*MAX_INCREMENT/M_PI;
	pitch = atan2(ax, az)*MAX_INCREMENT/M_PI;

}


