/*******************************************************************************/
/**
\file       dummy.c
\brief      Dummy Functions
\author     Francisco Martinez
\version    1.0
\date       04/04/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
//#include "typedefs.h"

/** Own headers */
#include "dummy.h"

/* GPIO routines prototypes */ 
//#include "GPIO.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Turn a combination of 4 LEDs with a unique blinking pattern, this funcation shall be 
* \brief    called periodically to operate. 
* \author   Francisco Martinez
* \return   void
*/


ButtonType MyButtonUP;
ButtonType MyButtonDOWN;
ButtonType MyButtonANTIPINCH;
BarType MyBar_WL;
Indicatortype MyIndicator; 
STATES_WL MyStatus;
ButtonType *PtrButton;
void Init_WL(void)
{
MyStatus=STATE_IDLE;
Button_Init(&MyButtonUP);
Button_Init(&MyButtonDOWN);
Button_Init(&MyButtonANTIPINCH);
LEDBar_Init(&MyBar_WL);
Indicator_Init(&MyIndicator);

}


void Read(void)
{
	if( (MyStatus != STATE_ANTIPINCH) &&
	(Button_GetButtonStatus(&MyButtonUP) ^ Button_GetButtonStatus(&MyButtonDOWN) ))
	{
		if(Button_GetButtonStatus(&MyButtonUP))
		{
			PtrButton= &MyButtonUP;
		}
		if(Button_GetButtonStatus(&MyButtonDOWN))
		{
			PtrButton= &MyButtonDOWN;
		}
		PtrButton->ButtonTimeHigh++;
	}
	else if( MyStatus == STATE_UP_AUTO ||  MyStatus == STATE_UP_MANUAL )
	{
		if(Button_GetButtonStatus(&MyButtonANTIPINCH))
		{
			MyButtonANTIPINCH.ButtonTimeHigh++;
		}
		
	}
	else
	{
	MyButtonUP.ButtonTimeHigh=0;
	MyButtonDOWN.ButtonTimeHigh=0;
	MyButtonANTIPINCH.ButtonTimeHigh=0;
	}

}



void Eval(void)
{
	if(	PtrButton->ButtonTimeHigh  > 10  )
	{
		if(	PtrButton->ButtonID == BUTTON_UP)
		{
			MyStatus=STATE_UP_MANUAL;
		}
		else if(PtrButton->ButtonID == BUTTON_DOWN)
		{
			MyStatus=STATE_DOWN_MANUAL;
		}
	
		
	}
	
}
