/*******************************************************************************/
/**
\file       dummy.h
\brief      Dummy Functions
\author     Francisco Martinez
\version    1.0
\date       04/04/2014
*/
/*******************************************************************************/

#ifndef _DUMMY_H        /*prevent duplicated includes*/
#define _DUMMY_H

/*-- Includes ----------------------------------------------------------------*/

/** Core modules */
/** Variable types and common definitions */

#include "Components.h"
#include "Button.h"


/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/

#define LED_TRANSITION_TIME					255
#define BUTTON_AUTO_TIME					10
#define BUTTON_MANUAL_TIME 	                500
#define BUTTON_OVERFLOW_TIME 				BUTTON_MANUAL_TIME +50
#define FUNCTIONALITY_INVALID				0
#define FUNCTIONALITY_MANUAL				1
#define FUNCTIONALITY_AUTO					2
#define FUNCTIONALITY_ANTIPINCH				3
#define DELAY_TIME                          1000



void Init_WL(void);
void Read(void);
void WL_StateFCN_AutoDOWN(void);
void WL_StateFCN_AutoUP(void);
void WL_StateFCN_ManualDOWN(void);
void WL_StateFCN_ManualUP(void);
void WL_StateFCN_Antipinch(void);
void WL_StateFCN_IDLE(void);
void WL_StateFCN_Block(void);


#endif /* _DUMMY_H */

/*******************************************************************************/
