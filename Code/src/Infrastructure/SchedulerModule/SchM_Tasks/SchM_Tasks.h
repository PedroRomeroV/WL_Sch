/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        SchM_Tasks.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas 
* %date_created:    Wed Jul 15 09:15:01 2015 
*=============================================================================*/
/* DESCRIPTION : Functions that are executed in respective time               */
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

#ifndef SCHMTASKS_H                               /* To avoid double inclusion */
#define SCHMTASKS_H

/* Includes */
/* -------- */
#include "SchM_Cfg.h" 
#include "dummy.h"


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


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

void SchM_Task_1MS(void);
void SchM_Task_2MS(void);
void SchM_Task_4MS(void);
void SchM_Task_8MS(void);
void SchM_Task_16MS(void);
void SchM_Task_32MS(void);


/* Functions macros */


/* Exported defines */


#endif


