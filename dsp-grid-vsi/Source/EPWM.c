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

#include "DSP2833x_Device.h"
#include "Define.h"

/*
ePWM1_A,B - Delta Sca2,1
ePWM2_A,B - VSI2L Scn,p 
ePWM3_A,B - Delta Sbc2,1
ePWM4_A,B - VSI2L Sbn,p 
ePWM5_A,B - Delta Sbc2,1
ePWM6_A,B - VSI2L San,p 
*/

/*

OBS: As saídas epwmA acionam as chaves negativas (inferiores) do inversor
OBS: As saídas epwmB acionam as chaves positivas (superiores) do inversor

*/
/*******************************************************************************/
/*		Arquivos Header						     		  					   */
/*******************************************************************************/

INIT_EPWM()
{

EALLOW;
SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC=0;	// for carriers sinc
EDIS;

/*******************************************************************************/
/* INVVERSOR Delta : ePWM1,3,5				     		  					   */
/*******************************************************************************/


//-------------------------------------------------------------------------------
// EPWM Module 1
//-------------------------------------------------------------------------------

EPwm1Regs.TBCTL.bit.HSPCLKDIV=0;					// Frequencia do clock/1
EPwm1Regs.TBCTL.bit.CLKDIV=0;						// pré escala 1/1

EPwm1Regs.TBPRD = TIMER_INV; 						// Period 
EPwm1Regs.TBPHS.half.TBPHS = PHASE_PWM1; 			// Set Phase register to zero

EPwm1Regs.TBCTL.bit.CTRMODE = 2;					// Symmetrical mode (up down)
EPwm1Regs.TBCTL.bit.PHSEN = 0; 						// Master module
EPwm1Regs.TBCTL.bit.PRDLD = 0;						// Period timer is load at zero
EPwm1Regs.TBCTL.bit.SYNCOSEL = 1; 					// Sync EPWMxsync when timer is 1
EPwm1Regs.TBCTL.bit.SWFSYNC =1;						// Force a Sync pulse
EPwm1Regs.TBCTL.bit.FREE_SOFT=2;					// runs free

EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0; 				// Shadow mode atualização não imediata
EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0; 				// Shadow mode atualização não imediata
EPwm1Regs.CMPCTL.bit.LOADAMODE = 2;					// load on zero or per. (2), zero(0), per.(1)
EPwm1Regs.CMPCTL.bit.LOADBMODE = 2; 				// load on zero or per. (2), zero(0), per.(1)

EPwm1Regs.AQCTLA.bit.CAU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLA.bit.CAD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLA.bit.CBU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLA.bit.CBD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLA.bit.PRD = 1;						// 0 Não faz nada no modo opdown
EPwm1Regs.AQCTLA.bit.ZRO = 1;						// 0 Não faz nada no modo opdown

EPwm1Regs.AQCTLB.bit.CAU = 0; 						// actions for EPWM1B -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLB.bit.CAD = 0;						// actions for EPWM1B -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLB.bit.CBU = 1; 						// actions for EPWM1B -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLB.bit.CBD = 2;						// actions for EPWM1B -> 1 clear, 2 set, 3 toggle
EPwm1Regs.AQCTLB.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm1Regs.AQCTLB.bit.ZRO = 0;						// 0 Não faz nada no modo opdown

EPwm1Regs.DBCTL.bit.OUT_MODE =0; 					// Bypass Dead-band module

EPwm1Regs.ETSEL.bit.SOCAEN=0;						//  habilita geraçaõ de eventos de SOCA para AD (no caso para SEQ1)
EPwm1Regs.ETSEL.bit.SOCASEL=1;						// SOCA gerado qdo timer =0  (periodo =2)
EPwm1Regs.ETPS.bit.SOCAPRD=1;						// gera ção em todos os eventos


EALLOW;
EPwm1Regs.TZSEL.bit.OSHT1=1;						// en
EPwm1Regs.TZCTL.bit.TZA  =2;						// Force PWMxA to low  state (2)
EPwm1Regs.TZCTL.bit.TZB	 =2;						// Force PWMxB to low state (2)
EPwm1Regs.TZFRC.bit.OST  =1;						// Forced trip in Rectifier=1
EDIS;


//-------------------------------------------------------------------------------
// EPWM Module 3
//-------------------------------------------------------------------------------

EPwm3Regs.TBCTL.bit.HSPCLKDIV=0;					// Frequencia do clock/1
EPwm3Regs.TBCTL.bit.CLKDIV=0;						// pré escala 1/1

EPwm3Regs.TBPRD = TIMER_INV; 	 					// Period 
EPwm3Regs.TBPHS.half.TBPHS = PHASE_PWM3;			// Set Phase register
EPwm3Regs.TBCTL.bit.CTRMODE = 2;					// Symmetrical mode (up down)
EPwm3Regs.TBCTL.bit.PHSEN = 1; 						// Slave module (EPwm1 is Master)
EPwm3Regs.TBCTL.bit.PHSDIR =1;						// Count up after the Sync event
EPwm3Regs.TBCTL.bit.PRDLD = 0;						// Period timer is load at zero
EPwm3Regs.TBCTL.bit.SYNCOSEL = 0; 					// Sync when timer is 0
EPwm3Regs.TBCTL.bit.SWFSYNC =0;						// Do not force a Sync pulse
EPwm3Regs.TBCTL.bit.FREE_SOFT=2;					// runs free

EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0; 				// Shadow mode atualização não imediata
EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0; 				// Shadow mode atualização não imediata
EPwm3Regs.CMPCTL.bit.LOADAMODE = 2;					// load on zero or per. (2), zero(0), per.(1)
EPwm3Regs.CMPCTL.bit.LOADBMODE = 2; 				// load on zero or per. (2), zero(0), per.(1)

EPwm3Regs.AQCTLA.bit.CAU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLA.bit.CAD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLA.bit.CBU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLA.bit.CBD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLA.bit.PRD = 1;						// 0 Não faz nada no modo opdown
EPwm3Regs.AQCTLA.bit.ZRO = 1;						// 0 Não faz nada no modo opdown


EPwm3Regs.AQCTLB.bit.CAU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLB.bit.CAD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLB.bit.CBU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLB.bit.CBD = 2;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm3Regs.AQCTLB.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm3Regs.AQCTLB.bit.ZRO = 0;						// 0 Não faz nada no modo opdown

EPwm3Regs.DBCTL.bit.OUT_MODE =0; 					// Bypass Dead-band module


EPwm3Regs.ETSEL.bit.SOCBEN=0;						// Habilita SOCB para SEQ2
EPwm3Regs.ETSEL.bit.SOCBSEL=2;						// Gera no período
EPwm3Regs.ETPS.bit.SOCBPRD=1;						// gera soc em todos os eventos


EALLOW;
EPwm3Regs.TZSEL.bit.OSHT1=1;						//  disable
EPwm3Regs.TZCTL.bit.TZA  =2;						// Force PWMxA to low  state (2)
EPwm3Regs.TZCTL.bit.TZB	 =2;						// Force PWMxB to low state (2)
EPwm3Regs.TZFRC.bit.OST  =1;						// Forced trip in rectifier=1
EDIS;


//-------------------------------------------------------------------------------
// EPWM Module 5
//-------------------------------------------------------------------------------

EPwm5Regs.TBCTL.bit.HSPCLKDIV=0;					// Frequencia do clock/1
EPwm5Regs.TBCTL.bit.CLKDIV=0;						// pré escala 1/1

EPwm5Regs.TBPRD = TIMER_INV; 	 					// Period 
EPwm5Regs.TBPHS.half.TBPHS = PHASE_PWM5;			// Set Phase register
EPwm5Regs.TBCTL.bit.CTRMODE = 2;					// Symmetrical mode (up down)
EPwm5Regs.TBCTL.bit.PHSEN = 1; 						// Slave module (EPwm1 is Master)
EPwm5Regs.TBCTL.bit.PHSDIR =1;						// Count up after the Sync event
EPwm5Regs.TBCTL.bit.PRDLD = 0;						// Period timer is load at zero
EPwm5Regs.TBCTL.bit.SYNCOSEL = 0; 					// Sync when timer is 0
EPwm5Regs.TBCTL.bit.SWFSYNC =0;						// Do not force a Sync pulse
EPwm5Regs.TBCTL.bit.FREE_SOFT=2;					// runs free

EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0; 				// Shadow mode atualização não imediata
EPwm5Regs.CMPCTL.bit.SHDWBMODE = 0; 				// Shadow mode atualização não imediata
EPwm5Regs.CMPCTL.bit.LOADAMODE = 2;					// load on zero or per. (2), zero(0), per.(1)
EPwm5Regs.CMPCTL.bit.LOADBMODE = 2; 				// load on zero or per. (2), zero(0), per.(1)

EPwm5Regs.AQCTLA.bit.CAU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLA.bit.CAD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLA.bit.CBU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLA.bit.CBD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLA.bit.PRD = 1;						// 0 Não faz nada no modo opdown
EPwm5Regs.AQCTLA.bit.ZRO = 1;						// 0 Não faz nada no modo opdown


EPwm5Regs.AQCTLB.bit.CAU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLB.bit.CAD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLB.bit.CBU = 1; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLB.bit.CBD = 2;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm5Regs.AQCTLB.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm5Regs.AQCTLB.bit.ZRO = 0;						// 0 Não faz nada no modo opdown

EPwm5Regs.DBCTL.bit.OUT_MODE =0; 					// Bypass Dead-band module


EPwm5Regs.ETSEL.bit.SOCBEN=0;						// Habilita SOCB para SEQ2
EPwm5Regs.ETSEL.bit.SOCBSEL=2;						// Gera no período
EPwm5Regs.ETPS.bit.SOCBPRD=1;						// gera soc em todos os eventos


EALLOW;
EPwm5Regs.TZSEL.bit.OSHT1=1;						//  disable
EPwm5Regs.TZCTL.bit.TZA  =2;						// Force PWMxA to low  state (2)
EPwm5Regs.TZCTL.bit.TZB	 =2;						// Force PWMxB to low state (2)
EPwm5Regs.TZFRC.bit.OST  =1;						// Forced trip in rectifier=1
EDIS;

/*******************************************************************************/
/* INVVERSOR VSI-2L : ePWM2,4,6			     		  					   	    */
/*******************************************************************************/

//-------------------------------------------------------------------------------
// EPWM Module 2
//-------------------------------------------------------------------------------

EPwm2Regs.TBCTL.bit.HSPCLKDIV=0;					// Frequencia do clock/1
EPwm2Regs.TBCTL.bit.CLKDIV=0;						// pré escala 1/1

EPwm2Regs.TBPRD = TIMER_INV; 	 					// Period 
EPwm2Regs.TBPHS.half.TBPHS = PHASE_PWM2;			// Set Phase register

EPwm2Regs.TBCTL.bit.CTRMODE = 2;					// Symmetrical mode (up down)
EPwm2Regs.TBCTL.bit.PHSEN = 1; 						// Slave module (EPwm1 is Master)
EPwm2Regs.TBCTL.bit.PHSDIR =0;						// Count down after the Sync event
EPwm2Regs.TBCTL.bit.PRDLD = 0;						// Period timer is load at zero
EPwm2Regs.TBCTL.bit.SYNCOSEL = 0; 					// Sync when timer is 0
EPwm2Regs.TBCTL.bit.SWFSYNC =0;						// Do not force a Sync pulse
EPwm2Regs.TBCTL.bit.FREE_SOFT=2;					// runs free

EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0; 				// Shadow mode atualização não imediata
EPwm2Regs.CMPCTL.bit.SHDWBMODE = 0; 				// Shadow mode atualização não imediata
EPwm2Regs.CMPCTL.bit.LOADAMODE = 2;					// load on zero or per. (2), zero(0), per.(1)
EPwm2Regs.CMPCTL.bit.LOADBMODE = 2; 				// load on zero or per. (2), zero(0), per.(1)

EPwm2Regs.AQCTLA.bit.CAU = 2; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLA.bit.CAD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLA.bit.CBU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLA.bit.CBD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLA.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm2Regs.AQCTLA.bit.ZRO = 0;						// 0 Não faz nada no modo opdown


EPwm2Regs.AQCTLB.bit.CAU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLB.bit.CAD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLB.bit.CBU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLB.bit.CBD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm2Regs.AQCTLB.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm2Regs.AQCTLB.bit.ZRO = 0;						// 0 Não faz nada no modo opdown

EPwm2Regs.DBCTL.bit.IN_MODE=0;						//  Dead-band module
EPwm2Regs.DBCTL.bit.POLSEL=2;
EPwm2Regs.DBCTL.bit.OUT_MODE =DEAD_BAND_OUT; 					
EPwm2Regs.DBRED=DEAD_TIME;
EPwm2Regs.DBFED=DEAD_TIME;

EPwm2Regs.ETSEL.bit.SOCAEN=1;						// Habilita SOCB para SEQ2
EPwm2Regs.ETSEL.bit.SOCASEL=1;						// Gera no zero
EPwm2Regs.ETPS.bit.SOCAPRD=1;						// gera soc em todos os eventos


EALLOW;
EPwm2Regs.TZSEL.bit.OSHT1=1;						//  en
EPwm2Regs.TZCTL.bit.TZA  =2;						// Force PWMxA to low  state (2)
EPwm2Regs.TZCTL.bit.TZB	 =2;						// Force PWMxB to low state (2)
EPwm2Regs.TZFRC.bit.OST  =1;						// Forced trip in rectifier=1
EDIS;


//-------------------------------------------------------------------------------
// EPWM Module 4
//-------------------------------------------------------------------------------

EPwm4Regs.TBCTL.bit.HSPCLKDIV=0;					// Frequencia do clock/1
EPwm4Regs.TBCTL.bit.CLKDIV=0;						// pré escala 1/1

EPwm4Regs.TBPRD = TIMER_INV; 	 					// Period 
EPwm4Regs.TBPHS.half.TBPHS = PHASE_PWM4;			// Set Phase register
EPwm4Regs.TBCTL.bit.CTRMODE = 2;					// Symmetrical mode (up down)
EPwm4Regs.TBCTL.bit.PHSEN = 1; 						// Slave module (EPwm1 is Master)
EPwm4Regs.TBCTL.bit.PHSDIR =1;						// Count up after the Sync event
EPwm4Regs.TBCTL.bit.PRDLD = 0;						// Period timer is load at zero
EPwm4Regs.TBCTL.bit.SYNCOSEL = 0; 					// Sync when timer is 0
EPwm4Regs.TBCTL.bit.SWFSYNC =0;						// Do not force a Sync pulse
EPwm4Regs.TBCTL.bit.FREE_SOFT=2;					// runs free

EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0; 				// Shadow mode atualização não imediata
EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0; 				// Shadow mode atualização não imediata
EPwm4Regs.CMPCTL.bit.LOADAMODE = 2;					// load on zero or per. (2), zero(0), per.(1)
EPwm4Regs.CMPCTL.bit.LOADBMODE = 2; 				// load on zero or per. (2), zero(0), per.(1)

EPwm4Regs.AQCTLA.bit.CAU = 2; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLA.bit.CAD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLA.bit.CBU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLA.bit.CBD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLA.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm4Regs.AQCTLA.bit.ZRO = 0;						// 0 Não faz nada no modo opdown


EPwm4Regs.AQCTLB.bit.CAU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLB.bit.CAD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLB.bit.CBU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLB.bit.CBD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm4Regs.AQCTLB.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm4Regs.AQCTLB.bit.ZRO = 0;						// 0 Não faz nada no modo opdown

EPwm4Regs.DBCTL.bit.IN_MODE=0;						//  Dead-band module
EPwm4Regs.DBCTL.bit.POLSEL=2;	
EPwm4Regs.DBCTL.bit.OUT_MODE =DEAD_BAND_OUT; 					
EPwm4Regs.DBRED=DEAD_TIME;
EPwm4Regs.DBFED=DEAD_TIME;

EPwm4Regs.ETSEL.bit.SOCAEN=1;						// Habilita SOCB para SEQ2
EPwm4Regs.ETSEL.bit.SOCASEL=2;						// Gera no periodo
EPwm4Regs.ETPS.bit.SOCAPRD=1;						// gera soc em todos os evento

EALLOW;
EPwm4Regs.TZSEL.bit.OSHT1=1;						//  disable
EPwm4Regs.TZCTL.bit.TZA  =2;						// Force PWMxA to low  state (2)
EPwm4Regs.TZCTL.bit.TZB	 =2;						// Force PWMxB to low state (2)
EPwm4Regs.TZFRC.bit.OST  =1;						// Forced trip in rectifier=1
EDIS;

//-------------------------------------------------------------------------------
// EPWM Module 6
//-------------------------------------------------------------------------------

EPwm6Regs.TBCTL.bit.HSPCLKDIV=0;					// Frequencia do clock/1
EPwm6Regs.TBCTL.bit.CLKDIV=0;						// pré escala 1/1

EPwm6Regs.TBPRD = TIMER_INV; 	 					// Period 
EPwm6Regs.TBPHS.half.TBPHS = PHASE_PWM6;			// Set Phase register
EPwm6Regs.TBCTL.bit.CTRMODE = 2;					// Symmetrical mode (up down)
EPwm6Regs.TBCTL.bit.PHSEN = 1; 						// Slave module (EPwm1 is Master)
EPwm6Regs.TBCTL.bit.PHSDIR =1;						// Count up after the Sync event
EPwm6Regs.TBCTL.bit.PRDLD = 0;						// Period timer is load at zero
EPwm6Regs.TBCTL.bit.SYNCOSEL = 0; 					// Sync when timer is 0
EPwm6Regs.TBCTL.bit.SWFSYNC =0;						// Do not force a Sync pulse
EPwm6Regs.TBCTL.bit.FREE_SOFT=2;					// runs free

EPwm6Regs.CMPCTL.bit.SHDWAMODE = 0; 				// Shadow mode atualização não imediata
EPwm6Regs.CMPCTL.bit.SHDWBMODE = 0; 				// Shadow mode atualização não imediata
EPwm6Regs.CMPCTL.bit.LOADAMODE = 2;					// load on zero or per. (2), zero(0), per.(1)
EPwm6Regs.CMPCTL.bit.LOADBMODE = 2; 				// load on zero or per. (2), zero(0), per.(1)

EPwm6Regs.AQCTLA.bit.CAU = 2; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLA.bit.CAD = 1;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLA.bit.CBU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLA.bit.CBD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLA.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm6Regs.AQCTLA.bit.ZRO = 0;						// 0 Não faz nada no modo opdown


EPwm6Regs.AQCTLB.bit.CAU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLB.bit.CAD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLB.bit.CBU = 0; 						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLB.bit.CBD = 0;						// actions for EPWM1A -> 1 clear, 2 set, 3 toggle
EPwm6Regs.AQCTLB.bit.PRD = 0;						// 0 Não faz nada no modo opdown
EPwm6Regs.AQCTLB.bit.ZRO = 0;						// 0 Não faz nada no modo opdown

EPwm6Regs.DBCTL.bit.IN_MODE=0;						//  Dead-band module
EPwm6Regs.DBCTL.bit.POLSEL=2;
EPwm6Regs.DBCTL.bit.OUT_MODE =DEAD_BAND_OUT; 					
EPwm6Regs.DBRED=DEAD_TIME;
EPwm6Regs.DBFED=DEAD_TIME;

EPwm6Regs.ETSEL.bit.SOCBEN=0;						// Habilita SOCB para SEQ2
EPwm6Regs.ETSEL.bit.SOCBSEL=2;						// Gera no período
EPwm6Regs.ETPS.bit.SOCBPRD=1;						// gera soc em todos os eventos


EALLOW;
EPwm6Regs.TZSEL.bit.OSHT1=1;						//  disable
EPwm6Regs.TZCTL.bit.TZA  =2;						// Force PWMxA to low  state (2)
EPwm6Regs.TZCTL.bit.TZB	 =2;						// Force PWMxB to low state (2)
EPwm6Regs.TZFRC.bit.OST  =1;						// Forced trip in rectifier=1
EDIS;

//-------------------------------------------------------------------------------
// EPWM Sync
//-------------------------------------------------------------------------------

EALLOW;
SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC=1;	// for carriers sinc
EDIS;




}

