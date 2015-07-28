/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        WindowLifter.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri JUL 24  07:41:01 2015 
*=============================================================================*/
/* DESCRIPTION : Header file Window Lifter contais all the functionaliy       */
/*============================================================================*/
/* FUNCTION COMMENT : contains functions which are exported to the scheduler  */
/* task to acomplish the simlation of a windows                               */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  | SAR/SIF/SCN_xxx               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef WL_H                               /* To avoid double inclusion */
#define WL_H

/* Includes */
/* -------- */


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


typedef enum
{
	STATE_IDLE,
	STATE_UP_AUTO,
	STATE_UP_MANUAL,
	STATE_DOWN_AUTO,
	STATE_DOWN_MANUAL,
	STATE_ANTIPINCH,
	STATE_BLOCK
}E_STATES_WL;


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */


extern void WL_Init(void);
extern void WL_Read_1MS(void);
extern void WL_TimeValidation_1MS(void);
extern void WL_StateManager_2MS(void);
extern void WL_StateResponse_2MS(void);
static void WL_StateFCN_AutoDOWN(void);
static void WL_StateFCN_AutoUP(void);
static void WL_StateFCN_ManualDOWN(void);
static void WL_StateFCN_ManualUP(void);
static void WL_StateFCN_Antipinch(void);
static void WL_StateFCN_IDLE(void);
static void WL_StateFCN_Block(void);




/* Exported defines */

#define TIME_LED_TRANSITION					200
#define TIME_DELAY                          2500
#define TIME_VALIDATION_BUTTON_AUTO			10
#define TIME_VALIDATION_BUTTON_ANTIPINCH	10
#define TIME_VALIDATION_BUTTON_MANUAL		500
#define TIME_BUTTON_OVERFLOW 				(TIME_VALIDATION_BUTTON_MANUAL + 50)

#define FUNCTIONALITY_INVALID				0
#define FUNCTIONALITY_MANUAL				1
#define FUNCTIONALITY_AUTO					2
#define FUNCTIONALITY_ANTIPINCH				3

#define OPEN                                0
#define CLOSE								10

#endif












