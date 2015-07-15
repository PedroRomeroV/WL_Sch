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
#include "SchM.h"
#include "PIT.h"
#include "MemAlloc.h"

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
SchedulerControlType SchedulerControl;
SchedulerTaskControlType SchedulerTaskControl[6];


void SchM_Init(const SchedulerConfigType * SchM_Config)
{
T_UBYTE lub_count=0;
for(lub_count=0;lub_count < SchM_Config->SchedulerNumberOfTasks;lub_count++)
{
	SchedulerTaskControl[lub_count].TaskFunctionControlPtr = (SchM_Config->SchedulerTaskTable+lub_count)->TaskFunctionPtr;
	SchedulerTaskControl[lub_count].SchedulerTaskState = TASK_STATE_SUSPENDED;
}
	SchedulerControl.SchedulerStatus=SCHEDULER_INIT;
	SchedulerControl.Schedulercounter=0;
	PIT_device_init(); 
	PIT_channel_configure(PIT_CHANNEL_0, SchM_OsTick); 	

}


void SchM_Stop(void)
{
	PIT_channel_stop(PIT_CHANNEL_0);	
	SchedulerControl.SchedulerStatus=SCHEDULER_HALTED;
}



 void SchM_Start(void)
{
	PIT_channel_start(PIT_CHANNEL_0);
	SchedulerControl.SchedulerStatus=	SCHEDULER_UNINIT;
	SchM_Background();
}





void SchM_OsTick(void)
{

SchedulerControl.Schedulercounter++;

	if( (MASK_3P125MS  & SchedulerControl.Schedulercounter )  == 0   )
	{
		SchedulerTaskControl[0].SchedulerTaskState = 	TASK_STATE_READY;
	}
	if( (MASK_6P25MS  & SchedulerControl.Schedulercounter)  == 1  )
	{
		SchedulerTaskControl[1].SchedulerTaskState = 	TASK_STATE_READY;
	}
	if( ( MASK_12P5MS  & SchedulerControl.Schedulercounter )  == 2  )
	{
		SchedulerTaskControl[2].SchedulerTaskState = 	TASK_STATE_READY;
	}
	if( (MASK_25MS & SchedulerControl.Schedulercounter )  == 3  )
	{
		SchedulerTaskControl[3].SchedulerTaskState = 	TASK_STATE_READY;
	}
	if( (MASK_50MS & SchedulerControl.Schedulercounter )  == 5  )
	{
		SchedulerTaskControl[4].SchedulerTaskState = 	TASK_STATE_READY;
	}
	if( (MASK_100MS & SchedulerControl.Schedulercounter)  == 6   )
	{
		SchedulerTaskControl[5].SchedulerTaskState = TASK_STATE_READY;
	
	}

}

void SchM_Background(void)
{

	T_SBYTE lsb_count=0;
for(lsb_count=0;;lsb_count++)
{

	if(SchedulerTaskControl[lsb_count].SchedulerTaskState == TASK_STATE_READY)
	{
		SchedulerControl.SchedulerStatus =	SCHEDULER_RUNNING;
	 	SchedulerTaskControl[lsb_count].SchedulerTaskState = TASK_STATE_RUNNING;
		SchedulerTaskControl[lsb_count].TaskFunctionControlPtr();
	    SchedulerTaskControl[lsb_count].SchedulerTaskState = TASK_STATE_SUSPENDED;
	    SchedulerControl.SchedulerStatus=	SCHEDULER_UNINIT;
	}
	if(lsb_count==6-1)
	lsb_count=-1;
	
}
	
}
