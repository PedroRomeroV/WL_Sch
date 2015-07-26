
/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         SchM_Cfg.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas 
* %date_created:    Wed Jul 15 09:15:01 2015 
*=============================================================================*/
/* DESCRIPTION : C  Build the table                                           */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
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
#include "SchM_Cfg.h"
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


const SchedulerTaskDescriptorType SchedulerTaskTableConfig []=
{
	{	SCHM_OFFSET_1MS		,SCHM_MASK_1MS	,SCHM_TASKID_1MS	,SchM_Task_1MS	},
	{	SCHM_OFFSET_2MS		,SCHM_MASK_2MS	,SCHM_TASKID_2MS	,SchM_Task_2MS	},
	{	SCHM_OFFSET_4MS		,SCHM_MASK_4MS	,SCHM_TASKID_4MS	,SchM_Task_4MS	},
	{	SCHM_OFFSET_8MS		,SCHM_MASK_8MS	,SCHM_TASKID_8MS	,SchM_Task_8MS	},
	{	SCHM_OFFSET_16MS	,SCHM_MASK_16MS	,SCHM_TASKID_16MS	,SchM_Task_16MS	},
	{	SCHM_OFFSET_32MS	,SCHM_MASK_32MS	,SCHM_TASKID_32MS	,SchM_Task_32MS	} 

};

const SchedulerConfigType SchedulerConfig =
{
(sizeof(SchedulerTaskTableConfig)/sizeof(SchedulerTaskTableConfig[0])),
SchedulerTaskTableConfig	
};



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

