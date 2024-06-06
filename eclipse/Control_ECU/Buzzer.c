/*
 * Buzzer.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Tarek Emad
 */

/*******************************************************************************
*                              Includes                                        *
*******************************************************************************/

#include "Buzzer.h"
#include "gpio.h"
#include "std_types.h"

/*******************************************************************************
*                             Functions Definations                            *
*******************************************************************************/


void Buzzer_Init(void)
{
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

void Buzzer_on(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

void Buzzer_off(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
