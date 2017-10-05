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

extern void interrupt MAIN_ISR(void);

//---------------------------------------------------------------------------
// InitPieVectTable: 
//---------------------------------------------------------------------------
// This function initializes the PIE vector table to a known state.
// This function must be executed after boot time.
//

void INIT_PIE_VEC_TABLE(void)
{


// Caso o programa se perca, é interessante popular todas os vetores de forma a descobrir o erro
// Isso é feito nos exemplos da texas, porém o procedimento só é recomendado para testes
//---------------------------------------------------------------------------
// Populate PIE vect with the ISR adress: 
//---------------------------------------------------------------------------
 
   EALLOW;  // This is needed to write to EALLOW protected registers

//	PieVectTable.EPWM1_INT = &MAIN_ISR;
	PieVectTable.EPWM2_INT = &MAIN_ISR;// TESTESEPWM2
//	PieVectTable.EPWM3_INT = &MAIN_ISR;
	PieVectTable.EPWM4_INT = &MAIN_ISR;// TESTES
//	PieVectTable.EPWM5_INT = &MAIN_ISR;
//	PieVectTable.EPWM6_INT = &MAIN_ISR;
    
   EDIS;    // This is needed to disable write to EALLOW protected registers

	// Enable the PIE Vector Table
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;	
			
}

//---------------------------------------------------------------------------
// InitPieVectTable: 
//---------------------------------------------------------------------------

void INIT_PIE_CTRL(void)
{
    // Disable Interrupts at the CPU level:

    DINT;
  
    // Disable the PIE
  
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

	// Clear all PIEIER registers:
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;	
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	// Clear all PIEIFR registers:
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;	
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;

}	
//===========================================================================
// End of file.
//===========================================================================


