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
T_UBYTE Functionality;

void test(void)
{
static int j=10;
static int i=1;
if(i)
{
	LEDBar_Init(&MyBar_WL);
	Button_Init(&MyButtonUP,BUTTON_UP);	
	i=0;	
}


if(Button_GetButtonStatus(&MyButtonUP))  //  (j) //
{
	LEDBar_UP_ONE(&MyBar_WL);	
j--;
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

}


void Read_o(void)    //lee los puertos de entrada y incrementa sus contadores si son presionados , unico que asigna el puntero a boton
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

void validation(void)  
{
	T_UBYTE variable=0;
	if(PtrButton->ButtonTimeHigh > BUTTON_OVERFLOW_TIME)
	{
		PtrButton->ButtonTimeHigh--;	
	}
	
	if(	PtrButton->ButtonTimeHigh == BUTTON_AUTO_TIME)  //poner rango 
	{
		Functionality = FUNCTIONALITY_AUTO;	 //automatic funtionality
		variable++;
	}
	if(	PtrButton->ButtonTimeHigh == BUTTON_MANUAL_TIME)     //poner rango 
	{
		Functionality = FUNCTIONALITY_MANUAL;    //manual functoinality
		variable++;
	}
	if(	MyButtonANTIPINCH.ButtonTimeHigh == BUTTON_AUTO_TIME)  //poner rango 
	{
		Functionality = FUNCTIONALITY_ANTIPINCH;	 //automatic funtionality
		variable++;
	}
	if(!variable)
	{
		Functionality=  FUNCTIONALITY_INVALID;
	}

}



void State_Mnager(void)    //if valid button 
{
	PreviousStatus=MyStatus;
	if(Functionality == FUNCTIONALITY_AUTO)
	{
		if(MyStatus == STATE_IDLE  )  
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
	}
	if(	Functionality  == FUNCTIONALITY_MANUAL   &&   (MyStatus == STATE_UP_AUTO  ||  MyStatus == STATE_DOWN_AUTO )   )
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
	if( Functionality == FUNCTIONALITY_ANTIPINCH  && (MyStatus == STATE_UP_AUTO || MyStatus == STATE_UP_MANUAL) )
	{
		MyStatus=STATE_ANTIPINCH;
		MyButtonANTIPINCH.ButtonTimeHigh=0;
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






