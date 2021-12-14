
/*Filename: switch.c
 *File description: This file has the implementation for the GPIO PortD pin 3 for external switch
 *Platform: MCUXpresso, NXP KL25Z
 *Author: Sudarshan J
 *Attributions: Howdy Pierce and Alexander Dean
 */


/*Macros and includes */

#include "switch.h"

#define RISING_EDGE 0xA0000		/* Configure interrupt on rising edge */
#define SWITCH_GPIO_PORT GPIOD	/*GPIO initialized on PORT D */

#define PORTD_PIN 3				/*PORT D, pin 3 initialized for GPIO */
#define ISFR_set 0xffffffff		/* ISFR is set */
#define SWITCH_SCGC5_MASK SIM_SCGC5_PORTD_MASK	/* PORTD clock gating control mask */

#define MASK (1 << PORTD_PIN)		/* PORTD Pin 3 mask */
#define SWITCH_PIN_CTRL_REG PORTD->PCR[PORTD_PIN]  	/* Port clear for pin 3 */
static volatile bool switch_flag = 0;	/* Flag to see if switch is pressed */


/*Function name: PORTD_IRQHandler
 * Description: Handles GPIO IRQ for PORTD GPIOs
 * Param: Void
 * Return: Void
*/

void PORTD_IRQHandler(void)
{

if(PORTD->ISFR & MASK)		/*Contains the GPIOD port pin interrupt, pin number is masked. */
{
switch_flag = !switch_flag;			/*Toggle switch */
NVIC_ClearPendingIRQ(PORTD_IRQn);		/*Clear Pending PORTD IRQs on NVIC */
PORTD->ISFR = ISFR_set;				/*ISFR is set. */
}
}


/*Function name: switch_init()
 * Description: Initializes the GPIO PortD for switch.
 * Param: Void
 * Return: Void
*/
void switch_init()
{

SIM->SCGC5 |= SWITCH_SCGC5_MASK;		/*Clock gating control for PORTD */
SWITCH_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;		/*CTRL register is cleared. */
SWITCH_PIN_CTRL_REG |= PORT_PCR_MUX(1);			/*MUX is selected on CTRL */
SWITCH_GPIO_PORT->PDDR &= ~(1<<PORTD_PIN);		/*Direction register sets Input functionality */
SWITCH_PIN_CTRL_REG |= RISING_EDGE;			/*Rising Edge interrupt is configured */
SWITCH_PIN_CTRL_REG |= PORT_PCR_PE(1) | PORT_PCR_PS(1);


NVIC_SetPriority(PORTD_IRQn, 4);		/* Interrupt Priority is lower than Systick Interrupt.*/
NVIC_ClearPendingIRQ(PORTD_IRQn);		/*Clear Pending GPIO interrupts for PORTD */
NVIC_EnableIRQ(PORTD_IRQn);				/*IRQ enabled on NVIC */

__enable_irq();

}



/*Function name: get_status_switch()
 * Description: API to return status of the switch, pressed = 1.
 * Param: Void
 * Return: bool
*/
bool get_status_switch()
{
	return (switch_flag);
}


/*Function name: clear_switch_flag()
 * Description: API to clear the button press event
 * Param: void
 * Return: bool
*/

bool clear_switch_flag()
{
	switch_flag = 0;
	return (switch_flag);
}
