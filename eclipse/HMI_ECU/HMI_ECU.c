/*
 * HMI_ECU.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Tarek Emad
 */

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"
#include "lcd.h"
#include "Timer1.h"
#include "uart.h"
#include "Control_ECU_Macros.h"

void getPassword(uint8 *);
uint8 setPassword();
uint8 checkPassword();
void timerTick();
uint16 gtime;

int main()
{
	uint8 key;
	UART_ConfigType uartConfig;
	/* a variable to store Timer1 configuration */
	Timer1_ConfigType timerConfig;

	/* UART configuration and initialization */
	uartConfig.baud_rate = 9600;
	uartConfig.bit_data = EIGHT_BITS;
	uartConfig.parity = DISABLED;
	uartConfig.stop_bit = ONE_BIT;
	UART_init(&uartConfig);

	/* Timer1 configuration without initialization
	 * configured to give interrupt every 7.5 seconds */
	timerConfig.initial_value = 0;
	timerConfig.mode = COMPARE;
	timerConfig.compare_value = 58593;
	timerConfig.prescaler = CLK_1024;
	Timer1_setCallBack(timerTick);

	LCD_init();
	SREG |= (1 << 7);


	uint8 ready= UART_recieveByte();
	while(ready!=readybyte)
	{
		UART_sendByte(0x70);
		ready=UART_recieveByte();
	}
	/*setpassward for the first time*/
	while (setPassword() == unmatchedpassword)
		;

	while (1)
	{

		LCD_clearScreen();
		LCD_displayString("+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");

		do
		{
			key = KEYPAD_getPressedKey();
		}while(key != '+' && key != '-');

		if (checkPassword() == matchedpassword)
		{
			switch (key)
			{
			case '+':
				UART_sendByte(openDoorcmd);
				while( UART_recieveByte()!=openDoorcmd);
				LCD_clearScreen();
				LCD_displayString("    Door is");
				LCD_displayStringRowColumn(1,3,"unlocking");
				while( UART_recieveByte()!=opened);
				LCD_clearScreen();
				LCD_displayString("    Door is");
				LCD_displayStringRowColumn(1,5,"open");
				while( UART_recieveByte()!=locked);
				LCD_clearScreen();
				LCD_displayString("    Door is");
				LCD_displayStringRowColumn(1,4,"locking");
				while( UART_recieveByte()!=readybyte);
				break;

			case'-':
				while (setPassword() == unmatchedpassword);
				break;
			}
		}
		else
		{
			LCD_clearScreen();
			LCD_displayString("     Wrong Pass");
			LCD_displayStringRowColumn(1, 3, "Door is locked");
			UART_sendByte(Buzzeron);
			while(UART_recieveByte()!=readybyte);
			gtime = 8;
			Timer1_init(&timerConfig);
			while (gtime) ;
			Timer1_deInit();
			UART_sendByte(Buzzeroff);
			while(UART_recieveByte()!=buzzercheck);
		}
	}
}

void timerTick()
{
	gtime--;
}

void getPassword(uint8 *password)
{
	uint8 key;
	uint8 i;
	for (i = 0; i < 5; i++)
	{
		do
		{
			key = KEYPAD_getPressedKey();
		} while (key < 0 || key > 9);
		password[i] = key;
		LCD_displayCharacter('*');
		_delay_ms(500);
	}
	while (KEYPAD_getPressedKey() != '=')
		;
	_delay_ms(50);
}

uint8 setPassword()
{
	uint8 password[5];
	uint8 confirm_pass[5];
	uint8 i;
	LCD_clearScreen();
	LCD_displayString("plz-enter Pass:");
	LCD_moveCursor(1, 0);
	getPassword(password);
	LCD_clearScreen();
	LCD_displayString("plz-reenter the:");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass:");
	LCD_moveCursor(1,10);
	getPassword(confirm_pass);
	UART_sendByte(setpasswordcmd);
	UART_recieveByte();
	for (i = 0; i < 5; i++)
	{
		UART_sendByte(password[i]);
		UART_recieveByte();
	}
	for (i = 0; i < 5; i++)
	{
		UART_sendByte(confirm_pass[i]);
		UART_recieveByte();
	}

	return UART_recieveByte();
}

uint8 checkPassword()
{
	uint8 i, j;
	uint8 password[6];
	for (i = 0; i < 3; i++)
	{
		LCD_clearScreen();
		LCD_displayString("plz-enter Pass:");
		LCD_moveCursor(1, 0);
		UART_sendByte(cmppasswordcmd);
		UART_recieveByte();
		getPassword(password);

		for (j = 0; j < 5; j++)
		{
			UART_sendByte(password[j]);
			UART_recieveByte();
		}
		uint8 status=UART_recieveByte();
		while (status == setready){
			status=UART_recieveByte();
		}
		if(status==matchedpassword)
			return matchedpassword;
	}
	return unmatchedpassword;
}
