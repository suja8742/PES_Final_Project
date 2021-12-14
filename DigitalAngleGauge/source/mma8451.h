/*
 * mma8451.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Sudarshan
 */

#ifndef MMA8451_H
#define MMA8451_H
#include <stdint.h>

#define MMA_ADDR 0x3A
#define REG_WHOAMI 0x0D
#define WHOAMI 0x1A



int init_mma(void);
void read_full_xyz(void);
void read_xyz(void);
void convert_xyz_to_roll_pitch(void);
void calibration_mma(float pitch_calibrated);
int tap_detection(void);
int mma_sleep_init(void);
extern float roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;


#endif
