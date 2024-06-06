/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: motor.c
 *
 * Author: Tarek Emad
 *
 *******************************************************************************/

/*******************************************************************************
                        Includes
 *******************************************************************************/
#include"motor.h"
#include"gpio.h"
#include"common_macros.h"
#include"pwm.h"
#include"avr/io.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void DcMotor_init(void){

	GPIO_setupPinDirection(MOTOR_PORT_OUT,MOTOR_PIN_ID0,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_OUT,MOTOR_PIN_ID1,PIN_OUTPUT);

	GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID0,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID1,LOGIC_LOW);

}

void DcMotor_Rotate( Motor_Dir direction,uint8 speed){
	/*equation to calculate the duty cycle of a certain speed
   50  -> 128
 speed -> pwm
 then : pwm = ((speed*128)/50)-1 ### (-1) as the highest value is 255
	 */
	uint8 pwm;
	pwm=((speed*128)/50)-1;



	switch(direction){
	case MOTOR_STOP:
		GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID0,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID1,LOGIC_LOW);
		break;
	case MOTOR_clockwise:
		GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID0,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID1,LOGIC_LOW);
		Timer0_PWM_Init(pwm);
		break;
	case MOTOR_anti_clockwise:
		GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID0,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_OUT,MOTOR_PIN_ID1,LOGIC_HIGH);
		Timer0_PWM_Init(pwm);
		break;
	default:
		break;
	}
}
