/* =========================================================================
 ***
 *** The MIT License (MIT)
 ***
 *** Copyright (c) 2016 uGrid
 ***
 *** Permission is hereby granted, free of charge, to any person obtaining a copy
 *** of this software and associated documentation files (the "Software"), to deal
 *** in the Software without restriction, including without limitation the rights
 *** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *** copies of the Software, and to permit persons to whom the Software is
 *** furnished to do so, subject to the following conditions:
 ***
 *** The above copyright notice and this permission notice shall be included in all
 *** copies or substantial portions of the Software.
 ***
 *** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *** SOFTWARE.
 ***
  ========================================================================= */
/*******************************************************************************/
/*		Arquivos Header						     		  					   */
/*******************************************************************************/

#include "DSP2833x_Device.h"     
#define ADC_Cal (void (*) (void)) 0x380080 // pointer for ADC calibration in OTP


#pragma CODE_SECTION(INIT_FLASH, "ramfuncs");


INIT_SYSTEM()
{
//-------------------------------------------------------------------------------
// Disable all interrupts and debug RTM flag
//-------------------------------------------------------------------------------

	DINT;
//	DRTM;  // Teste novo -
//-------------------------------------------------------------------------------
// Disable WatchDog Timer
//-------------------------------------------------------------------------------

    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;

//-------------------------------------------------------------------------------
// Configure PLL - Obs: The input frequency of the controlCard kit is:
// [ ] R1.0 = 25 MHz
// [X] R1.0 = 30 MHz (PGF)
// [ ] R1.1 = 20 MHz
// [ ] R1.2 = 30 MHz
// [ ] R2.2 = 30 MHz
//
//-------------------------------------------------------------------------------
// sprufb0c - pag 50;

   	// Make sure the PLL is not running in limp mode
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
   {
      asm("ESTOP0");
	  while (1);
   }



   	// DIVSEL MUST be 0 before PLLCR can be changed from
   	// 0x0000. 
   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
       EDIS;
   }
	// Disable failed oscilator detect logic
	   EALLOW;
	   SysCtrlRegs.PLLSTS.bit.MCLKOFF=1;
	   EDIS;
   	// Change the PLLCR
      EALLOW;
      SysCtrlRegs.PLLCR.bit.DIV = 10;	// Multiply by 10
      EDIS;
	// Wait for PLL lock    
       while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
      {
	      // Uncomment to service the watchdog
          // ServiceDog();
      }
	// Set failed oscilator detect logic
      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
      EDIS;
	// Set de DIVSEL value
	  EALLOW;
	  SysCtrlRegs.PLLSTS.bit.DIVSEL=2;	// Divide by 2;
	  
//-------------------------------------------------------------------------------
// Set clock for normal operation and low power mode operation
//-------------------------------------------------------------------------------

	EALLOW;
	SysCtrlRegs.HISPCP.all=0x0000;		// High Clock/1
	SysCtrlRegs.LOSPCP.all=0x0005;		// Low Clock/10

//-------------------------------------------------------------------------------
// Enable Peripheral clock
//-------------------------------------------------------------------------------

	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
	SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
   	SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 0;   // SCI-B
   	SysCtrlRegs.PCLKCR0.bit.SCICENCLK = 0;   // SCI-C
   	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;   // SPI-A
   	SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = 0; // McBSP-A
   	SysCtrlRegs.PCLKCR0.bit.MCBSPBENCLK = 0; // McBSP-B
   	SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=0;    // eCAN-A
   	SysCtrlRegs.PCLKCR0.bit.ECANBENCLK=0;    // eCAN-B

	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Disable TBCLK within the ePWM
   	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
   	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
   	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
   	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;  // ePWM4
   	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;  // ePWM5
   	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;  // ePWM6
   	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK within the ePWM

   	SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 0;  // eCAP3
   	SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 0;  // eCAP4
   	SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 0;  // eCAP5
   	SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 0;  // eCAP6
   	SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  // eCAP1
   	SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 0;  // eCAP2
   	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 0;  // eQEP1
   	SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 0;  // eQEP2

   	SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
   	SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 0; // CPU Timer 1
   	SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 0; // CPU Timer 2

   	SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 1;       // DMA Clock
   	SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;     // XTIMCLK
   	SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;    // GPIO input clock

   EDIS;

//-------------------------------------------------------------------------------
// Calibrate ADC
//-------------------------------------------------------------------------------

(*ADC_Cal) ();


} //EOF


//---------------------------------------------------------------------------
// Example: InitFlash:
//---------------------------------------------------------------------------
// This function initializes the Flash Control registers

//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

void INIT_FLASH(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1;

   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI.
   //Refer to the datasheet for the latest information.

// For 150 MHZ Operation

   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;

   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 8;

   //                CAUTION
   //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;

   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.

   asm(" RPT #7 || NOP");
}
