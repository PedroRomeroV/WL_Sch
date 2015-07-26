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





/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/

#define TIME_LED_TRANSITION					200
#define TIME_DELAY                          2500
#define TIME_VALIDATION_BUTTON_AUTO			10
#define TIME_VALIDATION_BUTTON_ANTIPINCH	9
#define TIME_VALIDATION_BUTTON_MANUAL		500
#define TIME_BUTTON_OVERFLOW 				TIME_VALIDATION_BUTTON_MANUAL + 50
#define FUNCTIONALITY_INVALID				0
#define FUNCTIONALITY_MANUAL				1
#define FUNCTIONALITY_AUTO					2
#define FUNCTIONALITY_ANTIPINCH				3



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


extern void WL_Init(void);
extern void WL_Read_1ms(void);
extern void WL_TimeValidation_1ms(void);
extern void WL_StateManager_2ms(void);
extern void WL_StateResponse_2ms(void);
static void WL_StateFCN_AutoDOWN(void);
static void WL_StateFCN_AutoUP(void);
static void WL_StateFCN_ManualDOWN(void);
static void WL_StateFCN_ManualUP(void);
static void WL_StateFCN_Antipinch(void);
static void WL_StateFCN_IDLE(void);
static void WL_StateFCN_Block(void);

#endif /* _DUMMY_H */

/*******************************************************************************/
