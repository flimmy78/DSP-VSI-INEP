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
#include "stdio.h"
#include "Define.h"
#include "Structs.h" 
#include "C28x_FPU_FastRTS.h"
#include <math.h>
#include "MSO_Coeff.h"

/*******************************************************************************/
/*		Protótipos das Funções 	 								   	   	  	   */
/*******************************************************************************/
extern void MODULATION(struct INVERSOR *inv);


extern struct INVERSOR inv;
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

extern double t, delt;
extern double *in, *out;

void ESTAGIO_2()
{

	//*******************************************************//
	// Geração dos sinais de referência Nominal
	//*******************************************************//
	/*
    if(temp.t3f>1.30) temp.t2f= (inv.w_avg-(inv.p_avg+2000.0)*0.0001);

    else temp.t2f=(inv.w_avg-(inv.p_avg)*0.0001);
	 */

	temp.t2f=inv.mgcc_wref;     //(inv.w_avg-(inv.p_avg)*0.0001);

	trig.wt+=temp.t2f*TS_PLL;

	if(trig.wt>PIX1) trig.wt = trig.wt - PIX2;

	sincos(trig.wt, &(trig.senoA), &(trig.coseA));
	sincos((trig.wt-2.09439510239319549230), &(trig.senoB), &(trig.coseB));
	sincos((trig.wt+2.09439510239319549230), &(trig.senoC), &(trig.coseC));


	// LPF1_g3.u0=0;  // TESTES CANCELA DROOP Q

	temp.t4f=inv.v_seqn*sin((trig.wt+inv.phi_seqn));
	temp.t5f=inv.v_seqn*cos((trig.wt+inv.phi_seqn));

	if(temp.t3f>2.10)
	{
		temp.t4f=0;
		temp.t5f=0;
	}

	// Testes--------------------

	inv.q_avg=0.0;
	temp.t4f=0.0;
	temp.t5f=0.0;

	//---------------------------

#if DROOP
	inv.valfa_refn =  (inv.vp-0.001*(inv.p_avg-inv.mgcc_pref))*trig.senoA;// +temp.t4f;
	inv.vbeta_refn = -(inv.vp-0.001*(inv.p_avg-inv.mgcc_pref))*trig.coseA;// +temp.t5f;
	//-------------------------------------------------------//
	// Impedância virtual e compensação harmônica de Lg
	//-------------------------------------------------------//
	inv.valfa_ref = inv.valfa_refn - 0.1*inv.ialfa_grid;
	inv.vbeta_ref = inv.vbeta_refn - 0.1*inv.ibeta_grid;
#else
	inv.valfa_ref = inv.vp*trig.senoA;
	inv.vbeta_ref = -inv.vp*trig.coseA;
#endif



	//*******************************************************//
	// Malha de Tensão
	//*******************************************************//

	inv.valfa_erro=(inv.valfa_ref-inv.valfa);
	inv.vbeta_erro=(inv.vbeta_ref-inv.vbeta);

	//--------------------------------------------------------/
	//Controlador de tensão eixo alfa
	//--------------------------------------------------------/

	// Fundamental
	PR1_alfa.e2+=PR1_alfa.e1*DELTA_PR1;
	PR1_alfa.e1+=PR1_alfa.e0*DELTA_PR1;
	PR1_alfa.e0= inv.valfa_erro-PR1_alfa.e1*A1_PR1-PR1_alfa.e2*A2_PR1;
	PR1_alfa.u0=PR1_alfa.e0*B0_PR1+PR1_alfa.e1*B1_PR1+PR1_alfa.e2*B2_PR1;

#if PR5CTRL 	// Quinta harmônica
	PR5_alfa.e2+=PR5_alfa.e1*DELTA_PR5;
	PR5_alfa.e1+=PR5_alfa.e0*DELTA_PR5;
	PR5_alfa.e0= inv.valfa_erro-PR5_alfa.e1*A1_PR5-PR5_alfa.e2*A2_PR5;
	PR5_alfa.u0=PR5_alfa.e0*B0_PR5+PR5_alfa.e1*B1_PR5+PR5_alfa.e2*B2_PR5;
#endif

#if PR7CTRL 	// Sétima harmônica
	PR7_alfa.e2+=PR7_alfa.e1*DELTA_PR7;
	PR7_alfa.e1+=PR7_alfa.e0*DELTA_PR7;
	PR7_alfa.e0= inv.valfa_erro-PR7_alfa.e1*A1_PR7-PR7_alfa.e2*A2_PR7;
	PR7_alfa.u0=PR7_alfa.e0*B0_PR7+PR7_alfa.e1*B1_PR7+PR7_alfa.e2*B2_PR7;
#endif

#if PR11CTRL	// Décima primeira harmônica
	PR11_alfa.e2+=PR11_alfa.e1*DELTA_PR11;
	PR11_alfa.e1+=PR11_alfa.e0*DELTA_PR11;
	PR11_alfa.e0= inv.valfa_erro-PR11_alfa.e1*A1_PR11-PR11_alfa.e2*A2_PR11;
	PR11_alfa.u0=PR11_alfa.e0*B0_PR11+PR11_alfa.e1*B1_PR11+PR11_alfa.e2*B2_PR11;
#endif

	inv.ialfa_ref= 0.1*inv.valfa_erro + 0.9*PR1_alfa.u0; //

#if PR5CTRL
	inv.ialfa_ref+=PR5_alfa.u0;
#endif
#if PR7CTRL
	inv.ialfa_ref+=PR7_alfa.u0;
#endif
#if PR11CTRL
	inv.ialfa_ref+=PR11_alfa.u0;
#endif



	//--------------------------------------------------------/
	//Controlador  Vbeta
	//--------------------------------------------------------/

	// Fundamental
	PR1_beta.e2+=PR1_beta.e1*DELTA_PR1;
	PR1_beta.e1+=PR1_beta.e0*DELTA_PR1;
	PR1_beta.e0=inv.vbeta_erro-PR1_beta.e1*A1_PR1-PR1_beta.e2*A2_PR1;
	PR1_beta.u0=PR1_beta.e0*B0_PR1+PR1_beta.e1*B1_PR1+PR1_beta.e2*B2_PR1;

#if PR5CTRL // Quinta harmônica
	PR5_beta.e2+=PR5_beta.e1*DELTA_PR5;
	PR5_beta.e1+=PR5_beta.e0*DELTA_PR5;
	PR5_beta.e0=inv.vbeta_erro-PR5_beta.e1*A1_PR5-PR5_beta.e2*A2_PR5;
	PR5_beta.u0=PR5_beta.e0*B0_PR5+PR5_beta.e1*B1_PR5+PR5_beta.e2*B2_PR5;
#endif

#if PR7CTRL // Sétima harmônica
	PR7_beta.e2+=PR7_beta.e1*DELTA_PR7;
	PR7_beta.e1+=PR7_beta.e0*DELTA_PR7;
	PR7_beta.e0=inv.vbeta_erro-PR7_beta.e1*A1_PR7-PR7_beta.e2*A2_PR7;
	PR7_beta.u0=PR7_beta.e0*B0_PR7+PR7_beta.e1*B1_PR7+PR7_beta.e2*B2_PR7;
#endif

#if PR11CTRL // Décima primeira harmônica
	PR11_beta.e2+=PR11_beta.e1*DELTA_PR11;
	PR11_beta.e1+=PR11_beta.e0*DELTA_PR11;
	PR11_beta.e0=inv.vbeta_erro-PR11_beta.e1*A1_PR11-PR11_beta.e2*A2_PR11;
	PR11_beta.u0=PR11_beta.e0*B0_PR11+PR11_beta.e1*B1_PR11+PR11_beta.e2*B2_PR11;
#endif

	inv.ibeta_ref= 0.1*inv.vbeta_erro + 0.9*PR1_beta.u0; //

#if PR5CTRL
	inv.ibeta_ref+=PR5_beta.u0;
#endif
#if PR7CTRL
	inv.ibeta_ref+=PR7_beta.u0;
#endif
#if PR11CTRL
	inv.ibeta_ref+=PR11_beta.u0;
#endif

	//*******************************************************//
	// Malha de corrente e amortecimento ativo
	//*******************************************************//



	//-----------------------------------------------
	//Filtro passa baixa
	//-----------------------------------------------
#if FPB // TODO: definir melhor quando utilizar os filtros
	LPF1_g4.e0= inv.ialfa_inv - inv.ialfa_grid;     // corrente no capacitor
	LPF1_g4.u0=LPF1_g4.e0*B0_LPF1+LPF1_g4.e1*B1_LPF1-LPF1_g4.u1*A1_LPF1;
	LPF1_g4.e1=LPF1_g4.e0;
	LPF1_g4.u1=LPF1_g4.u0;

	LPF1_g5.e0=inv.ibeta_inv - inv.ibeta_grid;
	LPF1_g5.u0=LPF1_g5.e0*B0_LPF1+LPF1_g5.e1*B1_LPF1-LPF1_g5.u1*A1_LPF1;
	LPF1_g5.e1=LPF1_g5.e0;
	LPF1_g5.u1=LPF1_g5.u0;

	//*******************************************************//
	// Sinais modulantes
	//*******************************************************//

	//--------------------------------------------------------/
	//Filtro passa baixa para resposta exponencial do soft starter de Z
	//--------------------------------------------------------/
	LPF1_g6.e0=1.0;
	LPF1_g6.u0=LPF1_g6.e0*B0_LPF1+LPF1_g6.e1*B1_LPF1-LPF1_g6.u1*A1_LPF1;
	LPF1_g6.e1=LPF1_g6.e0;
	LPF1_g6.u1=LPF1_g6.u0;
	//--------------------------------------------------------/

#endif


	// Controladores de corrente
	PR1i_alfa.e2+=PR1i_alfa.e1*DELTA_PR1i;
	PR1i_alfa.e1+=PR1i_alfa.e0*DELTA_PR1i;
	PR1i_alfa.e0= (inv.ialfa_ref-inv.ialfa_inv)-PR1i_alfa.e1*A1_PR1i-PR1i_alfa.e2*A2_PR1i;
	PR1i_alfa.u0=PR1i_alfa.e0*B0_PR1i+PR1i_alfa.e1*B1_PR1i+PR1i_alfa.e2*B2_PR1i;

	PR1i_beta.e2+=PR1i_beta.e1*DELTA_PR1i;
	PR1i_beta.e1+=PR1i_beta.e0*DELTA_PR1i;
	PR1i_beta.e0=(inv.ibeta_ref-inv.ibeta_inv)-PR1i_beta.e1*A1_PR1i-PR1i_beta.e2*A2_PR1i;
	PR1i_beta.u0=PR1i_beta.e0*B0_PR1i+PR1i_beta.e1*B1_PR1i+PR1i_beta.e2*B2_PR1i;

	//--------------------------------------------------------/

#if CLOSEDLOOP  

	inv.dalfa =   inv.valfa_ref + PR1i_alfa.u0*0.25;  //
	inv.dbeta =   inv.vbeta_ref + PR1i_beta.u0*0.25;  //

#else

	inv.dalfa =   inv.valfa_ref;  //
	inv.dbeta =   inv.vbeta_ref;  //

#endif       


}
//#############################################################################
// End of file 
//#############################################################################




