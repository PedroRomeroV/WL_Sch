/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        Indicator.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri JUL 24  07:41:01 2015 
*=============================================================================*/
/* DESCRIPTION : Header file LED Driver                                       */
/*============================================================================*/
/* FUNCTION COMMENT : contains  typedef T_INDICATOR_TYPE which are exported   */
/* and prototype of Indicator Functions                                       */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  | SAR/SIF/SCN_xxx               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef INDICATOR_H                               /* To avoid double inclusion */
#define INDICATOR_H

/* Includes */
/* -------- */


 #include "LED.h"  

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


typedef struct
{
	T_LED_TYPE t_LED_UP;
	T_LED_TYPE t_LED_DOWN;
}S_INDICATOR_TYPE;




/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

void Indicator_Init(S_INDICATOR_TYPE *lps_Indicator);
void Indicator_SetUP(S_INDICATOR_TYPE *lps_Indicator);
void Indicator_SetDOWN(S_INDICATOR_TYPE *lps_Indicator);
void Indicator_SetIDLE(S_INDICATOR_TYPE *lps_Indicator);



/* Exported defines */

#define  LED_GREEN  (T_UBYTE)46
#define  LED_BLUE   (T_UBYTE)47







#endif


