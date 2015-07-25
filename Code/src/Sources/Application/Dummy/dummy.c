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


S_BUTTON_TYPE MyButtonUP;
S_BUTTON_TYPE MyButtonDOWN;
S_BUTTON_TYPE MyButtonANTIPINCH;
S_BAR_TYPE MyBar_WL;
S_INDICATOR_TYPE MyIndicator; 
STATES_WL MyStatus;
STATES_WL PreviousStatus;
S_BUTTON_TYPE *PtrButton;
T_UBYTE Functionality;
T_UWORD lub_counter;

void test(void)
{


if(	PtrButton->ub_ButtonTimeHigh == BUTTON_AUTO_TIME)
{
		LEDBar_UP_ONE(&MyBar_WL);
}


}

void Init_WL(void)
{
MyStatus=STATE_IDLE;
Button_Init(&MyButtonUP,BUTTON_UP);
Button_Init(&MyButtonDOWN,BUTTON_DOWN);
Button_Init(&MyButtonANTIPINCH,BUTTON_ANTIPINCH);
LEDBar_Init(&MyBar_WL);
Indicator_Init(&MyIndicator);
Functionality = FUNCTIONALITY_INVALID;
lub_counter=LED_TRANSITION_TIME;
}


void Read_o(void)    //lee los puertos de entrada y incrementa sus contadores si son presionados , unico que asigna el puntero a boton
{
	if( (MyStatus != STATE_ANTIPINCH) &&
	(Button_GetStatus(&MyButtonUP) ^ Button_GetStatus(&MyButtonDOWN) ))
	{
		if(Button_GetStatus(&MyButtonUP))
		{
			PtrButton= &MyButtonUP;
		}
		if(Button_GetStatus(&MyButtonDOWN))
		{
			PtrButton= &MyButtonDOWN;
		}
		PtrButton->ub_ButtonTimeHigh++;
	}
	else
	{
	MyButtonUP.ub_ButtonTimeHigh=0;
	MyButtonDOWN.ub_ButtonTimeHigh=0;
	}
	if( MyStatus == STATE_UP_AUTO ||  MyStatus == STATE_UP_MANUAL )
	{
		if(Button_GetStatus(&MyButtonANTIPINCH))
		{
			MyButtonANTIPINCH.ub_ButtonTimeHigh++;
		}
		
	}
	else
	{
		MyButtonANTIPINCH.ub_ButtonTimeHigh=0;
	}
	
}

void validation(void)  
{

	if(	MyButtonANTIPINCH.ub_ButtonTimeHigh == BUTTON_AUTO_TIME)  //reach 10 ms go auto antipinch and ignore the rest
	{
		Functionality = FUNCTIONALITY_ANTIPINCH;	 //automatic funtionality
	}
	else
	{
		switch(PtrButton->ub_ButtonTimeHigh)
		{
		case BUTTON_AUTO_TIME:
			Functionality = FUNCTIONALITY_AUTO;	 
			break;
		case BUTTON_MANUAL_TIME:
			Functionality = FUNCTIONALITY_MANUAL; 
			break;
		default:
			if(PtrButton->ub_ButtonTimeHigh < BUTTON_AUTO_TIME)
			{
				Functionality=  FUNCTIONALITY_INVALID;
			}
			if(PtrButton->ub_ButtonTimeHigh > BUTTON_OVERFLOW_TIME)
			{
				PtrButton->ub_ButtonTimeHigh--;
			}
			else {}
		break;
		
		}
	}
}



void State_Mnager(void)    //if valid button 
{
	PreviousStatus=MyStatus;
	if(Functionality == FUNCTIONALITY_AUTO )
	{
		if(MyStatus == STATE_IDLE  )  
		{
			if(	PtrButton->ub_ButtonID == BUTTON_UP)
			{
				MyStatus=STATE_UP_AUTO;
			}
			else if(PtrButton->ub_ButtonID == BUTTON_DOWN)
			{
				MyStatus=STATE_DOWN_AUTO;
			}
		}
		else
		{
			MyStatus=STATE_BLOCK;
		}
		Functionality=  FUNCTIONALITY_INVALID;
	}
	if(	Functionality  == FUNCTIONALITY_MANUAL  )
	{
		if(MyStatus == STATE_UP_AUTO  ||  MyStatus == STATE_DOWN_AUTO )
		{
			if(	PtrButton->ub_ButtonID == BUTTON_UP)
			{
				MyStatus=STATE_UP_MANUAL;
			}
			else if(PtrButton->ub_ButtonID == BUTTON_DOWN)
			{
				MyStatus=STATE_DOWN_MANUAL;
			}
		}
		Functionality=  FUNCTIONALITY_INVALID;
	}
	if( Functionality == FUNCTIONALITY_ANTIPINCH  )
	{
		if(MyStatus == STATE_UP_AUTO || MyStatus == STATE_UP_MANUAL)
		{
			MyStatus=STATE_ANTIPINCH;
		}
		Functionality=  FUNCTIONALITY_INVALID;
	}	
}



void Response_o(void)
{
	switch(MyStatus)
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
lub_counter=LED_TRANSITION_TIME;
Indicator_SetIDLE(&MyIndicator);
}


void WL_StateFCN_Antipinch(void)
{
	
	if(MyBar_WL.ub_Position!=0)
	{
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			LEDBar_DOWN_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;	
		Indicator_SetDOWN(&MyIndicator);	
	}
	else
	{
	static couterdelay=0;
		if(DELAY_TIME ==  couterdelay)
		{
			MyStatus = STATE_IDLE;
			couterdelay=0;
		}
		couterdelay++;
		Indicator_SetIDLE(&MyIndicator);
	}
	
}

void WL_StateFCN_Block(void)
{
	if(!Button_GetStatus(PtrButton))
	{
		MyStatus = STATE_IDLE;
	}		
	Indicator_SetIDLE(&MyIndicator);
}


void WL_StateFCN_AutoUP(void)
{
	if(MyBar_WL.ub_Position!=SIZELEDBAR)
	{
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			LEDBar_UP_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;
		Indicator_SetUP(&MyIndicator);			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}
}


void WL_StateFCN_AutoDOWN(void)
{
	if(MyBar_WL.ub_Position!=0)
	{
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			LEDBar_DOWN_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;
		Indicator_SetDOWN(&MyIndicator);			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}
}

void WL_StateFCN_ManualDOWN(void)
{
	if(MyBar_WL.ub_Position!=0    &&  Button_GetStatus(&MyButtonDOWN) )
	{
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			LEDBar_DOWN_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;
		Indicator_SetDOWN(&MyIndicator);			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}		
}

void WL_StateFCN_ManualUP(void)
{
if(MyBar_WL.ub_Position!=0    &&  Button_GetStatus(&MyButtonUP) )
	{
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			
			LEDBar_UP_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;	
		Indicator_SetUP(&MyIndicator);		
	}
	else
	{
		MyStatus = STATE_IDLE;
	}
}






