/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         LEDBar.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri Jul 24  14:38:03 2015 
*=============================================================================*/
/* DESCRIPTION : C source LED Driver                                          */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source from the LEDBAR driver */
/*                                                                            */
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
 #include "LEDBar.h"


/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */

extern const  T_LED_TYPE  cat_LEDBAR_PORT[SIZELEDBAR]={LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8,LED9};



/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 


/* Exported functions prototypes */
/* ----------------------------- */



/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LEDBar_Init
 *  Description          :	Initialize LEDBar
 *  Parameters           :  S_BAR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void LEDBar_Init(S_BAR_TYPE *lps_LEDBar)
{
	T_UBYTE ub_Position=0;
	for(ub_Position=0;ub_Position<SIZELEDBAR;ub_Position++)
	{
		LED_Init(&lps_LEDBar->at_LED[ub_Position],cat_LEDBAR_PORT[ub_Position]);
	}
	lps_LEDBar->ub_Position=0;
}

/**************************************************************
 *  Name                 :	LEDBar_UP_ONE
 *  Description          :	Turn on one LED
 *  Parameters           :  S_BAR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void LEDBar_UP_ONE(S_BAR_TYPE *lps_LEDBar)
{
	LED_ON(&lps_LEDBar->at_LED[lps_LEDBar->ub_Position] );
	lps_LEDBar->ub_Position++;
}


/**************************************************************
 *  Name                 :	LEDBar_DOWN_ONE
 *  Description          :	Turn of one led
 *  Parameters           :  S_BAR_TYPE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void LEDBar_DOWN_ONE(S_BAR_TYPE *lps_LEDBar)
{
	lps_LEDBar->ub_Position--;
	LED_OFF(&lps_LEDBar->at_LED[lps_LEDBar->ub_Position] );
}

