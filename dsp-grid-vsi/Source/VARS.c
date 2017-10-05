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
#include "Define.h"
#include "Structs.h" 
#include "MSO.h"
#include "MSO_Coeff.h"
#include "Prototipos.h"	

#if GRIDVSI
#include "GridVsiFunctions.h"
#endif


extern struct INVERSOR inv;
extern struct MEAS_RMS rms;
#if UseGraphs
extern struct GRAFICOS graf;
#endif
extern struct CONTROLE CTRL;
extern struct TRIGONOMETRICO trig;
extern struct PLL pll;
extern struct PI PI_alfa,PI_beta;
extern struct PI pi_vdc;
extern struct PID pid_ialfa,pid_ibeta;

extern struct PR PR1_alfa,PR1_beta;
extern struct PR PR5_alfa,PR5_beta;
extern struct PR PR7_alfa,PR7_beta;
extern struct PR PR11_alfa,PR11_beta;
extern struct PR PR13_alfa,PR13_beta;
extern struct PR PR1i_alfa,PR1i_beta;
extern struct PR PRS_zalfa, PRS_zbeta;
extern struct PR CI_alfa, CI_beta;

extern struct LPF1 LPF1_g1, LPF1_g2, LPF1_g3, LPF1_g4, LPF1_g5, LPF1_g6;
extern struct LPF2 LPF2_g1,LPF2_g2,LPF2_g3,LPF2_g4;

extern struct GTF1 CVAC_alfa,CVAC_beta;

extern struct TEMP temp;
extern struct TESTES teste;


#if GRIDVSI
	extern struct DSOG_PLL dsog_pll;
	extern struct DSOG_PLL_INPUTS dsog_pll_in;
	extern struct DSOGPLL_OUTPUTS dsog_pll_out;
	extern struct IPC ipc;
	extern struct SVM svm;
	extern struct RPC rpc;
	extern struct CCL ccl;
	extern struct VCL  vcl;
	extern struct CRC crc;
	extern struct AICL aicl;
	extern struct LVRT lvrt;
	extern struct FREQ_PTC freq_ptc;
#endif



