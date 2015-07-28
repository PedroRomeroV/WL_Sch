/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         WindowLifter.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri Jul 24  14:38:03 2015 
*=============================================================================*/
/* DESCRIPTION : C source Window Lifter                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source from the Window Lifter */
/*Contains function of reading and validation and the state machine           */
/*also contain private functions that response to a diferent state            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  |                               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/
/* Includes */
/* -------- */

#include "WindowLifter.h"
#include "Button.h"
#include "Indicator.h"
#include "LEDBar.h"



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

T_UBYTE ub_Functionality;

/* WORD RAM variables */

T_UWORD uw_TimeCounter;


/* LONG and STRUCTURE RAM variables */

S_BUTTON_TYPE s_ButtonUP;
S_BUTTON_TYPE s_ButtonDOWN;
S_BUTTON_TYPE s_ButtonANTIPINCH;
S_BAR_TYPE s_Bar_WL;
S_INDICATOR_TYPE s_Indicator; 
E_STATES_WL e_State;
S_BUTTON_TYPE *ps_Button;




/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 



/* Private functions prototypes */
/* ---------------------------- */


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	WL_Init
 *  Description          : Initialize all variables used for this control 
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :	No
 **************************************************************/
void WL_Init(void)
{
	e_State=STATE_IDLE;	
	Button_Init(&s_ButtonUP,BUTTON_UP);
	Button_Init(&s_ButtonDOWN,BUTTON_DOWN);
	Button_Init(&s_ButtonANTIPINCH,BUTTON_ANTIPINCH);
	LEDBar_Init(&s_Bar_WL);
	Indicator_Init(&s_Indicator);
	ub_Functionality = FUNCTIONALITY_INVALID;
	uw_TimeCounter=0;
}


/**************************************************************
 *  Name                 :	WL_Read_1MS
 *  Description          :	This function recive all the input signals and incremnt the counter of the time in high
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  executed every 1MS
 **************************************************************/

void WL_Read_1MS(void)    
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
		if(	Button_GetStatus(&s_ButtonUP) && Button_GetStatus(&s_ButtonDOWN) )
		{
			e_State = STATE_IDLE;
		}
	}
	if( (e_State == STATE_UP_AUTO) ||  (e_State == STATE_UP_MANUAL ) ) 
	{
		if(Button_GetStatus(&s_ButtonANTIPINCH))
		{
			s_ButtonANTIPINCH.uw_ButtonTimeHigh++;
		}
		else
		{
			s_ButtonANTIPINCH.uw_ButtonTimeHigh=0;
		}
		
	}
	else
		{
			s_ButtonANTIPINCH.uw_ButtonTimeHigh=0;
		}

}


/**************************************************************
 *  Name                 :	WL_TimeValidation_1MS
 *  Description          :	Validates that certain amount of time is reached and active a functionality
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :  executed every 1MS
 **************************************************************/
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
			else {}
			if(ps_Button->uw_ButtonTimeHigh > TIME_BUTTON_OVERFLOW)
			{
				ps_Button->uw_ButtonTimeHigh--;
			}
			else {}
			break;
		
		}
	}
}




/**************************************************************
 *  Name                 :	WL_StateManager_2MS
 *  Description          :	Set the state of the machine depending on the time validation and the state
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    executed every 2MS
 **************************************************************/
 

void WL_StateManager_2MS(void)   
{
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

 


/**************************************************************
 *  Name                 :	WL_StateResponse_2MS
 *  Description          :	Call the function that response to certain state
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  executed every 2MS
 **************************************************************/
 

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


  

/* Exported functions prototypes */
/* ----------------------------- */



/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : WL_StateFCN_IDLE
 *  Description          :	Turn of Indicator
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/

void WL_StateFCN_IDLE(void)
{
/*	uw_TimeCounter=TIME_LED_TRANSITION; */
	Indicator_SetIDLE(&s_Indicator);
}


/**************************************************************
 *  Name                 : WL_StateFCN_Antipinch
 *  Description          :	Down all the window until open and delay 5 second
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void WL_StateFCN_Antipinch(void)
{
	if(s_Bar_WL.ub_Position!=OPEN)
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

/**************************************************************
 *  Name                 : WL_StateFCN_Block
 *  Description          :	Wait until Release the button
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void WL_StateFCN_Block(void)
{
	if(!Button_GetStatus(ps_Button))
	{
		e_State = STATE_IDLE;
	}		
	Indicator_SetIDLE(&s_Indicator);
}



/**************************************************************
 *  Name                 : WL_StateFCN_AutoUP
 *  Description          :	Close the window automatically
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void WL_StateFCN_AutoUP(void)
{
	if(s_Bar_WL.ub_Position!=CLOSE)
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


/**************************************************************
 *  Name                 : WL_StateFCN_AutoDOWN
 *  Description          :	Open the window automatically
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void WL_StateFCN_AutoDOWN(void)
{
	if(s_Bar_WL.ub_Position!=OPEN)
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


/**************************************************************
 *  Name                 : WL_StateFCN_ManualDOWN
 *  Description          :	Open the window manual
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void WL_StateFCN_ManualDOWN(void)
{
	if(s_Bar_WL.ub_Position!=OPEN    &&  Button_GetStatus(&s_ButtonDOWN) && !Button_GetStatus(&s_ButtonUP))
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


/**************************************************************
 *  Name                 : WL_StateFCN_ManualUP
 *  Description          :	Close the window manual
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void WL_StateFCN_ManualUP(void)
{
	if(s_Bar_WL.ub_Position!=CLOSE    &&  Button_GetStatus(&s_ButtonUP)  && !Button_GetStatus(&s_ButtonDOWN) )
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






