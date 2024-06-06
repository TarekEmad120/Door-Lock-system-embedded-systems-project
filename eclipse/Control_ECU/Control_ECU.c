/*
 * Control_ECU.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Tarek Emad
 */
#include<avr/io.h>
#include<util/delay.h>
#include"uart.h"
#include"Timer1.h"
#include"external_eeprom.h"
#include"Buzzer.h"
#include"motor.h"
#include"twi.h"
#include"Control_ECU_Macros.h"

#define password_location 0x0310/*start addressin eeprom*/

void timerTick(void);/*timer*/

void setPassword(void);
uint8 checkPassword(void);
void openDoor(void);

uint8 gtime;
Timer1_ConfigType timer_conifig;


int main(void){
    uint8 HMI_command;

    UART_ConfigType UART_ConfigType;
    UART_ConfigType.baud_rate=9600;
    UART_ConfigType.bit_data=EIGHT_BITS;
    UART_ConfigType.parity=DISABLED;
    UART_ConfigType.stop_bit=ONE_BIT;
    UART_init(&UART_ConfigType);

    TWI_ConfigType TWI_ConfigType;
    TWI_ConfigType.address=0x01;
    TWI_ConfigType.bit_rate=400;
    TWI_init(&TWI_ConfigType);

    timer_conifig.initial_value=0;
    timer_conifig.mode=COMPARE;
    timer_conifig.prescaler=CLK_1024;
    timer_conifig.compare_value=23437;
    Timer1_setCallBack(timerTick);
    
    Buzzer_Init();
    DcMotor_init();

    SREG|=(1<<7);
    UART_sendByte(readybyte);



    while(1){
        HMI_command=UART_recieveByte();

        switch (HMI_command)
        {
        case setpasswordcmd/* constant-expression */:
        	 setPassword();
            break;
        case cmppasswordcmd:
            if(checkPassword()== matchedpassword){

                HMI_command=UART_recieveByte();
                if(HMI_command==openDoorcmd){

                    openDoor();
                }
                else if (HMI_command==setpasswordcmd){
                    setPassword();
                }
            }
            else{

            }
            break;
        case Buzzeroff:
            Buzzer_off();
            UART_sendByte(buzzercheck);
            break;
        
        case Buzzeron:
            Buzzer_on();
            UART_sendByte(readybyte);
            break;
        
        default:
            break;
        }
    }


}

void timerTick(void){
    gtime--;
}

void setPassword(void){
    uint8 i;
    uint8 status;
    uint8 password[5];
    uint8 checkPassword[5];
    UART_sendByte(setready);
    for(i=0;i<5;i++){
        password[i]=UART_recieveByte();
        UART_sendByte(setready);

    }
    for(i=0;i<5;i++){
        checkPassword[i]=UART_recieveByte();
        UART_sendByte(setready);

    }

    status= matchedpassword;

    /*comapare password and check password*/
    for(i=0;i<5;i++){
        if(password[i]!=checkPassword[i]){
        	UART_sendByte(unmatchedpassword);
        	status =unmatchedpassword;
        	break;

        }
    }
    /*write password to eeprom*/
    if (status==matchedpassword){
    for(i=0;i<5;i++){
        EEPROM_writeByte(password_location+(3*i*8),password[i]);
        UART_sendByte(mem_alloc);
        _delay_ms(10);
    }

    UART_sendByte(matchedpassword);
    }

}

uint8 checkPassword(void){
    uint8 i;
    uint8 password[5];
    uint8 eeprompassdigit;

    UART_sendByte(readybyte);
    for(i=0;i<5;i++){
        password[i]=UART_recieveByte();
        UART_sendByte(setready);
    }
    /*checking password in EEPROM*/
    for(i=0;i<5;i++){
        EEPROM_readByte(password_location+(3*i*8),&eeprompassdigit);/*(3i*8) is where the memory stored */
        _delay_ms(10);
        if(password[i]!=eeprompassdigit){
        	 UART_sendByte(unmatchedpassword);
            return unmatchedpassword;
        }
    }
    UART_sendByte(matchedpassword);

    return matchedpassword;
}


void openDoor(void){

    gtime=11;/* the timer will give interrupt each 3 second so 11* 3= 33
                 in which 15 sec for locking , 15 sec for unlocking ,and 3 sec for open*/


    Timer1_init(&timer_conifig);
    DcMotor_Rotate(MOTOR_clockwise,100);
    UART_sendByte(openDoorcmd);
    while(gtime>6);/*unlocking*/


    DcMotor_Rotate(MOTOR_STOP,100);
    UART_sendByte(opened);
    while(gtime>5);/*open*/


    DcMotor_Rotate(MOTOR_anti_clockwise,100);
    UART_sendByte(locked);
    while(gtime>0);/*locking*/


    DcMotor_Rotate(MOTOR_STOP,100);
    UART_sendByte(readybyte);
    Timer1_deInit();
}