INIT_VARIAVEIS()
{


	LED_RED=0;
	LED_GREEN=0;
	LED_ORANGE=0;
	LED_YELLOW=0;

	//-------------------------------------------------------------------------------
	// Debug
	//-------------------------------------------------------------------------------
#if UseGraphs
	graf.dec=0;
	graf.g=0;
/*
	graf.g1=&inv.valfa;
	graf.g2=&inv.vbeta;
	graf.g3=&inv.vdc;
	*/
	/*
	graf.g1=&inv.ialfa_inv;
	graf.g2=&inv.ibeta_inv;
	graf.g3=&inv.vdc;
	 */

	/*
	graf.g1=&inv.valfa;
	graf.g2=&inv.ialfa_grid;
	graf.g3=&inv.ialfa_inv;
	 */

	/*
	graf.g1=&inv.valfa_refn;
	graf.g2=&inv.vbeta_refn;
	graf.g3=&pll.wt;
	 */
/*
	graf.g1=&inv.da;
	graf.g2=&inv.db;
	graf.g3=&inv.dc;
*/
	graf.g1=&inv.valfa;
	graf.g2=&inv.theta;
	graf.g3=&inv.ialfa_ref;


#endif
	//-------------------------------------------------------------------------------
	// Converter
	//-------------------------------------------------------------------------------

	inv.m=0.8;
	inv.da=0.0;
	inv.db=0.0;
	inv.dc=0.0;

	inv.ib_inv=0.0;
	inv.ib_grid=0.0;
	inv.ic_inv=0.0;
	inv.ic_grid=0.0;

	inv.vab=0.0;
	inv.vca=0.0;

	inv.vp=190.52; // Vref Droop

	inv.vdc=0.0;
	inv.dalfa=0;
	inv.dbeta=0;


#if GRIDVSI
	//-------------------------------------------------------------------------------
	//GRID-TIE VSI
	//-------------------------------------------------------------------------------
	inv.valfa_p=0;
	inv.valfa_n=0;
	inv.vbeta_p=0;
	inv.vbeta_n=0;
	inv.norma_vp=0;
	inv.norma_vn=0;
	inv.norma_nominal=220;
	inv.theta=0;
	inv.w=0;
	inv.f=0;
	inv.pll_sinc_ok=0;
	inv.p_ref=0;
	inv.q_ref=0;
	inv.vdip=0;
	inv.lvrt_disconnect=0;
	inv.ialfa_islanding_ref=0;
	inv.ibeta_islanding_ref=0;
	inv.first_time = 0;
	inv.Estado=0;
	inv.contatora_bypass = 0;
	inv.contatora_inv=0;
	inv.control_on = 0;
	inv.enable = 0;

	//Inicializacao das funcoes
	DSOG_PLL_Init();
	Instantaneous_Power_Calculation_Init();
	Space_Vector_Modulation_Init();
	Reactive_Power_Compensation_Init();
	Current_Control_Loop_Init();
	Voltage_Control_Loop_Init();
	Current_Reference_Calculation_Init();
	Anti_Islanding_Control_Loop_Init();
	Anti_Islanding_Control_Loop_Init();
	LVRT_protection_Init();
	FREQ_Protection_Init();
#endif
	//-------------------------------------------------------------------------------
	// Converter Control
	//-------------------------------------------------------------------------------

	CTRL.STATE=0;
	CTRL.MF=0; // Era -5
	CTRL.AD_EOC=0;
	CTRL.ENABLE=0;
	CTRL.PWM=0;	
	CTRL.TIMER_E0=0;
	CTRL.SW_CNT=0;

	RELAY=1; // Aciona relé geral da placa de filtro
	//--------------------------------------------------------/
	//Circuito de sincronismo PLL
	//--------------------------------------------------------/
	pll.e0 = 0;
	pll.e1 = 0;
	pll.w =CI_PLL;
	pll.wt = 0;
	pll.seq=0;  // inicial leitura como seq de fase positiva
	pll.ctrl=0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Controlador de corrente P+BRF na ressonância
	//--------------------------------------------------------/
	CI_alfa.e0 = 0;
	CI_alfa.e1 = 0;
	CI_alfa.e2 = 0;
	CI_alfa.u0 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Controlador de corrente P+BRF na ressonância
	//--------------------------------------------------------/
	CI_beta.e0 = 0;
	CI_beta.e1 = 0;
	CI_beta.e2 = 0;
	CI_beta.u0 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Controlador PR alfa
	//--------------------------------------------------------/
	PI_alfa.e0 = 0;
	PI_alfa.e1 = 0;
	PI_alfa.u0 = 0;

	PR1_alfa.e0 = 0;
	PR1_alfa.e1 = 0;
	PR1_alfa.e2 = 0;
	PR1_alfa.u0 = 0;

	PR5_alfa.e0 = 0;
	PR5_alfa.e1 = 0;
	PR5_alfa.e2 = 0;
	PR5_alfa.u0 = 0;

	PR7_alfa.e0 = 0;
	PR7_alfa.e1 = 0;
	PR7_alfa.e2 = 0;
	PR7_alfa.u0 = 0;

	PR11_alfa.e0 = 0;
	PR11_alfa.e1 = 0;
	PR11_alfa.e2 = 0;
	PR11_alfa.u0 = 0;

	PR13_alfa.e0 = 0;
	PR13_alfa.e1 = 0;
	PR13_alfa.e2 = 0;
	PR13_alfa.u0 = 0;

	PR1i_alfa.e0 = 0;
	PR1i_alfa.e1 = 0;
	PR1i_alfa.e2 = 0;
	PR1i_alfa.u0 = 0;

	pid_ialfa.e0 = 0;
	pid_ialfa.x0 = 0;
	pid_ialfa.x1 = 0;
	pid_ialfa.x2 = 0;
	pid_ialfa.u0 = 0;

	//--------------------------------------------------------/
	//Controlador PR beta
	//--------------------------------------------------------/

	PI_beta.e0 = 0;
	PI_beta.e1 = 0;
	PI_beta.u0 = 0;

	PR1_beta.e0 = 0;
	PR1_beta.e1 = 0;
	PR1_beta.e2 = 0;
	PR1_beta.u0 = 0;

	PR5_beta.e0 = 0;
	PR5_beta.e1 = 0;
	PR5_beta.e2 = 0;
	PR5_beta.u0 = 0;

	PR7_beta.e0 = 0;
	PR7_beta.e1 = 0;
	PR7_beta.e2 = 0;
	PR7_beta.u0 = 0;

	PR11_beta.e0 = 0;
	PR11_beta.e1 = 0;
	PR11_beta.e2 = 0;
	PR11_beta.u0 = 0;

	PR13_beta.e0 = 0;
	PR13_beta.e1 = 0;
	PR13_beta.e2 = 0;
	PR13_beta.u0 = 0;

	PR1i_beta.e0 = 0;
	PR1i_beta.e1 = 0;
	PR1i_beta.e2 = 0;
	PR1i_beta.u0 = 0;

	pid_ibeta.e0 = 0;
	pid_ibeta.x0 = 0;
	pid_ibeta.x1 = 0;
	pid_ibeta.x2 = 0;
	pid_ibeta.u0 = 0;
	//--------------------------------------------------------/
	//Filtro passa faixa para impedância virtual
	//--------------------------------------------------------/
	PRS_zalfa.e0 = 0;
	PRS_zalfa.e1 = 0;
	PRS_zalfa.e2 = 0;
	PRS_zalfa.u0 = 0;
	//--------------------------------------------------------/
	PRS_zbeta.e0 = 0;
	PRS_zbeta.e1 = 0;
	PRS_zbeta.e2 = 0;
	PRS_zbeta.u0 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Controlador lag para vac
	//--------------------------------------------------------/
	CVAC_alfa.e0 = 0;
	CVAC_alfa.e1 = 0;
	CVAC_alfa.u0 = 0;
	CVAC_alfa.u1 = 0;

	CVAC_beta.e0 = 0;
	CVAC_beta.e1 = 0;
	CVAC_beta.u0 = 0;
	CVAC_beta.u1 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 1
	//--------------------------------------------------------/
	LPF1_g1.e0 = 0;
	LPF1_g1.e1 = 0;
	LPF1_g1.u0 = 0;
	LPF1_g1.u1 = 0;
	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 2
	//--------------------------------------------------------/
	LPF1_g2.e0 = 0;
	LPF1_g2.e1 = 0;
	LPF1_g2.u0 = 0;
	LPF1_g2.u1 = 0;
	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 3
	//--------------------------------------------------------/
	LPF1_g3.e0 = 0;
	LPF1_g3.e1 = 0;
	LPF1_g3.u0 = 0;
	LPF1_g3.u1 = 0;
	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 4
	//--------------------------------------------------------/
	LPF1_g4.e0 = 0;
	LPF1_g4.e1 = 0;
	LPF1_g4.u0 = 0;
	LPF1_g4.u1 = 0;
	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 5
	//--------------------------------------------------------/
	LPF1_g5.e0 = 0;
	LPF1_g5.e1 = 0;
	LPF1_g5.u0 = 0;
	LPF1_g5.u1 = 0;
	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 6
	//--------------------------------------------------------/
	LPF1_g6.e0 = 0;
	LPF1_g6.e1 = 0;
	LPF1_g6.u0 = 0;
	LPF1_g6.u1 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Filtro passa-baixa genérico 1 segunda ordem
	//--------------------------------------------------------/
	LPF2_g1.x0 = 0;
	LPF2_g1.x1 = 0;
	LPF2_g1.x2 = 0;
	//--------------------------------------------------------/
	LPF2_g2.x0 = 0;
	LPF2_g2.x1 = 0;
	LPF2_g2.x2 = 0;
	//--------------------------------------------------------/
	LPF2_g3.x0 = 0;
	LPF2_g3.x1 = 0;
	LPF2_g3.x2 = 0;
	//--------------------------------------------------------/
	LPF2_g4.x0 = 0;
	LPF2_g4.x1 = 0;
	LPF2_g4.x2 = 0;
	//--------------------------------------------------------/


	inv.valfa_acc=0;
	inv.vbeta_acc=0;
	inv.ialfa_grid_acc=0;
	inv.ibeta_grid_acc=0;
	inv.count=0;
	inv.vp=190.5255;
	inv.s=2500;


	inv.mgcc_vref=0.0;
	//-------------------------------------------------------------------------------
	// Calibration & offset
	//-------------------------------------------------------------------------------
	/*
	calib.e0=0;
	calib.e1=0;
	calib.e2=0;
	calib.u0=0;
	 */


	//-------------------------------------------------------------------------------
	// PI_vdc
	//-------------------------------------------------------------------------------

	pi_vdc.e0=0;
	pi_vdc.e1=0;
	pi_vdc.u0=0;

	//-------------------------------------------------------------------------------
	// Protections values
	//-------------------------------------------------------------------------------

	temp.t1c=0;
	temp.t2c=0;
	temp.t3c=0;

	temp.t1f=0;
	temp.t2f=0;
	temp.t3f=0;

	temp.t1i=0;
	temp.t2i=0;
	temp.t3i=0;


	//-------------------------------------------------------------------------------
	// Trig
	//-------------------------------------------------------------------------------
	trig.wt=0;




	//-------------------------------------------------------------------------------
	// RMS Calculation
	//-------------------------------------------------------------------------------
	rms.state=1;

	rms.acc1=0;
	rms.acc2=0;
	rms.acc3=0;
	rms.acc4=0;

	for(rms.idx1=0;rms.idx1<170;rms.idx1++)
	{
		rms.buff1[rms.idx1]=0;
		rms.buff2[rms.idx1]=0;
		rms.buff3[rms.idx1]=0;
		rms.buff4[rms.idx1]=0;
	}

	rms.idx1=0;
	rms.idx2=0;
	rms.idx3=0;
	rms.idx4=0;

}



