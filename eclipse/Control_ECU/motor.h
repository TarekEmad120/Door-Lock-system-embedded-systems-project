 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: motor.h
 *
 * Author: Tarek Emad
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

/*******************************************************************************
                                  Includes
 *******************************************************************************/
#include "gpio.h"
#include "pwm.h"
#include "common_macros.h"
#include <avr/io.h>


#define MOTOR_PORT_OUT  PORTB_ID
#define MOTOR_PIN_ID0   PIN0_ID
#define MOTOR_PIN_ID1   PIN1_ID
/*******************************************************************************
 *                                enums                                 *
 *******************************************************************************/
typedef enum
{
    MOTOR_STOP,
    MOTOR_clockwise,
    MOTOR_anti_clockwise
}Motor_Dir;
/*******************************************************************************
 *                                FUNCTIONS PROTOTYPES                                 *
 *******************************************************************************/
/*
 Description
 The Function responsible for setup the direction for the two
 motor pins through the GPIO driver.
 Stop DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void);

/*
 Description
 The Function responsible for control the motor direction.
 */

void DcMotor_Rotate(Motor_Dir direction, uint8 speed);

#endif /* MOTOR_H_ */

