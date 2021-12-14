
/*
 * Filename: TPM.c
 * File description : Low-Level TPM implementation for the PWM interface.
 * Toolchain: GCC, MCUXpresso IDE
 * Author: Sudarshan Jagannathan
 * Credits for code : Howdy Pierce (Lecture Slides) and Alexander Dean
 * Alexander Dean (Github) - https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code
*/

/* Includes */
#include "stdio.h"
#include "TPM.h"

/* Macros */
#define CLOCK_GATING_PORTD (SIM->SCGC5)
#define PORTD_PIN_CONTROL (PORTD->PCR[BLUE_LED_POS])
#define PORT_CONTROL_MUX_VALUE (4u)
#define CLOCK_GATING_TPM (SIM->SCGC6)
#define CLOCK_SOURCE_TPM (SIM->SOPT2)
#define MOD_COUNTER_0 (TPM0->MOD)
#define TPM_COUNT_DIR (TPM0->SC)
#define CONF_REG (TPM0->CONF)
#define SET_CHANNEL (TPM0->CONTROLS[1].CnSC)
#define TPM0_DUTY_CYCLE (TPM0->CONTROLS[1].CnV)
#define CLOCK_GATING_5 (SIM->SCGC5)
#define CLOCK_GATING_6 (SIM->SCGC6)
#define CLK_SRC (SIM->SOPT2)
#define MOD_REG_TPM2 (TPM2->MOD)
#define COUNT_DIR (TPM2->SC)
#define CONF_REG_2 (TPM2->CONF)
#define CHANNEL1_CONTROL (TPM2->CONTROLS[1].CnSC)
#define TPM2_DUTY_CYCLE (TPM2->CONTROLS[1].CnV)
#define TPM2_START (TPM2->SC)
#define CHANNEL_0 (TPM2->CONTROLS[0].CnSC)
#define TPM2_DUTY_CYCLE_C0 (TPM2->CONTROLS[0].CnV)
#define DBGMODE (3u)
#define CNT_DIR (1u)

/* Function name: Init_Blue_LED_PWM
 * Return: void
 * Param: uint16_t period
 Description: Initializes PWM functionality for the GPIO for Blue LED - PORT D, Pin 4.
 */

void Init_Blue_LED_PWM(uint16_t period)
{
	// Enable clock to port D
	CLOCK_GATING_PORTD |= SIM_SCGC5_PORTD_MASK;

	// Blue FTM0_CH1, Mux Alt 4
	// Set pin to FTMs
	PORTD_PIN_CONTROL &= ~PORT_PCR_MUX_MASK;
	PORTD_PIN_CONTROL |= PORT_PCR_MUX(PORT_CONTROL_MUX_VALUE);


	// Configure TPM
	CLOCK_GATING_TPM |= SIM_SCGC6_TPM0_MASK;
	//set clock source for tpm: 48 MHz
	CLOCK_SOURCE_TPM |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	MOD_COUNTER_0 = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM_COUNT_DIR =  TPM_SC_PS(CNT_DIR);
	// Continue operation in debug mode
	CONF_REG |= TPM_CONF_DBGMODE(DBGMODE);
	// Set channel 1 to edge-aligned low-true PWM
	SET_CHANNEL = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM0_DUTY_CYCLE = 0;
	// Start TPM
	TPM_COUNT_DIR |= TPM_SC_CMOD(1);
}

/* Function name: Init_Green_LED_PWM
 * Return: void
 * Param: uint16_t period
 Description: Initializes PWM functionality for the GPIO for Green LED PortB, pin 19
 */

void Init_Green_LED_PWM(uint16_t period)
{
	CLOCK_GATING_5 |= SIM_SCGC5_PORTB_MASK;

	// Blue FTM0_CH1, Mux Alt 4
	// Set pin to FTMs
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);


	// Configure TPM
	CLOCK_GATING_6 |= SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	CLK_SRC |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	MOD_REG_TPM2 = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	COUNT_DIR =  TPM_SC_PS(1);
	// Continue operation in debug mode
	CONF_REG_2 |= TPM_CONF_DBGMODE(DBGMODE);
	// Set channel 1 to edge-aligned low-true PWM
	CHANNEL1_CONTROL = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM2_DUTY_CYCLE = 0;
	// Start TPM
	TPM2_START |= TPM_SC_CMOD(1);

}

/* Function name: Init_Red_LED_PWM
 * Return: void
 * Param: uint16_t period
 Description: Initializes PWM functionality for the GPIO for RED LED PortB, pin 18.
 */

void Init_Red_LED_PWM(uint16_t period)
{


	// Blue FTM0_CH1, Mux Alt 4
	// Set pin to FTMs
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);


	// Configure TPM
	CLOCK_GATING_TPM |= SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	CLK_SRC |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	MOD_REG_TPM2 = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	COUNT_DIR =  TPM_SC_PS(1);
	// Continue operation in debug mode
	CONF_REG_2 |= TPM_CONF_DBGMODE(3);
	// Set channel 1 to edge-aligned low-true PWM
	CHANNEL_0 = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM2_DUTY_CYCLE_C0 = 0;
	// Start TPM
	TPM2_START |= TPM_SC_CMOD(1);


}

/* Function name: DeInit_LED()
 * Return: void
 * Param: void
 Description: DeInitializes the 3 LEDs to faciliate load power management.
 */

void DeInit_LED(void)
{
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX(4);
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX(3);
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX(3);
}
