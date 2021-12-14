/*
 * Filename: I2C.c
 * File description: Low-level implementation for the I2C peripheral used to communicate with the
 * MMA8451Q accelerometer.
 * Author: Sudarshan Jagannathan
 * Credit: Alexander Dean (Github)
 */

/* Includes */
#include <MKL25Z4.H>
#include "I2C.h"

/* Defines */
#define SDA_PIN (PORTE->PCR[24])
#define SCL_PIN (PORTE->PCR[25])
#define FREQ_DIVIDER_VAL (0x10)
#define FREQ_DIVIDER_REG (I2C0->F)
#define CONTROL_REG1 (I2C0->C1)
#define CONTROL_REG2 (I2C0->C2)
#define PCR_MUX_VAL (5u)
#define DATA_REG (I2C0->D)
#define STATUS_REG (I2C0->S)
#define LOCK_DETECT_THRESHOLD (200u)
#define CLOCK_GATING_REG4 (SIM->SCGC4)
#define CLOCK_GATING_REG5 (SIM->SCGC5)
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK
#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK
#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 			i2c_wait();
#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK


static int lock_detect=0;
static int i2c_lock=0;

/*
 * Function Name: i2c_init()
 * Parameters: void
 * Return: void
 * Function description: Initializes the I2C peripheral
 *
 */
void i2c_init(void)
{
	/* I2C peripheral clock setup. */
	CLOCK_GATING_REG4 |= SIM_SCGC4_I2C0_MASK;
	CLOCK_GATING_REG5 |= (SIM_SCGC5_PORTE_MASK);

	/* Set I2C pin functionality */
	SDA_PIN |= PORT_PCR_MUX(PCR_MUX_VAL);
	SCL_PIN |= PORT_PCR_MUX(PCR_MUX_VAL);

	/* Baud rate = 100KHz */
	/*baud = bus freq/(scl_div+mul) */
	/*~400k = 24M/(64); icr=0x12 sets scl_div to 64 */

	FREQ_DIVIDER_REG = (I2C_F_ICR(FREQ_DIVIDER_VAL) | I2C_F_MULT(0));

	/*enable i2c and set to master mode */
	CONTROL_REG1 |= (I2C_C1_IICEN_MASK);

	/* Select high drive mode */
	CONTROL_REG2 |= (I2C_C2_HDRS_MASK);
}


/*
 * Function Name: i2c_busy()
 * Parameters: void
 * Return: void
 * Function description: Checks for the I2C busy flag
 *
 */


void i2c_busy(void)
{
	/* Start Signal */
	lock_detect=0;
	CONTROL_REG1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	CONTROL_REG1 |=  I2C_C1_IICEN_MASK;
	/* Write to clear line */
	CONTROL_REG1 |= I2C_C1_MST_MASK; /* set MASTER mode */
	CONTROL_REG1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	DATA_REG = 0xFF;
	while ((STATUS_REG & I2C_S_IICIF_MASK) == 0U)
	{

	} /* wait interrupt */
	STATUS_REG |= I2C_S_IICIF_MASK; /* clear interrupt bit */


	/* Clear arbitration error flag*/
	STATUS_REG |= I2C_S_ARBL_MASK;


	/* Send start */
	CONTROL_REG1 &= ~I2C_C1_IICEN_MASK;
	CONTROL_REG1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	CONTROL_REG1 |= I2C_C1_MST_MASK; /* START signal generated */

	CONTROL_REG1 |= I2C_C1_IICEN_MASK;
	/*Wait until start is send*/

	/* Send stop */
	CONTROL_REG1 &= ~I2C_C1_IICEN_MASK;
	CONTROL_REG1 |= I2C_C1_MST_MASK;
	CONTROL_REG1 &= ~I2C_C1_MST_MASK; /* set SLAVE mode */
	CONTROL_REG1 &= ~I2C_C1_TX_MASK; /* Set Rx */
	CONTROL_REG1 |= I2C_C1_IICEN_MASK;


	/* wait */
	/* Clear arbitration error & interrupt flag*/
	STATUS_REG |= I2C_S_IICIF_MASK;
	STATUS_REG |= I2C_S_ARBL_MASK;
	lock_detect=0;
	i2c_lock=1;
}

/*
 * Function Name: i2c_wait()
 * Parameters: void
 * Return: void
 * Function description: Waiting for the i2c blocking function to execute.
 *
 */

void i2c_wait(void) {
	lock_detect = 0;
	/* Halts i2c for 200 lock_detect count. */
	while(((STATUS_REG & I2C_S_IICIF_MASK)==0) & (lock_detect < LOCK_DETECT_THRESHOLD))
	{
		lock_detect++;
	}

	if (lock_detect >= LOCK_DETECT_THRESHOLD)
		i2c_busy();
	STATUS_REG |= I2C_S_IICIF_MASK;
}

/*
 * Function Name: i2c_start()
 * Parameters: void
 * Return: void
 * Function description: Starts I2C transactions.
 *
 */

void i2c_start()
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

/*
 * Function Name: i2c_read_setup()
 * Parameters: uint8_t, uint8_t
 * Return: void
 * Function description: I2C read is setup.
 *
 */
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	DATA_REG = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	DATA_REG =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	DATA_REG = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to receive mode */

}

/*
 * Function Name: i2c_repeated_read()
 * Parameters: uint8_t
 * Return: uint8_t
 * Function description: I2C repeated read reads multiple bytes at once.
 *
 */

uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;

	lock_detect = 0;

	if(isLastRead)
	{
		NACK;								/*set NACK after read	*/
	}
	else
	{
		ACK;								/*ACK after read	*/
	}

	data = DATA_REG;				/*dummy read	*/
	I2C_WAIT							/*wait for completion */

	if(isLastRead)
	{
		I2C_M_STOP;					/*send stop	*/
	}
	data = DATA_REG;				/*read data	*/

	return  data;
}

/*
 * Function Name: i2c_read_byte()
 * Parameters: uint8_t, uint8_t
 * Return: uint8_t
 * Function description: Reads a single byte of data.
 */

uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	DATA_REG = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	DATA_REG =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	DATA_REG = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to recieve mode */
	NACK;									 /*set NACK after read	*/

	data = DATA_REG;					/*dummy read	*/
	I2C_WAIT								/*wait for completion */

	I2C_M_STOP;							/*send stop	*/
	data = DATA_REG;					/*read data	*/

	return data;
}



/*
 * Function Name: i2c_write_byte()
 * Parameters: uint8_t, uint8_t, uint8_t
 * Return: void
 * Function description: Writes a byte of data.
 */

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	DATA_REG = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */

	DATA_REG =  address;		/*send write address	*/
	I2C_WAIT

	DATA_REG = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;

}
