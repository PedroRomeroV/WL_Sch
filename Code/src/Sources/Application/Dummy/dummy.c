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
STATES_WL PreviousStatus;
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


void Read(void)    //lee los puertos de entrada y incrementa sus contadores si son presionados , unico que asigna el puntero a boton
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
	else
	{
	MyButtonUP.ButtonTimeHigh=0;
	MyButtonDOWN.ButtonTimeHigh=0;
	}
	if( MyStatus == STATE_UP_AUTO ||  MyStatus == STATE_UP_MANUAL )
	{
		if(Button_GetButtonStatus(&MyButtonANTIPINCH))
		{
			MyButtonANTIPINCH.ButtonTimeHigh++;
		}
		
	}
	else
	{
		MyButtonANTIPINCH.ButtonTimeHigh=0;
	}
	
}

T_UBYTE validation()  
{
	if(PtrButton->ButtonTimeHigh > BUTTON_OVERFLOW_TIME)
	{
		PtrButton->ButtonTimeHigh--;	
	}
	if(	MyButtonANTIPINCH.ButtonTimeHigh == BUTTON_AUTO_TIME)  //poner rango 
	{
		return FUNCTIONALITY_ANTIPINCH;	 //automatic funtionality
	}
	if(	PtrButton->ButtonTimeHigh == BUTTON_AUTO_TIME)  //poner rango 
	{
		return FUNCTIONALITY_AUTO;	 //automatic funtionality
	}
	if(	PtrButton->ButtonTimeHigh == BUTTON_MANUAL_TIME)     //poner rango 
	{
		return FUNCTIONALITY_MANUAL;    //manual functoinality
	}
	else
	{
		return FUNCTIONALITY_INVALID;
	}
}



void State_Mnager(void)    //if valid button 
{
	PreviousStatus=MyStatus;
	if(MyStatus == STATE_IDLE  && FUNCTIONALITY_AUTO  )  
	{
		if(	PtrButton->ButtonID == BUTTON_UP)
		{
			MyStatus=STATE_UP_AUTO;
		}
		else if(PtrButton->ButtonID == BUTTON_DOWN)
		{
			MyStatus=STATE_DOWN_AUTO;
		}
	}
	else
	{
		MyStatus=STATE_BLOCK;
	}
	if(	FUNCTIONALITY_MANUAL   &&   (MyStatus == STATE_UP_AUTO  ||  MyStatus == STATE_DOWN_AUTO )   )
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
	if( FUNCTIONALITY_ANTIPINCH  && (MyStatus == STATE_UP_AUTO || MyStatus == STATE_UP_MANUAL) )
	{
		MyStatus=STATE_ANTIPINCH;
		MyButtonANTIPINCH.ButtonTimeHigh=0;
	}	
}



void Response(void)
{
	switch(MyStatus)
	{
		case STATE_BLOCK:
		break;
		case STATE_IDLE:
		break;
		case STATE_ANTIPINCH:
		break;
		case STATE_UP_AUTO:
		break;
		case STATE_UP_MANUAL:
		break;
		case STATE_DOWN_AUTO:
		break;
		case STATE_DOWN_MANUAL:
		break;
		default:
		break;
		
	}
}





void WL_StateFCN_IDLE(void)
{
	
}


void WL_StateFCN_Antipinch(void)
{
	
	if(MyBar_WL.Position!=0)
	{
		static T_UWORD lub_counter=LED_TRANSITION_TIME;
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			LEDBar_DOWN_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;			
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
	}
	
}
void WL_StateFCN_Block(void)
{
	if(!Button_GetButtonStatus(PtrButton))
	{
		MyStatus = STATE_IDLE;
	}		
}


void WL_StateFCN_AutoUP(void)
{
	if(MyBar_WL.Position!=SIZELEDBAR)
	{
		static T_UWORD lub_counter=LED_TRANSITION_TIME;
		if(PreviousStatus != STATE_UP_AUTO)
		{
			lub_counter=LED_TRANSITION_TIME ;
		}
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			
			LEDBar_UP_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}
}


void WL_StateFCN_AutoDOWN(void)
{
	if(MyBar_WL.Position!=0)
	{
		static T_UWORD lub_counter=LED_TRANSITION_TIME;
		if(PreviousStatus != STATE_DOWN_AUTO)
		{
			lub_counter=LED_TRANSITION_TIME ;
		}
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			
			LEDBar_DOWN_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}
}





void WL_StateFCN_ManualDOWN(void)
{

	if(MyBar_WL.Position!=0    &&  Button_GetButtonStatus(&MyButtonDOWN) )
	{
		static T_UWORD lub_counter=LED_TRANSITION_TIME;
		if(PreviousStatus != STATE_DOWN_MANUAL)
		{
			lub_counter=LED_TRANSITION_TIME ;
		}
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			
			LEDBar_DOWN_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}	
	
}

void WL_StateFCN_ManualUP(void)
{
if(MyBar_WL.Position!=0    &&  Button_GetButtonStatus(&MyButtonUP) )
	{
		static T_UWORD lub_counter=LED_TRANSITION_TIME;
		if(PreviousStatus != STATE_UP_MANUAL)
		{
			lub_counter=LED_TRANSITION_TIME ;
		}
		if(lub_counter  == LED_TRANSITION_TIME )
		{
			
			LEDBar_UP_ONE(&MyBar_WL);
			lub_counter=0;
		}
		lub_counter++;			
	}
	else
	{
		MyStatus = STATE_IDLE;
	}
}






