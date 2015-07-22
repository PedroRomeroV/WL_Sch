/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %template.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid02495 %
* %date_created:    Fri Jan  9 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
 #include "Components.h"
/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/









void Indicator_Init(Indicatortype *MyIndicator)
{
	MyIndicator->LedUP=LED_GREEN;
	MyIndicator->LedDOWN=LED_BLUE;
}
void Indicator_SetUP(Indicatortype *MyIndicator)
{
Leds_ON(&MyIndicator->LedUP);
Leds_OFF(&MyIndicator->LedDOWN);
}
void Indicator_SetDOWN(Indicatortype *MyIndicator)
{
Leds_OFF(&MyIndicator->LedUP);
Leds_ON(&MyIndicator->LedDOWN);	
}
void IndicatorI_SetIDLE(Indicatortype *MyIndicator)
{
Leds_OFF(&MyIndicator->LedUP);
Leds_OFF(&MyIndicator->LedDOWN);
}

T_UBYTE Indicator_GetStatus(Indicatortype *MyIndicator)
{
	return 0;
}
	

 
void LEDBar_Init(BarType *MyBar)
{
BarType MyBar2 = 
{ 
{LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8,LED9},
 0, 400 
 };
*MyBar=MyBar2;
}

void LEDBar_UP_ONE(BarType *MyBar)
{
	Leds_ON(&MyBar->Leds[MyBar->Position] );
	MyBar->Position++;
}

void LEDBar_DOWN_ONE(BarType *MyBar)
{
MyBar->Position--;
Leds_OFF(&MyBar->Leds[MyBar->Position] );
}
void LEDBar_UP_ALL()
{
	
}
void LEDBar_DOWN_ALL()
{
	
}



