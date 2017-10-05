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
extern struct STAGE_STRUCT Stage;

#pragma CODE_SECTION(ESTAGIO_0, "ramfuncs");

void ESTAGIO_0()
{
	//-------------------------------------
	//LPF valfa - OBS inversão antes
	//-------------------------------------
	LPF1_g3.e1=LPF1_g3.e0;
	LPF1_g3.u1=LPF1_g3.u0;
	LPF1_g3.e0=pll.valfa;
	LPF1_g3.u0=LPF1_g3.e0*B0_LPF10+LPF1_g3.e1*B1_LPF10-LPF1_g3.u1*A1_LPF10;

	//-------------------------------------
	//LPF vbeta - OBS inversão antes
	//-------------------------------------
	LPF1_g4.e1=LPF1_g4.e0;
	LPF1_g4.u1=LPF1_g4.u0;
	LPF1_g4.e0=pll.vbeta;
	LPF1_g4.u0=LPF1_g4.e0*B0_LPF10+LPF1_g4.e1*B1_LPF10-LPF1_g4.u1*A1_LPF10;


	//*******************************************************//
	// State machine testes
	//*******************************************************//

	if(++CTRL.TIMER_E0>19980) // 0.5s
	{
		switch(temp.t1c) // Stage.State==0
		{
		case 0:// teste de cruzamento por zero
		{
			if(LPF1_g3.u1<0 && LPF1_g3.u0>0) // detecta cruzamento em Valfa
			{
				if(LPF1_g4.u0<0)
				{
					pll.ctrl|=1;                  // set flag de cruzamento por zero   = temp.t2c
				}
				temp.t1c=1;                    // pasa para próximo teste
				Stage.State=1;
			}
			break;
		}

		case 1: // teste de potências fictícias
		{
			if(inv.v_seqp>inv.v_seqn) pll.ctrl|=2;
			temp.t1c=2;
			Stage.State=2;
			break;
		}

		case 2:  // verificação amplitude seq +
		{

			if(inv.v_seqp>(0.8*190.52)){    // se seq positiva abaixo de 80% desliga
				 pll.ctrl|=4;
			}
			temp.t1c=3;                               // aqui poderia se incluir taxa de desbalanço
			Stage.State=3;
			break;
		}
		case 3:  // verificação final
		{
			if(pll.ctrl==7) // sequência é positiva!
			{
				pll.seq=0; // muda leitura de variáveis
				temp.t1i=32000; // força saída ??
				temp.t1c=4;
				Stage.State=4;
			}

			else if(pll.ctrl==0) // sequência é negativa
			{
				pll.seq=1; // muda leitura de variáveis
				temp.t1c=4;
				Stage.State=4;
			}
			else
				CTRL.STATE= 10; // ERRO
			    Stage.Value=10;

			break;
		}
		case 4:  // verificação final
		{
			if(CTRL.TIMER_E0>32000)
			{

				CTRL.STATE=1;  // vai para estagio 1
				Stage.Value=1;
				Stage.State=0;

				temp.t2c=0;
				temp.t1c=0;
			//	temp.t2c=0;

				LPF1_g1.e1 = 0;
				LPF1_g1.u0 = 0;
				LPF1_g1.u1 = 0;
				LPF1_g2.e1 = 0;
				LPF1_g2.u0 = 0;
				LPF1_g2.u1 = 0;
				LPF1_g3.e1 = 0;
				LPF1_g3.u0 = 0;
				LPF1_g3.u1 = 0;
				LPF1_g4.e1 = 0;
				LPF1_g4.u0 = 0;
				LPF1_g4.u1 = 0;
			}


			break;
		}


		} // fim switch
	} // fim if


}
//#############################################################################
// End of file 
//#############################################################################


