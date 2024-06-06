/*
 * Buzzer.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Tarek Emad
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"

/*******************************************************************************
 *                                Configuration
 *******************************************************************************/
#define BUZZER_PORT_ID PORTC_ID
#define BUZZER_PIN_ID  PIN2_ID

/*******************************************************************************
 *                                Functions Prototypes
 *******************************************************************************/


void Buzzer_init(void);

void Buzzer_on(void);

void Buzzer_off(void);


#endif /* BUZZER_H_ */
