/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        LEDBar.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri JUL 24  07:41:01 2015 
*=============================================================================*/
/* DESCRIPTION : Header file LEDBar Driver                                    */
/*============================================================================*/
/* FUNCTION COMMENT : contains  typedef T_LEDBAR_TYPE which are exported      */
/* and prototype of LEDBAR Functions                                          */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  | SAR/SIF/SCN_xxx               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef LEDBAR_H                               /* To avoid double inclusion */
#define LEDBAR_H

/* Includes */
/* -------- */


 #include "LED.h"  

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */

/* Exported defines */


#define SIZELEDBAR  (T_UBYTE)10

/* typedef */

typedef enum
{
	LED0 = (T_UBYTE)34,
	LED1 = (T_UBYTE)35,
	LED2 = (T_UBYTE)36,
	LED3 = (T_UBYTE)37,
	LED4 = (T_UBYTE)38,
	LED5 = (T_UBYTE)39,
	LED6 = (T_UBYTE)40,
	LED7 = (T_UBYTE)41,
	LED8 = (T_UBYTE)42,
	LED9 = (T_UBYTE)44
}E_LEDBAR_PORT;




typedef struct 
{
	T_UBYTE ub_Position;
	T_LED_TYPE at_LED[SIZELEDBAR];
}S_BAR_TYPE;



/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

void LEDBar_Init(S_BAR_TYPE *lps_Bar);
void LEDBar_UP_ONE(S_BAR_TYPE *lps_Bar);
void LEDBar_DOWN_ONE(S_BAR_TYPE *lps_Bar);








#endif


