/*
 * test.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Sudarshan
 */

#ifndef TEST_H_
#define TEST_H_

//#define TEST_ALL

/* Prototypes */
uint8_t i2c_test(void);
uint8_t MMA_range_test(float pitch_val);
uint8_t MMA_color_test(float pitch_val);
uint8_t Target_Angle_test(float pitch_val);

#endif /* TEST_H_ */
