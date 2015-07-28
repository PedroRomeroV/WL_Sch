/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         Indicator.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri Jul 24  14:38:03 2015 
*=============================================================================*/
/* DESCRIPTION : C source Indicator Driver                                    */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source from the Indicator     */
/* driver                                                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  |                               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
 #include "Indicator.h"



/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 


/* Exported functions prototypes */
/* ----------------------------- */



/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Indicator_Init
 *  Description          : Initilize an Indicator
 *  Parameters           :	S_INDICATOR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void Indicator_Init(S_INDICATOR_TYPE *lps_Indicator)
{
	LED_Init(&lps_Indicator->t_LED_UP,LED_GREEN);
	LED_Init(&lps_Indicator->t_LED_DOWN,LED_BLUE);
}


/**************************************************************
 *  Name                 :	Indicator_SetUP
 *  Description          :	Turn on the led that indicates UP movement and turn off the other one
 *  Parameters           :  S_INDICATOR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void Indicator_SetUP(S_INDICATOR_TYPE *lps_Indicator)
{
	LED_ON(&lps_Indicator->t_LED_UP);
	LED_OFF(&lps_Indicator->t_LED_DOWN);
}

/**************************************************************
 *  Name                 :	Indicator_SetDOWN
 *  Description          :	Turn on the led that indicates DOWN movement and turn off the other one
 *  Parameters           :  S_INDICATOR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void Indicator_SetDOWN(S_INDICATOR_TYPE *lps_Indicator)
{
	LED_OFF(&lps_Indicator->t_LED_UP);
	LED_ON(&lps_Indicator->t_LED_DOWN);	
}

/**************************************************************
 *  Name                 :	Indicator_SetIDLE
 *  Description          :	Turn off both LEDs
 *  Parameters           :  S_INDICATOR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void Indicator_SetIDLE(S_INDICATOR_TYPE *lps_Indicator)
{
	LED_OFF(&lps_Indicator->t_LED_UP);
	LED_OFF(&lps_Indicator->t_LED_DOWN);
}


	
