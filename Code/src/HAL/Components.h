/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %template.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      uid02495 %
* %date_created:    Fri Feb 28 13:41:01 2003 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  | SAR/SIF/SCN_xxx               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef COMPONENTS_H                               /* To avoid double inclusion */
#define COMPONENTS_H

/* Includes */
/* -------- */


 #include "Leds.h"  

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */


/* Functions macros */


/* Exported defines */



#define SIZELEDBAR   10

typedef enum
{
	STATE_UP,
	STATE_DOWN,
	STATE_IDLE,
	STATE_UP_AUTO,
	STATE_UP_MANUAL,
	STATE_DOWN_AUTO,
	STATE_DOWN_MANUAL,
	STATE_ANTIPINCH
}STATES_WL;

typedef  enum 
{
	LED0 = 34,
	LED1 = 35,
	LED2 = 36,
	LED3 = 37,
	LED4 = 38,
	LED5 = 39,
	LED6 = 40,
	LED7 = 41,
	LED8 = 42,
	LED9 = 44,
	LED_BLUE = 46,
	LED_GREEN = 47
}LEDBAR;


typedef struct
{
	LedType LedUP;
	LedType LedDOWN;
}Indicatortype;


typedef struct
{
LedType Leds[SIZELEDBAR];
T_UBYTE Position;
T_UBYTE speed;
}BarType;




void Indicator_Init(Indicatortype *MyIndicator);
void Indicator_SetUP(Indicatortype *MyIndicator);
void Indicator_SetDOWN(Indicatortype *MyIndicator);
void IndicatorI_SetIDLE(Indicatortype *MyIndicator);
T_UBYTE Indicator_GetStatus(Indicatortype *MyIndicator);
void LEDBar_Init(BarType *MyBar);
void LEDBar_UP_ONE(BarType *MyBar);
void LEDBar_DOWN_ONE(BarType *MyBar);
void LEDBar_UP_ALL();
void LEDBar_DOWN_ALL();


#endif


