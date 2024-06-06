#ifndef CONTROL_ECU_MACROS_H
#define CONTROL_ECU_MACROS_H

/*******************************************************************************************
*                     this is the macros for control ECU                                   *
*                     in order to send/recieve bytes from and                              *
*                     to the control ECU  instead of strings                               *
********************************************************************************************/

#define openDoorcmd         0x59   /*this is for opening door*/
#define setpasswordcmd      0x60   /*this is for seting password in eeprom */
#define cmppasswordcmd      0x61   /*this is for comparing password */
#define Buzzeron            0x62   /*this is for turning on buzzer */
#define Buzzeroff           0x63   /*this is for turning off buzzer */
#define unmatchedpassword   0x64   /*this is for unmatched password */
#define matchedpassword     0x65   /*this is for matched password */
#define readybyte           0x66   /*this is for ready byte */
#define setready            0x68   /*start to set bit*/
#define mem_alloc           0x72   /*checking for memory allocation*/
#define opened              0x80   /*opened door*/
#define locked              0x81   /*locked door*/
#define buzzercheck         0x90   /*checking for buzzer status*/
#endif /* CONTROL_ECU_MACROS_H */
