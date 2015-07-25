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





extern const  T_LED_TYPE  at_LEDBAR_PORT[SIZELEDBAR]={LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8,LED9};

void Indicator_Init(S_INDICATOR_TYPE *Indicator)
{
	LED_Init(&Indicator->t_LED_UP,LED_GREEN);
	LED_Init(&Indicator->t_LED_DOWN,LED_BLUE);
}

void Indicator_SetUP(S_INDICATOR_TYPE *Indicator)
{
	LED_ON(&Indicator->t_LED_UP);
	LED_OFF(&Indicator->t_LED_DOWN);
}
void Indicator_SetDOWN(S_INDICATOR_TYPE *Indicator)
{
	LED_OFF(&Indicator->t_LED_UP);
	LED_ON(&Indicator->t_LED_DOWN);	
}
void Indicator_SetIDLE(S_INDICATOR_TYPE *Indicator)
{
	LED_OFF(&Indicator->t_LED_UP);
	LED_OFF(&Indicator->t_LED_DOWN);
}


	

 
void LEDBar_Init(S_BAR_TYPE *MyBar)
{

T_UBYTE pos=0;
for(pos=0;pos<SIZELEDBAR;pos++)
{
	LED_Init(&MyBar->at_LED[pos],at_LEDBAR_PORT[pos]);
}
MyBar->ub_Position=0;
}

void LEDBar_UP_ONE(S_BAR_TYPE *MyBar)
{
	LED_ON(&MyBar->at_LED[MyBar->ub_Position] );
	MyBar->ub_Position++;
}

void LEDBar_DOWN_ONE(S_BAR_TYPE *MyBar)
{
MyBar->ub_Position--;
LED_OFF(&MyBar->at_LED[MyBar->ub_Position] );
}
void LEDBar_UP_ALL()
{
	
}
void LEDBar_DOWN_ALL()
{
	
}



