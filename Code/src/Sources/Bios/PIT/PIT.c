/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/* MCU-specific derivative */
#include "MCU_derivative.h" 
/* Data types */
#include "typedefs.h"

#include "IntcInterrupts.h"

/* Own Headers */
#include "PIT.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* PIT_Callback, function to be called upon timeout of PIT ub_Channel N */
tCallbackFunction PIT_Callback[8];

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    PIT device - Low level initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void PIT_device_init(void) 
{
    PIT.PITMCR.R = 0x00000001;       /* Enable PIT and configure timers to stop in debug mode */
}

/****************************************************************************************************/
/**
* \brief    PIT Channel Low level configuration
* \author   Abraham Tezmol
* \param    T_UBYTE ub_Channel - Channel to be configured
* \param    tCallbackFunction Callback - Function to invoke upon PIT count to zero event
* \return   void
*/
void PIT_channel_configure(T_UBYTE ub_Channel, tCallbackFunction t_Callback) 
{
    PIT.CH[ub_Channel].LDVAL.R = PIT_CHANNEL_VALUE;      /* PIT1 timeout --> Refer to PIT.h file for calculations */
    PIT_Callback[ub_Channel]   = t_Callback;               /* Initialize callback function */
    
    /* Install Interrupt routine for this specific ub_Channel */
    INTC_InstallINTCInterruptHandler(PIT_channel_0_isr,59,5);
}

/****************************************************************************************************/
/**
* \brief    PIT ub_Channel Low level Start procedure
* \author   Abraham Tezmol
* \param    T_UBYTE ub_Channel - PIT ub_Channel to start
* \return   void
*/
void PIT_channel_start(T_UBYTE ub_Channel)
{
    PIT.CH[ub_Channel].TCTRL.R = 0x000000003;            /* Enable PIT1 interrupt and make PIT active to count */
}


/****************************************************************************************************/
/**
* \brief    PIT ub_Channel Low level Stop procedure
* \author   Abraham Tezmol
* \param    T_UBYTE ub_Channel - PIT ub_Channel to stop
* \return   void
*/
void PIT_channel_stop(T_UBYTE ub_Channel)
{
	PIT.CH[ub_Channel].TCTRL.R = 0x000000000;            /* Disable PIT ub_Channel interrupt and make PIT inactive to count */
}


/***************************************************************************************************/
/**
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
void PIT_channel_0_isr(void)
{
  if (PIT.CH[0].TFLG.B.TIF)
  {
    /* Clear the time-base interrupt flag */
    PIT.CH[0].TFLG.B.TIF = 1;
    
    /*call callback function, if initialized*/
        if( PIT_Callback[0] != NULL )
        {
            PIT_Callback[0]();
        }
  }
}


