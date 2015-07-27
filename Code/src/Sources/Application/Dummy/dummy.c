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
#include "Button.h"
#include "Components.h"

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


S_BUTTON_TYPE s_ButtonUP;
S_BUTTON_TYPE s_ButtonDOWN;
S_BUTTON_TYPE s_ButtonANTIPINCH;
S_BAR_TYPE s_Bar_WL;
S_INDICATOR_TYPE s_Indicator; 
E_STATES_WL e_State;
E_STATES_WL e_PrevState;
S_BUTTON_TYPE *ps_Button;
T_UBYTE ub_Functionality;
T_UWORD uw_TimeCounter;



void WL_Init(void)
{
	e_State=STATE_IDLE;	
	Button_Init(&s_ButtonUP,BUTTON_UP);
	Button_Init(&s_ButtonDOWN,BUTTON_DOWN);
	Button_Init(&s_ButtonANTIPINCH,BUTTON_ANTIPINCH);
	LEDBar_Init(&s_Bar_WL);
	Indicator_Init(&s_Indicator);
	ub_Functionality = FUNCTIONALITY_INVALID;
	uw_TimeCounter=TIME_LED_TRANSITION;
}


void WL_Read_1MS(void)    //lee los puertos de entrada y incrementa sus contadores si son presionados , unico que asigna el puntero a boton
{
	if( (e_State != STATE_ANTIPINCH) &&
	(Button_GetStatus(&s_ButtonUP) ^ Button_GetStatus(&s_ButtonDOWN) ))
	{
		if(Button_GetStatus(&s_ButtonUP))
		{
			ps_Button= &s_ButtonUP;
		}
		if(Button_GetStatus(&s_ButtonDOWN))
		{
			ps_Button= &s_ButtonDOWN;
		}
		ps_Button->uw_ButtonTimeHigh++;
	}
	else
	{
		s_ButtonUP.uw_ButtonTimeHigh=0;
		s_ButtonDOWN.uw_ButtonTimeHigh=0;
	}
	if( e_State == STATE_UP_AUTO ||  e_State == STATE_UP_MANUAL )
	{
		if(Button_GetStatus(&s_ButtonANTIPINCH))
		{
			s_ButtonANTIPINCH.uw_ButtonTimeHigh++;
		}
		
	}
	else
	{
		s_ButtonANTIPINCH.uw_ButtonTimeHigh=0;
	}
}


void WL_TimeValidation_1MS(void)  
{

	if(	s_ButtonANTIPINCH.uw_ButtonTimeHigh > TIME_VALIDATION_BUTTON_ANTIPINCH) 
	{
		ub_Functionality = FUNCTIONALITY_ANTIPINCH;	
	}
	else
	{
		switch(ps_Button->uw_ButtonTimeHigh)
		{
		case TIME_VALIDATION_BUTTON_AUTO:
			ub_Functionality = FUNCTIONALITY_AUTO;	 
			break;
		case TIME_VALIDATION_BUTTON_MANUAL:
			ub_Functionality = FUNCTIONALITY_MANUAL; 
			break;
		default:
			if(ps_Button->uw_ButtonTimeHigh < TIME_VALIDATION_BUTTON_AUTO)
			{
				ub_Functionality=  FUNCTIONALITY_INVALID;
			}
			if(ps_Button->uw_ButtonTimeHigh > TIME_BUTTON_OVERFLOW)
			{
				ps_Button->uw_ButtonTimeHigh--;
			}
			else {}
		break;
		
		}
	}
}



void WL_StateManager_2MS(void)    //if valid button 
{
	e_PrevState=e_State;
	if(ub_Functionality == FUNCTIONALITY_AUTO )
	{
		if(e_State == STATE_IDLE  )  
		{
			if(	ps_Button->ub_ButtonID == BUTTON_UP)
			{
				e_State=STATE_UP_AUTO;
			}
			else if(ps_Button->ub_ButtonID == BUTTON_DOWN)
			{
				e_State=STATE_DOWN_AUTO;
			}
		}
		else
		{
			e_State=STATE_BLOCK;
		}
		ub_Functionality=  FUNCTIONALITY_INVALID;
	}
	if(	ub_Functionality  == FUNCTIONALITY_MANUAL  )
	{
		if(e_State == STATE_UP_AUTO  ||  e_State == STATE_DOWN_AUTO )
		{
			if(	ps_Button->ub_ButtonID == BUTTON_UP)
			{
				e_State=STATE_UP_MANUAL;
			}
			else if(ps_Button->ub_ButtonID == BUTTON_DOWN)
			{
				e_State=STATE_DOWN_MANUAL;
			}
		}
		ub_Functionality=  FUNCTIONALITY_INVALID;
	}
	if( ub_Functionality == FUNCTIONALITY_ANTIPINCH  )
	{
		if(e_State == STATE_UP_AUTO || e_State == STATE_UP_MANUAL)
		{
			e_State=STATE_ANTIPINCH;
		}
		ub_Functionality=  FUNCTIONALITY_INVALID;
	}	
}



