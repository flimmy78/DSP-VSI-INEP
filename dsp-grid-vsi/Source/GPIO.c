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

void INIT_GPIO(void)
{
   EALLOW;

   	GpioCtrlRegs.GPAMUX1.all = 0x0000;     	// GPIO functionality GPIO00-GPIO15
   	GpioCtrlRegs.GPAMUX2.all = 0x0000;     	// GPIO functionality GPIO16-GPIO31
   	GpioCtrlRegs.GPBMUX1.all = 0x0000;     	// GPIO functionality GPIO23-GPIO47
   	GpioCtrlRegs.GPBMUX2.all = 0x0000;     	// GPIO functionality GPIO48-GPIO63
   	GpioCtrlRegs.GPCMUX1.all = 0x0000;     	// GPIO functionality GPIO64-GPIO79
   	GpioCtrlRegs.GPCMUX2.all = 0x0000;     	// GPIO functionality GPIO80-GPIO95

	
   
   // Each GPIO pin can be: 
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs 

//-------------------------------------------------------------------------------
// MUX REGS
//-------------------------------------------------------------------------------
//        31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 
// GPIOA  0  1  0  1  0  1  0  1  0  1  0  1  0  1  0  1                     
//        15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
//        0  1  0  1  0  0  0  1  0  1  0  1  0  1  0  1
// Todos pinos configurados para as funções ligadas a PWM 

//-----------------------------------------------
// Delta - Configurados como I/O e deixados em 0
//-----------------------------------------------

	GpioCtrlRegs.GPAMUX1.bit.GPIO0=0;		// Fase ? 
	GpioCtrlRegs.GPAMUX1.bit.GPIO1=0;		// Fase ? 
	GpioCtrlRegs.GPAMUX1.bit.GPIO4=0;		// Fase ?	
	GpioCtrlRegs.GPAMUX1.bit.GPIO5=0;		// Fase ?
	GpioCtrlRegs.GPAMUX1.bit.GPIO8=0;		// Fase ? 
	GpioCtrlRegs.GPAMUX1.bit.GPIO9=0;		// Fase ?

	GpioDataRegs.GPACLEAR.bit.GPIO0=1;		
	GpioDataRegs.GPACLEAR.bit.GPIO1=1;
	GpioDataRegs.GPACLEAR.bit.GPIO4=1;		
	GpioDataRegs.GPACLEAR.bit.GPIO5=1;
	GpioDataRegs.GPACLEAR.bit.GPIO8=1;		
	GpioDataRegs.GPACLEAR.bit.GPIO9=1;

	GpioCtrlRegs.GPADIR.bit.GPIO0=1;	// Saída
	GpioCtrlRegs.GPADIR.bit.GPIO1=1;	// Saída
	GpioCtrlRegs.GPADIR.bit.GPIO4=1;	// Saída
	GpioCtrlRegs.GPADIR.bit.GPIO5=1;	// Saída
	GpioCtrlRegs.GPADIR.bit.GPIO8=1;	// Saída
	GpioCtrlRegs.GPADIR.bit.GPIO9=1;	// Saída

//-----------------------------------------------
// VSI-2L
//-----------------------------------------------

	GpioCtrlRegs.GPAMUX1.bit.GPIO2=1;		// Fase ?
	GpioCtrlRegs.GPAMUX1.bit.GPIO3=1;		// Fase ?
	GpioCtrlRegs.GPAMUX1.bit.GPIO6=1;		// Fase ? 
	GpioCtrlRegs.GPAMUX1.bit.GPIO7=1;		// Fase ? 
	GpioCtrlRegs.GPAMUX1.bit.GPIO10=1;		// Fase ?	
	GpioCtrlRegs.GPAMUX1.bit.GPIO11=1;		// Fase ?

//-----------------------------------------------
// LEDS
//-----------------------------------------------

   	GpioCtrlRegs.GPAMUX2.bit.GPIO31=0;		//LED_2KIT
	GpioCtrlRegs.GPBMUX1.bit.GPIO34=0;		//LED_3KIT
	GpioCtrlRegs.GPBMUX2.bit.GPIO60=0;		//LED_1
	GpioCtrlRegs.GPBMUX2.bit.GPIO61=0;		//LED_2
   	GpioCtrlRegs.GPBMUX2.bit.GPIO62=0;		//LED_3
   	GpioCtrlRegs.GPBMUX2.bit.GPIO63=0;		//LED_4

   	GpioCtrlRegs.GPADIR.bit.GPIO31=1;	  // GPIO31 (LED2 kit) 	
	GpioCtrlRegs.GPBDIR.bit.GPIO34=1;	  // GPIO34 (LED3 kit) 		
	GpioCtrlRegs.GPBDIR.bit.GPIO60=1;	  // LED 
   	GpioCtrlRegs.GPBDIR.bit.GPIO61=1;	  // LED 
   	GpioCtrlRegs.GPBDIR.bit.GPIO62=1;	  // LED 
   	GpioCtrlRegs.GPBDIR.bit.GPIO63=1;	  // LED


//-----------------------------------------------
// RELAY
//-----------------------------------------------
	GpioCtrlRegs.GPBDIR.bit.GPIO49=1;	  // RELAY	 
//-----------------------------------------------
// Switches
//-----------------------------------------------

   	GpioCtrlRegs.GPBMUX2.bit.GPIO58=0;		//SWITCH_SW1
   	GpioCtrlRegs.GPBMUX2.bit.GPIO59=0;		//SWITCH_SW2

   	GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;    // SWITCH_RESET
  	GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0;    // SWITCH_TURNOFF 

    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;    // Pullup's enable for SWITCH_RESET
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0;    // Pullup's enable for SWITCH_TURNOFF

//-------------------------------------------------------------------------------
// QUAL REGS
//-------------------------------------------------------------------------------

   // Each input can have different qualification
   // a) input synchronized to SYSCLKOUT
   // b) input qualified by a sampling window
   // c) input sent asynchronously (valid for peripheral inputs only)

   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT 
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO39 Synch to SYSCLKOUT 
   GpioCtrlRegs.GPBQSEL2.all = 0x0000;    // GPIO48-GPIO63 Synch to SYSCLKOUT 


   GpioCtrlRegs.GPAQSEL2.bit.GPIO24=1;    // GPIO0-GPIO15 Synch to SYSCLKOUT 		
   GpioCtrlRegs.GPAQSEL2.bit.GPIO25=1;    // GPIO0-GPIO15 Synch to SYSCLKOUT 		
   GpioCtrlRegs.GPAQSEL1.bit.GPIO12=1;	  // for tripzone qualification


   GpioCtrlRegs.GPACTRL.bit.QUALPRD3=100;  // 1us for switches qualification
   GpioCtrlRegs.GPACTRL.bit.QUALPRD1=100;  // 1us for switches qualification

//-------------------------------------------------------------------------------
// PULLuPS REGS
//-------------------------------------------------------------------------------

   // Pull-ups can be enabled or disabled. 

   GpioCtrlRegs.GPAPUD.all = 0xFFFF;     // Pullup's disabled GPIO0-GPIO31
   GpioCtrlRegs.GPBPUD.all = 0xFFFF;     // Pullup's disabled GPIO32-GPIO34
   GpioCtrlRegs.GPCPUD.all = 0xFFFF;     // Pullup's disabled GPIO64-GPIO79


   EDIS;

}	
	

