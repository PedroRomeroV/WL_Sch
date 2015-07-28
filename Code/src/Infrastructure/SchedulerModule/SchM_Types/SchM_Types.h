/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        SchM_Types.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas 
* %date_created:    Wed Jul 15 09:15:01 2015 
*=============================================================================*/
/* DESCRIPTION : Typedefs for the Scheduler Struct                            */
/*============================================================================*/
/* FUNCTION COMMENT : contains only typedefes which are exported              */
/* to platform scheduler module.                                              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 15/07/2015  | SAR/SIF/SCN_xxx               | Pedro RV         */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef SCHMTYPES_H                               /* To avoid double inclusion */
#define SCHMTYPES_H

/* Includes */
/* -------- */
#include "typedefs.h"


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */

/* Pointer to function*/
typedef void (*TaskFunctionPtrType)(void);

/* Offset Type */
typedef T_UBYTE SchedulerTaskOffsetType; 

/* Masks*/
typedef enum
{
	SCHM_MASK_1MS	= 1,
	SCHM_MASK_2MS	= 3,
	SCHM_MASK_4MS	= 15,
	SCHM_MASK_8MS	= 31,
	SCHM_MASK_16MS	= 63,
	SCHM_MASK_32MS	= 127
}SchM_TaskMaskType;   
 
/* Tasks*/
typedef enum
{
	SCHM_TASKID_BKG,
	SCHM_TASKID_1MS,
	SCHM_TASKID_2MS,
	SCHM_TASKID_4MS,
	SCHM_TASKID_8MS,
	SCHM_TASKID_16MS,
	SCHM_TASKID_32MS	
}SchM_TaskIDType;

/* Tasks States*/
typedef enum
{
	SCHM_TASK_STATE_SUSPENDED,
	SCHM_TASK_STATE_READY,
	SCHM_TASK_STATE_RUNNING
}SchM_TaskStateType;

/* Scheduler States*/
typedef enum
{
	SCHEDULER_UNINIT,
	SCHEDULER_INIT,
	SCHEDULER_RUNNING,
	SCHEDULER_OVERLOAD,
	SCHEDULER_HALTED,
	SCHEDULER_IDLE
}SchM_SchedulerStateType;

/* Scheduler States*/
typedef enum
{
	SCHM_OFFSET_1MS	= 0,
	SCHM_OFFSET_2MS	= 1,
	SCHM_OFFSET_4MS	= 2,
	SCHM_OFFSET_8MS	= 3,
	SCHM_OFFSET_16MS= 5,
	SCHM_OFFSET_32MS	= 6
}SchM_TaskOffsetType;

/* TaskDescriptorType: Provides the table with the Offset, Mask, TaskID, Function */
typedef struct 
{

SchedulerTaskOffsetType SchedulerTaskOffset;
SchM_TaskMaskType SchedulerTaskMask;
SchM_TaskIDType SchedulerTaskID;
TaskFunctionPtrType TaskFunctionPtr;
	
}SchedulerTaskDescriptorType; 


/* SchedulerConfig: Contains the number of tasks and the Table to the tasks*/
typedef struct 
{
T_UBYTE SchedulerNumberOfTasks;
const SchedulerTaskDescriptorType *SchedulerTaskTable; 
}SchedulerConfigType;


/* TaskControl: Link the Function whit they respective state*/
typedef struct
{
	SchM_TaskStateType SchedulerTaskState;
	TaskFunctionPtrType TaskFunctionControlPtr;
	
}SchedulerTaskControlType; 

/* SchedulerControl: Contains the counter, the Scheduler State, The current task running */
typedef struct
{
	T_UBYTE Schedulercounter;
	SchM_TaskIDType SchedulerTaskRunning;
	SchM_SchedulerStateType  SchedulerStatus;
}SchedulerControlType;



/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */


/* Functions macros */


/* Exported defines */


#endif


