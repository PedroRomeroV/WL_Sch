
/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         SchM.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas 
* %date_created:    Wed Jul 15 09:15:01 2015 
*=============================================================================*/
/* DESCRIPTION : C  Contain the functions that control the scheduler          */
/*============================================================================*/
/* FUNCTION COMMENT : contains function that initialize start stop            */
/* the scheduler module.                                                      */
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

SchedulerControlType rt_SchedulerControl;
SchedulerTaskControlType* rpt_SchedulerTaskControl;
const SchedulerConfigType * cpt_SchedulerConfig;  


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
 *  Name                 : SchM_OsTick
 *  Description          :	this shall be indirect called by the PIT, increment the counter and set the correspondig task state to ready
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
void SchM_OsTick(void)
{	
	T_UBYTE lub_count=0;
	rt_SchedulerControl.Schedulercounter++;
	for(lub_count=0;lub_count< cpt_SchedulerConfig->SchedulerNumberOfTasks  ;lub_count++)
	{
		if((cpt_SchedulerConfig->SchedulerTaskTable[lub_count].SchedulerTaskMask & rt_SchedulerControl.Schedulercounter )
		 == cpt_SchedulerConfig->SchedulerTaskTable[lub_count].SchedulerTaskOffset )
		{
			rpt_SchedulerTaskControl[lub_count].SchedulerTaskState = SCHM_TASK_STATE_READY;
		}
		else{/*Do nothing*/}
	}
}


/**************************************************************
 *  Name                 : SchM_Background
 *  Description          :	this function shall execute an infinite loop and search for all the task to be ready and execute.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :   No
 **************************************************************/
void SchM_Background(void)
{
	T_SBYTE lub_count=0;
	do
	{
		if(rpt_SchedulerTaskControl[lub_count].SchedulerTaskState == SCHM_TASK_STATE_READY)
		{
			rt_SchedulerControl.SchedulerStatus =	SCHEDULER_RUNNING;
	 		rpt_SchedulerTaskControl[lub_count].SchedulerTaskState = SCHM_TASK_STATE_RUNNING;
			rpt_SchedulerTaskControl[lub_count].TaskFunctionControlPtr();
	    	rpt_SchedulerTaskControl[lub_count].SchedulerTaskState = SCHM_TASK_STATE_SUSPENDED;
	    	rt_SchedulerControl.SchedulerStatus=	SCHEDULER_IDLE;
		}
		else{/*Do nothing*/}
		lub_count++;
		if(lub_count== cpt_SchedulerConfig->SchedulerNumberOfTasks )
		{
			lub_count=0;	
		}
		else{/*Do nothing*/}
	}while(1);
}



/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Init
 *  Description          :	Initialize all task in suspended, all the resources , the PIT and the sheduler status in INIT
 *  Parameters           :  [const SchedulerConfigType]
 *  Return               :	void
 *  Critical/explanation :   No
 **************************************************************/

void SchM_Init(const SchedulerConfigType * SchM_Config)
{
	T_UBYTE lub_count=0;
	rpt_SchedulerTaskControl = (SchedulerTaskControlType*)MemAlloc(sizeof(rpt_SchedulerTaskControl)*SchM_Config->SchedulerNumberOfTasks);
	cpt_SchedulerConfig = SchM_Config;
	for(lub_count=0;lub_count < SchM_Config->SchedulerNumberOfTasks;lub_count++)
	{
		rpt_SchedulerTaskControl[lub_count].TaskFunctionControlPtr = (SchM_Config->SchedulerTaskTable+lub_count)->TaskFunctionPtr;
		rpt_SchedulerTaskControl[lub_count].SchedulerTaskState = SCHM_TASK_STATE_SUSPENDED;
	}
	rt_SchedulerControl.SchedulerStatus=SCHEDULER_INIT;
	rt_SchedulerControl.Schedulercounter=0;
	PIT_device_init(); 
	PIT_channel_configure(PIT_CHANNEL_0, SchM_OsTick); 	

}


/**************************************************************
 *  Name                 :	SchM_Stop
 *  Description          :	Stop PIT and set the scheduler status in HALTED
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :   No
 **************************************************************/
void SchM_Stop(void)
{
	PIT_channel_stop(PIT_CHANNEL_0);	
	rt_SchedulerControl.SchedulerStatus=SCHEDULER_HALTED;
}


/**************************************************************
 *  Name                 :	SchM_Start
 *  Description          :	Start the PIT, Set the scheduler status in IDLE and start SchM_Background function
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :   No
 **************************************************************/

 void SchM_Start(void)
{
	PIT_channel_start(PIT_CHANNEL_0);
	rt_SchedulerControl.SchedulerStatus=	SCHEDULER_IDLE;
	SchM_Background();
}