INIT_COM_REGISTERS()
{

	inv.iac_trip_level=0;
	inv.vdc_trip_level=0;
	inv.vac_trip_level=0;


}

RE_INIT_VARIAVEIS()
{
	// aqui deve-se  reiniciar as variáveis dos controladores
	inv.da=0.0;
	inv.db=0.0;
	inv.dc=0.0;


	CTRL.SW_CNT=0;
	//--------------------------------------------------------/
	//Controlador de corrente P+BRF na ressonância
	//--------------------------------------------------------/
	CI_alfa.e0 = 0;
	CI_alfa.e1 = 0;
	CI_alfa.e2 = 0;
	CI_alfa.u0 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Controlador de corrente P+BRF na ressonância
	//--------------------------------------------------------/
	CI_beta.e0 = 0;
	CI_beta.e1 = 0;
	CI_beta.e2 = 0;
	CI_beta.u0 = 0;
	//--------------------------------------------------------/

	//--------------------------------------------------------/
	//Controlador PR alfa
	//--------------------------------------------------------/
	PI_alfa.e0 = 0;
	PI_alfa.e1 = 0;
	PI_alfa.u0 = 0;

	PR1_alfa.e0 = 0;
	PR1_alfa.e1 = 0;
	PR1_alfa.e2 = 0;
	PR1_alfa.u0 = 0;

	PR5_alfa.e0 = 0;
	PR5_alfa.e1 = 0;
	PR5_alfa.e2 = 0;
	PR5_alfa.u0 = 0;

	PR7_alfa.e0 = 0;
	PR7_alfa.e1 = 0;
	PR7_alfa.e2 = 0;
	PR7_alfa.u0 = 0;

	PR11_alfa.e0 = 0;
	PR11_alfa.e1 = 0;
	PR11_alfa.e2 = 0;
	PR11_alfa.u0 = 0;

	PR13_alfa.e0 = 0;
	PR13_alfa.e1 = 0;
	PR13_alfa.e2 = 0;
	PR13_alfa.u0 = 0;

	PR1i_alfa.e0 = 0;
	PR1i_alfa.e1 = 0;
	PR1i_alfa.e2 = 0;
	PR1i_alfa.u0 = 0;

	pid_ialfa.e0 = 0;
	pid_ialfa.x0 = 0;
	pid_ialfa.x1 = 0;
	pid_ialfa.x2 = 0;
	pid_ialfa.u0 = 0;

	//--------------------------------------------------------/
	//Controlador PR beta
	//--------------------------------------------------------/

	PI_beta.e0 = 0;
	PI_beta.e1 = 0;
	PI_beta.u0 = 0;

	PR1_beta.e0 = 0;
	PR1_beta.e1 = 0;
	PR1_beta.e2 = 0;
	PR1_beta.u0 = 0;

	PR5_beta.e0 = 0;
	PR5_beta.e1 = 0;
	PR5_beta.e2 = 0;
	PR5_beta.u0 = 0;

	PR7_beta.e0 = 0;
	PR7_beta.e1 = 0;
	PR7_beta.e2 = 0;
	PR7_beta.u0 = 0;

	PR11_beta.e0 = 0;
	PR11_beta.e1 = 0;
	PR11_beta.e2 = 0;
	PR11_beta.u0 = 0;

	PR13_beta.e0 = 0;
	PR13_beta.e1 = 0;
	PR13_beta.e2 = 0;
	PR13_beta.u0 = 0;

	PR1i_beta.e0 = 0;
	PR1i_beta.e1 = 0;
	PR1i_beta.e2 = 0;
	PR1i_beta.u0 = 0;

	pid_ibeta.e0 = 0;
	pid_ibeta.x0 = 0;
	pid_ibeta.x1 = 0;
	pid_ibeta.x2 = 0;
	pid_ibeta.u0 = 0;
	//--------------------------------------------------------/
	//Filtro passa faixa para impedância virtual
	//--------------------------------------------------------/
	PRS_zalfa.e0 = 0;
	PRS_zalfa.e1 = 0;
	PRS_zalfa.e2 = 0;
	PRS_zalfa.u0 = 0;
	//--------------------------------------------------------/
	PRS_zbeta.e0 = 0;
	PRS_zbeta.e1 = 0;
	PRS_zbeta.e2 = 0;
	PRS_zbeta.u0 = 0;
	//--------------------------------------------------------/
}



