void WL_StateResponse_2MS(void)
{
	switch(e_State)
	{
		case STATE_BLOCK:
			WL_StateFCN_Block();
			break;
		case STATE_IDLE:
			WL_StateFCN_IDLE();
			break;
		case STATE_ANTIPINCH:
			WL_StateFCN_Antipinch();
			break;
		case STATE_UP_AUTO:
			WL_StateFCN_AutoUP();
			break;
		case STATE_UP_MANUAL:
			WL_StateFCN_ManualUP();
			break;
		case STATE_DOWN_AUTO:
			WL_StateFCN_AutoDOWN();
			break;
		case STATE_DOWN_MANUAL:
			WL_StateFCN_ManualDOWN();
			break;
		default:
			break;
		
	}
}








void WL_StateFCN_IDLE(void)
{
	uw_TimeCounter=TIME_LED_TRANSITION;
	Indicator_SetIDLE(&s_Indicator);
}


void WL_StateFCN_Antipinch(void)
{
	if(s_Bar_WL.ub_Position!=0)
	{
		if(uw_TimeCounter  == TIME_LED_TRANSITION )
		{
			LEDBar_DOWN_ONE(&s_Bar_WL);
			uw_TimeCounter=0;
		}
		uw_TimeCounter++;	
		Indicator_SetDOWN(&s_Indicator);	
	}
	else
	{
		static T_UWORD ruw_TimeDelay=0;
		if(TIME_DELAY ==  ruw_TimeDelay)
		{
			e_State = STATE_IDLE;
			ruw_TimeDelay=0;
		}
		ruw_TimeDelay++;
		Indicator_SetIDLE(&s_Indicator);
	}
	
}

void WL_StateFCN_Block(void)
{
	if(!Button_GetStatus(ps_Button))
	{
		e_State = STATE_IDLE;
	}		
	Indicator_SetIDLE(&s_Indicator);
}


void WL_StateFCN_AutoUP(void)
{
	if(s_Bar_WL.ub_Position!=SIZELEDBAR)
	{
		if(uw_TimeCounter  == TIME_LED_TRANSITION )
		{
			LEDBar_UP_ONE(&s_Bar_WL);
			uw_TimeCounter=0;
		}
		uw_TimeCounter++;
		Indicator_SetUP(&s_Indicator);			
	}
	else
	{
		e_State = STATE_IDLE;
	}
}


void WL_StateFCN_AutoDOWN(void)
{
	if(s_Bar_WL.ub_Position!=0)
	{
		if(uw_TimeCounter  == TIME_LED_TRANSITION )
		{
			LEDBar_DOWN_ONE(&s_Bar_WL);
			uw_TimeCounter=0;
		}
		uw_TimeCounter++;
		Indicator_SetDOWN(&s_Indicator);			
	}
	else
	{
		e_State = STATE_IDLE;
	}
}

void WL_StateFCN_ManualDOWN(void)
{
	if(s_Bar_WL.ub_Position!=0    &&  Button_GetStatus(&s_ButtonDOWN) )
	{
		if(uw_TimeCounter  == TIME_LED_TRANSITION )
		{
			LEDBar_DOWN_ONE(&s_Bar_WL);
			uw_TimeCounter=0;
		}
		uw_TimeCounter++;
		Indicator_SetDOWN(&s_Indicator);			
	}
	else
	{
		e_State = STATE_IDLE;
	}		
}

void WL_StateFCN_ManualUP(void)
{
	if(s_Bar_WL.ub_Position!=SIZELEDBAR    &&  Button_GetStatus(&s_ButtonUP) )
	{
		if(uw_TimeCounter  == TIME_LED_TRANSITION )
		{
			
			LEDBar_UP_ONE(&s_Bar_WL);
			uw_TimeCounter=0;
		}
		uw_TimeCounter++;	
		Indicator_SetUP(&s_Indicator);		
	}
	else
	{
		e_State = STATE_IDLE;
	}
}






