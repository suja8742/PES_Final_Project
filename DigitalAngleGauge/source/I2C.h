/*
 * Filename: I2C.h
 * File Description: Supporting header file implementation for I2C.c
 * Author: Sudarshan J
 * Credit: Alexander Dean
 */

#ifndef I2C_H_
#define I2C_H_
/* Includes */
#include <stdint.h>

/* Macros */

/* Function descriptions in I2C.c */
void i2c_init(void);

void i2c_start(void);
void i2c_read_setup(uint8_t dev, uint8_t address);
uint8_t i2c_repeated_read(uint8_t);

uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);
void i2c_deinit(void);


#endif /* I2C_H_ */
