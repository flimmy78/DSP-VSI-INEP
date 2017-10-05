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

extern struct PR PR1_alfa,PR1_beta;
extern struct PR PR5_alfa,PR5_beta;
extern struct PR PR7_alfa,PR7_beta;
extern struct PR PR11_alfa,PR11_beta;
extern struct PR PR13_alfa,PR13_beta;
extern struct PR PR1i_alfa,PR1i_beta;
extern struct PR PRS_zalfa, PRS_zbeta;

extern struct LPF1 LPF1_g1, LPF1_g2, LPF1_g3, LPF1_g4, LPF1_g5;
extern struct LPF2 LPF2_g1,LPF2_g2,LPF2_g3,LPF2_g4;

extern struct GTF1 CVAC_alfa,CVAC_beta;

extern struct TEMP temp;

void ESTAGIO_1()
{

//*******************************************************//
// Geração dos sinais de referência Nominal
//*******************************************************//
                                                                                     
	trig.wt=pll.wt;
		
	sincos(trig.wt, &(trig.senoA), &(trig.coseA));
	sincos((trig.wt-2.09439510239319549230), &(trig.senoB), &(trig.coseB));
	sincos((trig.wt+2.09439510239319549230), &(trig.senoC), &(trig.coseC));

    inv.phi_seqn=0; // OBS Cancela ação

    temp.t4f=inv.v_seqn*sin((trig.wt+inv.phi_seqn));
    temp.t5f=inv.v_seqn*cos((trig.wt+inv.phi_seqn));


    inv.valfa_refn =  (inv.vp)*trig.senoA +temp.t4f;
    inv.vbeta_refn = -(inv.vp)*trig.coseA +temp.t5f;      

   
//-------------------------------------------------------//
// Impedância virtual e compensação harmônica de Lg
//-------------------------------------------------------// 

   inv.valfa_ref = inv.valfa_refn + 0.002*377.0*inv.ibeta_grid;
   inv.vbeta_ref = inv.vbeta_refn - 0.002*377.0*inv.ialfa_grid;

//*******************************************************//
// Malha de Tensão
//*******************************************************//


//*******************************************************//
// Malha de corrente e amortecimento ativo
//*******************************************************//

    
    PR1i_alfa.e2+=PR1i_alfa.e1*DELTA_PR1i;
    PR1i_alfa.e1+=PR1i_alfa.e0*DELTA_PR1i;
    PR1i_alfa.e0= (0.0-inv.ialfa_inv)-PR1i_alfa.e1*A1_PR1i-PR1i_alfa.e2*A2_PR1i;
    PR1i_alfa.u0=PR1i_alfa.e0*B0_PR1i+PR1i_alfa.e1*B1_PR1i+PR1i_alfa.e2*B2_PR1i;

    PR1i_beta.e2+=PR1i_beta.e1*DELTA_PR1i;
    PR1i_beta.e1+=PR1i_beta.e0*DELTA_PR1i;
    PR1i_beta.e0=(0.0-inv.ibeta_inv)-PR1i_beta.e1*A1_PR1i-PR1i_beta.e2*A2_PR1i;
    PR1i_beta.u0=PR1i_beta.e0*B0_PR1i+PR1i_beta.e1*B1_PR1i+PR1i_beta.e2*B2_PR1i;

//*******************************************************//
// Sinais modulantes
//*******************************************************// 
  
    inv.dalfa =   inv.valfa_ref + PR1i_alfa.u0*1.0 -1.0*inv.ialfa_inv;  
    inv.dbeta =   inv.vbeta_ref + PR1i_beta.u0*1.0 -1.0*inv.ibeta_inv; 
  
}
//#############################################################################
// End of file 
//#############################################################################
