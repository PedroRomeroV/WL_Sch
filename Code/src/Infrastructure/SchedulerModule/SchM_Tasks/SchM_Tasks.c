
/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         SchM_Tasks.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas 
* %date_created:    Wed Jul 15 09:15:01 2015 
*=============================================================================*/
/* DESCRIPTION : C  Functions that are executed in respective time            */
/*============================================================================*/
/* FUNCTION COMMENT : contains only functions which are called every          */
/* certain time by the scheduler module.                                      */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 15/07/2015  | SAR/SIF/SCN_xxx               | Pedro RV         */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "SchM_Tasks.h"

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
 *  Name                 : SchM_Task_3P125MS
 *  Description          : Called every 3.125ms
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/
void SchM_Task_3P125MS(void)
{

	static T_UBYTE rub_Init=1;
	if(rub_Init)
	{
		WL_Init();
		rub_Init=0;	
	}
	else
	{
		WL_Read_1ms();
		WL_TimeValidation_1ms();	
	}



}

/**************************************************************
 *  Name                 : SchM_Task_6P25MS
 *  Description          : Called every 6.25ms
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/
 void SchM_Task_6P25MS(void)
{

	WL_StateManager_2ms();
	WL_StateResponse_2ms();

}

/*************************************************************
 *  Name                 : SchM_Task_12P5MS
 *  Description          : Called every 12.5ms
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/
 void SchM_Task_12P5MS(void)
{

	
}

/**************************************************************
 *  Name                 : SchM_Task_25MS
 *  Description          : Called every 25ms
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/
void SchM_Task_25MS(void)
{
	
}

/**************************************************************
 *  Name                 : SchM_Task_50MS
 *  Description          : Called every 50ms
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/
 void SchM_Task_50MS(void)
{
		
}

/**************************************************************
 *  Name                 : SchM_Task_100MS
 *  Description          : Called every 100ms
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/
 void SchM_Task_100MS(void)
{


}
 

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/







