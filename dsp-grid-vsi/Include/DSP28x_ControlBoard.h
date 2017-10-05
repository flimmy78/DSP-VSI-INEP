
//###########################################################################
//
// FILE:   DSP28x_ControlBoard.h
//
// TITLE:  DSP28x Project Headerfile and Examples Include File
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V141 $
// $Release Date: November  6, 2015 $
// $Copyright: Copyright (C) 2007-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef DSP28x_CONTROLBOARD_H
#define DSP28x_CONTROLBOARD_H

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
//#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#endif  // end of DSP28x_CONTROLBOARD_H definition



/*******************************************************************************/
/*	GPIO									     		  					   */
/*******************************************************************************/


#define LED1DAT	GpioDataRegs.GPBDAT.bit.GPIO60
#define LED2DAT	GpioDataRegs.GPBDAT.bit.GPIO61
#define LED3DAT	GpioDataRegs.GPBDAT.bit.GPIO62
#define LED4DAT	GpioDataRegs.GPBDAT.bit.GPIO63

#define LED1TGL GpioDataRegs.GPBTOGGLE.bit.GPIO60
#define LED2TGL GpioDataRegs.GPBTOGGLE.bit.GPIO61
#define LED3TGL GpioDataRegs.GPBTOGGLE.bit.GPIO62
#define LED4TGL GpioDataRegs.GPBTOGGLE.bit.GPIO63


#define LED1CLR GpioDataRegs.GPBCLEAR.bit.GPIO60
#define LED2CLR GpioDataRegs.GPBCLEAR.bit.GPIO61
#define LED3CLR GpioDataRegs.GPBCLEAR.bit.GPIO62
#define LED4CLR GpioDataRegs.GPBCLEAR.bit.GPIO63


#define LED1SET GpioDataRegs.GPBSET.bit.GPIO60
#define LED2SET GpioDataRegs.GPBSET.bit.GPIO61
#define LED3SET GpioDataRegs.GPBSET.bit.GPIO62
#define LED4SET GpioDataRegs.GPBSET.bit.GPIO63


#define LED2kitDAT  	GpioDataRegs.GPADAT.bit.GPIO31	//LED_2KIT
#define	LED3kitDAT		GpioDataRegs.GPBDAT.bit.GPIO34	//LED_3KIT

#define SWITCH_TURNOFF  !GpioDataRegs.GPBDAT.bit.GPIO58  // SW1
#define SWITCH_RESET	!GpioDataRegs.GPBDAT.bit.GPIO59  // SW2

#define RELAY			GpioDataRegs.GPBDAT.bit.GPIO49


#define LED2kitTGL  GpioDataRegs.GPATOGGLE.bit.GPIO31  // Toggle GPIO31 once per 500 milliseconds
#define LED3kitTGL  GpioDataRegs.GPBTOGGLE.bit.GPIO34  // Toggle GPIO34 once per 500 milliseconds

#define LED2kitCLR	GpioDataRegs.GPACLEAR.bit.GPIO31
#define LED2kitSET  GpioDataRegs.GPASET.bit.GPIO31


#define LED3kitCLR GpioDataRegs.GPBCLEAR.bit.GPIO34
#define	LED3kitSET GpioDataRegs.GPBSET.bit.GPIO34



