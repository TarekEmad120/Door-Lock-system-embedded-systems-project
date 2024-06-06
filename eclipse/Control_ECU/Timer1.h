/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the Timer 1 driver
 *
 * Author: Tarek Emad
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include "avr/io.h"
#include "std_types.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                              Definations                                    *
 *******************************************************************************/
/*Modular configuration for Timer1 in Avr Atmega32*/
typedef enum
{
    NO_CLK,
    CLK_1,
    CLK_8,
    CLK_64,
    CLK_256,
    CLK_1024
} Timer1_Prescaler;

typedef enum
{
    NORMAL,
    COMPARE
} Timer1_Mode;

typedef struct
{
    uint16 initial_value;
    uint16 compare_value; // it will be used in compare mode only.
    Timer1_Prescaler prescaler;
    Timer1_Mode mode;
} Timer1_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer1_init(const Timer1_ConfigType *Config_Ptr);

void Timer1_deInit(void);

void Timer1_setCallBack(void (*a_ptr)(void));

#endif /* TIMER1_H_ */
