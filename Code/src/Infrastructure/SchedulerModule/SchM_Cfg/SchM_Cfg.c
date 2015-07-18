
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
	{	SCHM_OFFSET_3P125MS	,SCHM_MASK_3P125MS	,SCHM_TASKID_3P125MS	,SchM_Task_3P125MS	},
	{	SCHM_OFFSET_6P25MS	,SCHM_MASK_6P25MS	,SCHM_TASKID_6P25MS		,SchM_Task_6P25MS	},
	{	SCHM_OFFSET_12P5MS	,SCHM_MASK_12P5MS	,SCHM_TASKID_12P5MS		,SchM_Task_12P5MS	},
	{	SCHM_OFFSET_25MSS	,SCHM_MASK_25MS		,SCHM_TASKID_25MS		,SchM_Task_25MS		},
	{	SCHM_OFFSET_50MS	,SCHM_MASK_50MS		,SCHM_TASKID_50MS		,SchM_Task_50MS		},
	{	SCHM_OFFSET_100MS	,SCHM_MASK_100MS	,SCHM_TASKID_100MS		,SchM_Task_100MS	} 

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

