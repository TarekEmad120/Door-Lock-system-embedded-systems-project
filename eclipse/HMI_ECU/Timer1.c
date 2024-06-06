/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.c
 *
 * Description: Source file for the Timer 1 driver
 *
 * Author: Tarek Emad
 *
 *******************************************************************************/
#include "common_macros.h"
#include "avr/io.h"
#include "Timer1.h"
#include "std_types.h"
/******************************************************************************************
*                                   Function Defination                                   *
*******************************************************************************************/
 static void(*Timer1_callBackPtr)(void);

ISR(TIMER1_COMPA_vect)
{
    (*Timer1_callBackPtr)();
}

ISR(TIMER1_COMPB_vect)
{
    (*Timer1_callBackPtr)();
}
/* ISR for overflow interrupt */
ISR(TIMER1_OVF_vect)
{
    (*Timer1_callBackPtr)();
}

void Timer1_init(const Timer1_ConfigType *Config_Ptr)
{
    /*Timer1 initialization*/
    TCNT1 = Config_Ptr->initial_value;
    OCR1A = Config_Ptr->compare_value;
    if (Config_Ptr->mode == COMPARE)
    {
        TIMSK |= (1 << OCIE1A); // enable compare interrupt
    }
    else
    {
        TIMSK |= (1 << TOIE1); // enable overflow interrupt}
    }
    TCCR1A = (1 << FOC1A) | (1 << FOC1B);
    TCCR1B= Config_Ptr->prescaler | (Config_Ptr->mode<<WGM12);
}

void Timer1_deInit(void)
{
    /*Timer1 de-initialization*/
    TCNT1 = 0;
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK &= ~(1 << OCIE1A);
    TIMSK &= ~(1 << TOIE1);
}

void Timer1_setCallBack(void (*a_ptr)(void))
{
    /*Timer1 set callback*/
    Timer1_callBackPtr = a_ptr;
}


