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
/*
OBSERVAÇÕES: 																	
1- As correntes ib_grid e ic_grid estão trocadas no hardware e serão corrigidas 
   diretamente e unicametne neste arquivo.
2- As correntes do inversor são positivas qdo entram neste, diferentemente das
   da placa de filtro.

|______________________________________________________________________________*/
/*******************************************************************************/
/*		Arquivos Header						     		  					   */
/*******************************************************************************/

#include "DSP2833x_Device.h"
#include "Define.h" 

/*******************************************************************************/
/*		Definições						     		  					   */
/*******************************************************************************/

#define ADC_usDELAY5  10000		// 5ms
#define ADC_usDELAY2  50000		// O clock de entrada é de 150Mhz


/*
A0 0x0
A1 0x1
A2 0x2
A3 0x3
A4 0x4
A5 0x5
A6 0x6
A7 0x7
B0 0x8
B1 0x9
B2 0xA
B3 0xB
B4 0xC
B5 0xD
B6 0xE
B7 0xF
*/



#define AD_Vdc		0x5
#define AD_Vba		0x4
#define AD_Vca		0xC
#define AD_ibinv	0x1
#define AD_icinv	0x9
#define AD_ibgrid	0x2		// Observe que foram alterados pois no projeto estão
#define AD_icgrid	0x3		// trocados	

INIT_ADC(void)
{

extern void DSP28x_usDelay(Uint32 Count);
//-------------------------------------------------------------------------------
// Bandgap and reference circuits 
//-------------------------------------------------------------------------------

    AdcRegs.ADCTRL3.all = 0x00E0;  	  	// Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY5);   // Delay before converting ADC channels -> 

//-------------------------------------------------------------------------------
// General Configurations
//-------------------------------------------------------------------------------
	
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;		// Modo de amostragem sequencial =0 , simultaneo =1
    AdcRegs.ADCMAXCONV.all =0x000A;			// 11 conversions 


/*___Determinação dos canais do Mux na Sequencia de Conversões_____*/

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = AD_ibinv;  	//	setup for
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = AD_icinv;  	//	setup for
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = AD_ibgrid;  	//	setup for
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = AD_icgrid;  	//	setup for  

    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = AD_Vdc;  		//	setup for
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = AD_Vba;  		//	setup for          
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = AD_Vca;  		//	setup for
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = AD_ibinv;  	//	setup for  

    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = AD_icinv;  	//	setup for
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = AD_ibgrid;  	//	setup for          
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = AD_icgrid;  	//	setup for


/*___Configurações do controle do AD_____*/

    AdcRegs.ADCTRL1.bit.RESET=0;    	//
	AdcRegs.ADCTRL1.bit.SUSMOD=1; 		// A suspensão da emulação é ignorada
	AdcRegs.ADCTRL1.bit.CONT_RUN=0;		// Reseta a sequencia no modo continuo (nao tem relevancia no modo atual)
    AdcRegs.ADCTRL1.bit.CPS=0;			// Divide a frequencia do HSPCLK (0=/1 e 1=/2)
    AdcRegs.ADCTRL1.bit.SEQ_CASC=1;		// Modo com dois seqs. (Cascateado=1)
    AdcRegs.ADCTRL1.bit.ACQ_PS=2;		// A janela de aquisição é de 2+1 periodos do ADCCLK
    AdcRegs.ADCTRL1.bit.SEQ_OVRD=0;
        
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ=0;	// Se 1 permite que um evento Epwm dispare a seq no modo cascateado
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1=1;	// SEQ 1 pode ser iniciada pelo epwm através do SOC A
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2=0;	// SEQ 2 pode ser iniciada pelo epwm através do SOCB
	AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1=0;
	AdcRegs.ADCTRL2.bit.RST_SEQ1=0;			// Reseta o sequenciador 1
	AdcRegs.ADCTRL2.bit.RST_SEQ2=0;			// Reseta o sequenciador 2
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1=0;		//des habilita pedido de interrupção  pela SEQ1
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1=1;		// INT SEQ1 é setado em todas as sequencias
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2=0;		// Desabilita o pedido de INT pelo SEQ2

	AdcRegs.ADCTRL3.bit.ADCCLKPS= 3; 		// Divisor do clock {HSPCLK/[2*3*(ADCCLKPS+)1]} o HSPCLK é de 150MHz, logo escreve-se 3 e fica 25MHz, a ser dividido por 1 no CPS

}



























