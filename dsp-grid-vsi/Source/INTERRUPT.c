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

void ConfigEIRandDBGIER(Uint16 en_cpu_int);

void INIT_INTERRUPT()
{

//---------------------------------------------------------------------------
// General configurations: 
//---------------------------------------------------------------------------
 
  	DINT;			  		// Desabilita a chave geral de interrupções 
  	IER = 0x0000;			// Desabilita todas as interrupções da CPU
  	asm(" MOV *SP++,IER");
  	asm(" POP DBGIER");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
  	IFR = 0x0000;			// Limpa todos os flags de interrupção da CPU

}



//---------------------------------------------------------------------------
// Enable selected interrupts and general CPU interrupts: 
//---------------------------------------------------------------------------

void ENABLE_INTERRUPT() // Movido para o Main.
{

//---------------------------------------------------------------------------
// Individual configurations (Pheripheral interrupts): 
//---------------------------------------------------------------------------
 	
 	EPwm1Regs.ETSEL.bit.INTEN =0;
	EPwm2Regs.ETSEL.bit.INTEN =0;
	EPwm3Regs.ETSEL.bit.INTEN =0;
	EPwm4Regs.ETSEL.bit.INTEN =0;
	EPwm5Regs.ETSEL.bit.INTEN =0;
	EPwm6Regs.ETSEL.bit.INTEN =0;

	EPwm1Regs.ETCLR.bit.INT=1;							//Limpa flag 
	EPwm2Regs.ETCLR.bit.INT=1;							//Limpa flag 
	EPwm3Regs.ETCLR.bit.INT=1;							//Limpa flag 
	EPwm4Regs.ETCLR.bit.INT=1;							//Limpa flag 
	EPwm5Regs.ETCLR.bit.INT=1;							//Limpa flag
	EPwm6Regs.ETCLR.bit.INT=1;							//Limpa flag
	 
	EPwm2Regs.ETSEL.bit.INTSEL=1;
	EPwm2Regs.ETPS.bit.INTPRD=1;
	EPwm2Regs.ETSEL.bit.INTEN=1; 

	EPwm4Regs.ETSEL.bit.INTSEL=2;						// habilita evento quando timer =0
	EPwm4Regs.ETPS.bit.INTPRD =1;						// gera INT no primeiro (todos) evento
	EPwm4Regs.ETSEL.bit.INTEN =1;




//---------------------------------------------------------------------------
// Enable selected interrupts (PIE): 
//---------------------------------------------------------------------------
 	
 	PieCtrlRegs.PIEACK.all  = 0xFFFF;  // Reseta o bit de acknowledgement

	PieCtrlRegs.PIEIER3.bit.INTx1 = 0; // Configura a INT do EPWM1
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1; // Configura a INT do EPWM2
	PieCtrlRegs.PIEIER3.bit.INTx3 = 0;// Configura a INT do EPWM3
	PieCtrlRegs.PIEIER3.bit.INTx4 = 1;// Configura a INT do EPWM4	
	PieCtrlRegs.PIEIER3.bit.INTx5 = 0;// Configura a INT do EPWM5
	PieCtrlRegs.PIEIER3.bit.INTx6 = 0;// Configura a INT do EPWM6	

//---------------------------------------------------------------------------
// Enable selected interrupts and general CPU interrupts: 
//---------------------------------------------------------------------------

// Enable CPU INT3 which is connected to EPWM1-6 INT:
   	IER |= 0x0004;
					// Enable=1
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; // Enable the PIE
	EINT;  	// Enable Interrupts at the CPU level 
  	ERTM; 	// Coloca 0 no FLAG DBGM, permitindo Debug em Tempo Real

}


void ConfigEIRandDBGIER(Uint16 en_cpu_int)
{


  IER = en_cpu_int;
  asm(" MOV *SP++,IER");
  asm(" POP DBGIER");

}
