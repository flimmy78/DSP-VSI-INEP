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
#include "GridVsiFunctions.h"

/*******************************************************************************/
/*		Defines				 	 								   	   	  	   */
/*******************************************************************************/
#define	Tax	5e-005
#define	Kp_pr	0.0107
#define	b0_pr	0.000395364879168612
#define	b1_pr	0
#define	b2_pr	-0.000395364879168612
#define	a1_pr	-1.99964471580197
#define	a2_pr	0.999999990000888
#define	b0_pr3	0.000395084152756858
#define	b1_pr3	0
#define	b2_pr3	-0.000395084152756858
#define	a1_pr3	-1.99680479256013
#define	a2_pr3	0.999999990007988
#define	b0_pr4	0.000394838843966139
#define	b1_pr4	0
#define	b2_pr4	-0.000394838843966139
#define	a1_pr4	-1.99432316594068
#define	a2_pr4	0.999999990014192
#define	b0_pr5	0.000394523894205798
#define	b1_pr5	0
#define	b2_pr5	-0.000394523894205798
#define	a1_pr5	-1.99113702774009
#define	a2_pr5	0.999999990022157
#define	b0_pr7	0.000393686479385537
#define	b1_pr7	0
#define	b2_pr7	-0.000393686479385537
#define	a1_pr7	-1.98266545644667
#define	a2_pr7	0.999999990043336
#define	b0_pr11	0.000391195429879457
#define	b1_pr11	0
#define	b2_pr11	-0.000391195429879457
#define	a1_pr11	-1.95746515789019
#define	a2_pr11	-1.95746515789019
#define	b0_pr15	0.000387652397058434
#define	b1_pr15	0
#define	b2_pr15	-0.000387652397058434
#define	a1_pr15	-1.92162264064304
#define	a2_pr15	1
#define	b0_pb_30Hz	0
#define	b1_pb_30Hz	0.00662020521206189
#define	b2_pb_30Hz	0.00662020521206189
#define	a1_pb_30Hz	1
#define	a2_pb_30Hz	-0.986759589575876
#define	b0_v_aw	2.00125
#define	b1_v_aw	-1.99875
#define	a1_v_aw	-1
#define	kp_v_aw	2
#define	b0_notch_60Hz	0.00469007920132078
#define	b1_notch_60Hz	0
#define	b2_notch_60Hz	-0.00469007920132078
#define	a1_notch_60Hz	-1.99044302977699
#define	a2_notch_60Hz	0.990619841597358
#define	b0_v_aw2	1.000025
#define	b1_v_aw2	-0.999975
#define	a1_v_aw2	-1
#define	kp_v_aw2	1
#define	b0_pb_360Hz	0.00933349559248204
#define	b1_pb_360Hz	0
#define	b2_pb_360Hz	-0.00933349559248204
#define	a1_pb_360Hz	-1.97992555083812
#define	a2_pb_360Hz	0.981333008815036
#define	b0_pb_420Hz	0.00932365360450233
#define	b1_pb_420Hz	0
#define	b2_pb_420Hz	-0.00932365360450233
#define	a1_pb_420Hz	-1.97572879743064
#define	a2_pb_420Hz	0.981352692790995



#if FLASH

#pragma CODE_SECTION(DSOG_PLL, "ramfuncs");
#pragma CODE_SECTION(Voltage_Control_Loop, "ramfuncs");
#pragma CODE_SECTION(Reactive_Power_Compensation, "ramfuncs");
#pragma CODE_SECTION(Current_Reference_Calculation, "ramfuncs");
#pragma CODE_SECTION(Anti_Islanding_Control_Loop, "ramfuncs");
#pragma CODE_SECTION(Current_Control_Loop, "ramfuncs");
#pragma CODE_SECTION(Instantaneous_Power_Calculation, "ramfuncs");
#pragma CODE_SECTION(LVRT_protection, "ramfuncs");
#pragma CODE_SECTION(FREQ_Protection, "ramfuncs");



#pragma DATA_SECTION(dsog_pll , "DATARAM");
#pragma DATA_SECTION(dsog_pll_in , "DATARAM");
#pragma DATA_SECTION(dsog_pll_out , "DATARAM");
#pragma DATA_SECTION(vcl , "DATARAM");
#pragma DATA_SECTION(rpc , "DATARAM");
#pragma DATA_SECTION(crc , "DATARAM");
#pragma DATA_SECTION(aicl , "DATARAM");
#pragma DATA_SECTION(ipc , "DATARAM");
#pragma DATA_SECTION(lvrt , "DATARAM");
#pragma DATA_SECTION(freq_ptc , "DATARAM");

#endif



/*******************************************************************************/
/*		Protótipos das Funções 	 								   	   	  	   */
/*******************************************************************************/

struct DSOG_PLL dsog_pll;
struct DSOG_PLL_INPUTS dsog_pll_in;
struct DSOGPLL_OUTPUTS dsog_pll_out;
struct IPC ipc;
struct SVM svm;
struct RPC rpc;
struct CCL ccl;
struct VCL  vcl;
struct CRC crc;
struct AICL aicl;
struct LVRT lvrt;
struct FREQ_PTC freq_ptc;


/*******************************************************************************/
/*		DSOG_PLL 	 								   	   	  	  			   */
/*******************************************************************************/




void DSOG_PLL_Init(void)
{

    dsog_pll.count_pll=0;
    dsog_pll.f_pll=0;
    dsog_pll.pll_sinc_ok=0;

    //Inicializar com os parâmetros do filtro discretizado
    dsog_pll.b0_pb = b0_pb_30Hz;
    dsog_pll.b1_pb = b1_pb_30Hz;
    dsog_pll.b2_pb = b2_pb_30Hz;
    dsog_pll.a1_pb = a1_pb_30Hz;
    dsog_pll.a2_pb = a2_pb_30Hz;
    dsog_pll.Ts = Tsample;

    dsog_pll.count_theta=1;
    dsog_pll.count_theta2=1;
    dsog_pll.Va = 0;
    dsog_pll.Vb = 0;
    dsog_pll.Vc = 0;
    dsog_pll.Valpha = 0;
    dsog_pll.Vbeta = 0;
    dsog_pll.erro_alpha = 0;
    dsog_pll.erro_beta = 0;
    dsog_pll.erro_fll = 0;
    dsog_pll.Valpha_out = 0;
    dsog_pll.Vbeta_out = 0;
    dsog_pll.erro_alpha_1 = 0;
    dsog_pll.erro_beta_1 = 0;
    dsog_pll.Valpha_out_90 = 0;
    dsog_pll.Vbeta_out_90 = 0;
    dsog_pll.w_pll = 0;
    dsog_pll.uk_int1[0] = 0;
    dsog_pll.yk_int1[0] = 0;
    dsog_pll.yk_int1[1] = 0;
    dsog_pll.uk_int2[0] = 0;
    dsog_pll.yk_int2[0] = 0;
    dsog_pll.yk_int2[1] = 0;
    dsog_pll.uk_int3[0] = 0;
    dsog_pll.yk_int3[0] = 0;
    dsog_pll.yk_int3[1] = 0;
    dsog_pll.uk_int4[0] = 0;
    dsog_pll.yk_int4[0] = 0;
    dsog_pll.yk_int4[1] = 0;
    dsog_pll.uk_int5[0] = 0;
    dsog_pll.yk_int5[0] = 0;
    dsog_pll.yk_int5[1] = 0;
    dsog_pll.Valpha_p = 0;
    dsog_pll.Valpha_n = 0;
    dsog_pll.Vbeta_p = 0;
    dsog_pll.Vbeta_n = 0;
    dsog_pll.theta_dsog = 0;
    dsog_pll.theta_aux = 0;
    dsog_pll.norma_vp = 0;
    dsog_pll.norma_vn = 0;
    dsog_pll.f_pll = 0;
    dsog_pll.norma_w = 0;
	dsog_pll.k_dsog = -10;
    dsog_pll.uk_pb1[0] = 0;
    dsog_pll.uk_pb1[1] = 0;
    dsog_pll.uk_pb1[2] = 0;
    dsog_pll.yk_pb1[0] = 0;
    dsog_pll.yk_pb1[1] = 0;
    dsog_pll.yk_pb1[2] = 0;
    dsog_pll.uk_pb2[0] = 0;
    dsog_pll.uk_pb2[1] = 0;
    dsog_pll.uk_pb2[2] = 0;
    dsog_pll.yk_pb2[0] = 0;
    dsog_pll.yk_pb2[1] = 0;
    dsog_pll.yk_pb2[2] = 0;
    dsog_pll.count = 0;
    dsog_pll.count_theta2 = 0;
    dsog_pll.count_pll = 0;
    dsog_pll.pll_sinc_ok = 0;

}


void DSOG_PLL(struct DSOG_PLL_INPUTS *i, struct DSOGPLL_OUTPUTS *o)
{

    dsog_pll.Va = i->va;
    dsog_pll.Vb = i->vb;
    dsog_pll.Vc = i->vc;

    //Transformada alpha-beta

    dsog_pll.Valpha = (dsog_pll.Va - (0.5*dsog_pll.Vb) -  (0.5*dsog_pll.Vc))*0.81649658092772603273242802490196;                                                    // Calculo da Tensao alfa
    dsog_pll.Vbeta = (0.86602540378443864676372317075294*dsog_pll.Vb-0.86602540378443864676372317075294*dsog_pll.Vc)*0.81649658092772603273242802490196;            // Calculo da tensao beta


    //----------------------------------
    //Calculo dos erros

    dsog_pll.erro_alpha = 1.4142*(dsog_pll.Valpha - dsog_pll.Valpha_out);
    dsog_pll.erro_beta = 1.4142*(dsog_pll.Vbeta - dsog_pll.Vbeta_out);

    dsog_pll.erro_alpha_1 = (dsog_pll.erro_alpha - dsog_pll.Valpha_out_90)*dsog_pll.w_pll;
    dsog_pll.erro_beta_1 = (dsog_pll.erro_beta - dsog_pll.Vbeta_out_90)*dsog_pll.w_pll;

    //----------------------------------



    //Integrador 1

    dsog_pll.uk_int1[0] = dsog_pll.erro_alpha_1;

    dsog_pll.yk_int1[0] = dsog_pll.uk_int1[0]*dsog_pll.Ts + dsog_pll.yk_int1[1];

    dsog_pll.yk_int1[1] = dsog_pll.yk_int1[0];

    dsog_pll.Valpha_out = dsog_pll.yk_int1[0];

    //----------------------------------




    //Integrador 2

    dsog_pll.uk_int2[0] = dsog_pll.Valpha_out;

    dsog_pll.yk_int2[0] = dsog_pll.uk_int2[0]*dsog_pll.Ts + dsog_pll.yk_int2[1];

    dsog_pll.yk_int2[1] = dsog_pll.yk_int2[0];

    dsog_pll.Valpha_out_90 = dsog_pll.yk_int2[0]*dsog_pll.w_pll;

    //----------------------------------


    //Integrador 3

    dsog_pll.uk_int3[0] = dsog_pll.erro_beta_1;

    dsog_pll.yk_int3[0] = dsog_pll.uk_int3[0]*dsog_pll.Ts + dsog_pll.yk_int3[1];

    dsog_pll.yk_int3[1] = dsog_pll.yk_int3[0];

    dsog_pll.Vbeta_out = dsog_pll.yk_int3[0];

    //----------------------------------

    //Integrador 4

    dsog_pll.uk_int4[0] = dsog_pll.Vbeta_out;

    dsog_pll.yk_int4[0] = dsog_pll.uk_int4[0]*dsog_pll.Ts + dsog_pll.yk_int4[1];

    dsog_pll.yk_int4[1] = dsog_pll.yk_int4[0];

    dsog_pll.Vbeta_out_90 = dsog_pll.yk_int4[0]*dsog_pll.w_pll;


    //----------------------------------

    //Calculo dos componentes de sequencia

    dsog_pll.Valpha_p = 0.5*(dsog_pll.Valpha_out - dsog_pll.Vbeta_out_90);
    dsog_pll.Vbeta_p = 0.5*(dsog_pll.Valpha_out_90 + dsog_pll.Vbeta_out);

    dsog_pll.Valpha_n = 0.5*(dsog_pll.Valpha_out + dsog_pll.Vbeta_out_90);
    dsog_pll.Vbeta_n = 0.5*(dsog_pll.Vbeta_out - dsog_pll.Valpha_out_90);

    //----------------------------------



    //Frequency locked loop


    if (dsog_pll.count_theta2 ==1)
    {
        if (dsog_pll.Valpha_p == 0) dsog_pll.Valpha_p = 0.01;
        if (dsog_pll.Vbeta_p == 0) dsog_pll.Vbeta_p = 0.01;
        dsog_pll.count_theta2=2;
    }

    dsog_pll.norma_w = dsog_pll.w_pll*1.4142/(dsog_pll.Valpha_p*dsog_pll.Valpha_p + dsog_pll.Vbeta_p*dsog_pll.Vbeta_p);

    if (dsog_pll.norma_w >= 1) dsog_pll.norma_w = 1;
    if (dsog_pll.norma_w <= -1) dsog_pll.norma_w = -1;

    dsog_pll.erro_fll = (dsog_pll.erro_alpha*dsog_pll.Valpha_out_90 + dsog_pll.erro_beta*dsog_pll.Vbeta_out_90)*0.5*(dsog_pll.k_dsog)*dsog_pll.norma_w;



    //------------------------------------


    //Integrador 5

    dsog_pll.uk_int5[0] = dsog_pll.erro_fll;

    dsog_pll.yk_int5[0] = dsog_pll.uk_int5[0]*dsog_pll.Ts + dsog_pll.yk_int5[1];

    dsog_pll.yk_int5[1] = dsog_pll.yk_int5[0];

    dsog_pll.yk_int5[0] = dsog_pll.yk_int5[0] + 2*3.14159*60;

    dsog_pll.w_pll = dsog_pll.yk_int5[0];

    //----------------------------------

    //Tempo de sincronizacao

    dsog_pll.f_pll = dsog_pll.w_pll*0.15920068519974909972012519541884;

    if (dsog_pll.f_pll >= 58 && dsog_pll.f_pll <= 63)
    {
        dsog_pll.count_pll++;

        if (dsog_pll.count_pll >= ms_100)
           {
               dsog_pll.pll_sinc_ok = TRUE;
               dsog_pll.count_pll = 0;

           }
    }

    else if (dsog_pll.f_pll <= 58 && dsog_pll.f_pll >= 63)
	{
    	dsog_pll.pll_sinc_ok = FALSE;
	}

    //----------------------------------


    if (dsog_pll.count_theta ==1)
    {
        if (dsog_pll.Valpha_p == 0) dsog_pll.Valpha_p = 0.001;
        if (dsog_pll.Vbeta_p == 0) dsog_pll.Vbeta_p = 0.001;
        dsog_pll.count_theta=2;
    }

    dsog_pll.theta_dsog = atan2(dsog_pll.Vbeta_p,dsog_pll.Valpha_p);

    dsog_pll.theta_dsog = dsog_pll.theta_dsog+PI_RAD/2;

    if (dsog_pll.theta_dsog >= (TWO_PI))
    {
        dsog_pll.theta_dsog = dsog_pll.theta_dsog - TWO_PI;
    }

    if (dsog_pll.theta_dsog <= 0)
    {
        dsog_pll.theta_dsog = dsog_pll.theta_dsog + TWO_PI;
    }

    //----------------------------------

    dsog_pll.norma_vp = sqrt(dsog_pll.Valpha_p*dsog_pll.Valpha_p + dsog_pll.Vbeta_p*dsog_pll.Vbeta_p);
    dsog_pll.norma_vn = sqrt(dsog_pll.Valpha_n*dsog_pll.Valpha_n + dsog_pll.Vbeta_n*dsog_pll.Vbeta_n);


    //Filtro passa baixa nas normas

    dsog_pll.uk_pb1[0] = dsog_pll.norma_vp;

    dsog_pll.yk_pb1[0] = dsog_pll.b1_pb*dsog_pll.uk_pb1[0] + dsog_pll.b2_pb*dsog_pll.uk_pb1[1] - dsog_pll.a2_pb*dsog_pll.yk_pb1[1];

    dsog_pll.uk_pb1[2] = dsog_pll.uk_pb1[1];
    dsog_pll.uk_pb1[1] = dsog_pll.uk_pb1[0];
    dsog_pll.yk_pb1[2] = dsog_pll.yk_pb1[1];
    dsog_pll.yk_pb1[1] = dsog_pll.yk_pb1[0];

    dsog_pll.norma_vp = dsog_pll.yk_pb1[0];



    dsog_pll.uk_pb2[0] = dsog_pll.norma_vn;

    dsog_pll.yk_pb2[0] = dsog_pll.b1_pb*dsog_pll.uk_pb2[0] + dsog_pll.b2_pb*dsog_pll.uk_pb2[1] - dsog_pll.a2_pb*dsog_pll.yk_pb2[1];

    dsog_pll.uk_pb2[2] = dsog_pll.uk_pb2[1];
    dsog_pll.uk_pb2[1] = dsog_pll.uk_pb2[0];
    dsog_pll.yk_pb2[2] = dsog_pll.yk_pb2[1];
    dsog_pll.yk_pb2[1] = dsog_pll.yk_pb2[0];

    dsog_pll.norma_vn = dsog_pll.yk_pb2[0];


    o->valpha = dsog_pll.Valpha;
    o->vbeta = dsog_pll.Vbeta;
    o->valpha_p = dsog_pll.Valpha_p;
    o->valpha_n = dsog_pll.Valpha_n;
    o->vbeta_p = dsog_pll.Vbeta_p;
    o->vbeta_n = dsog_pll.Vbeta_n;
    o->norma_vp = dsog_pll.norma_vp;
    o->norma_vn = dsog_pll.norma_vn;
    o->theta = dsog_pll.theta_dsog;
    o->w = dsog_pll.w_pll;
    o->f = dsog_pll.f_pll;
    o->pll_sinc_ok = dsog_pll.pll_sinc_ok;

}





/*******************************************************************************/
/*		Instantaneous_Power_Calculation				   	   	  	  			   */
/*******************************************************************************/


void Instantaneous_Power_Calculation_Init(void)
{
    ipc.yk_pb1[0] = 0;
    ipc.yk_pb1[1] = 0;
    ipc.yk_pb1[2] = 0;
    ipc.uk_pb1[0] = 0;
    ipc.uk_pb1[1] = 0;
    ipc.uk_pb1[2] = 0;

    ipc.yk_pb2[0] = 0;
    ipc.yk_pb2[1] = 0;
    ipc.yk_pb2[2] = 0;
    ipc.uk_pb2[0] = 0;
    ipc.uk_pb2[1] = 0;
    ipc.uk_pb2[2] = 0;

    //Inicializar com os parâmetros do filtro discretizado
    ipc.b0_pb = b0_pb_30Hz;
    ipc.b1_pb = b1_pb_30Hz;
    ipc.b2_pb = b2_pb_30Hz;
    ipc.a1_pb = a1_pb_30Hz;
    ipc.a2_pb = a2_pb_30Hz;

}



void Instantaneous_Power_Calculation(float valpha, float vbeta, float ialpha, float ibeta)
{

    //Passagem dos parâmetros
    ipc.Valpha = valpha;
    ipc.Vbeta = vbeta;
    ipc.i_alpha = ialpha;
    ipc.i_beta = ibeta;


    ipc.P_inst = ipc.Valpha*ipc.i_alpha + ipc.Vbeta*ipc.i_beta;

    ipc.uk_pb1[0] = ipc.P_inst;


    ipc.yk_pb1[0] = ipc.b1_pb*ipc.uk_pb1[0] + ipc.b2_pb*ipc.uk_pb1[1] - ipc.a2_pb*ipc.yk_pb1[1];

    ipc.uk_pb1[2] = ipc.uk_pb1[1];
    ipc.uk_pb1[1] = ipc.uk_pb1[0];
    ipc.yk_pb1[2] = ipc.yk_pb1[1];
    ipc.yk_pb1[1] = ipc.yk_pb1[0];

    ipc.P_inst = ipc.yk_pb1[0];

    //---------------------

    ipc.Q_inst = - (ipc.Vbeta*ipc.i_alpha - ipc.Valpha*ipc.i_beta);

    ipc.uk_pb2[0] = ipc.Q_inst;

    ipc.yk_pb2[0] = ipc.b1_pb*ipc.uk_pb2[0] + ipc.b2_pb*ipc.uk_pb2[1] - ipc.a2_pb*ipc.yk_pb2[1];

    ipc.uk_pb2[2] = ipc.uk_pb2[1];
    ipc.uk_pb2[1] = ipc.uk_pb2[0];
    ipc.yk_pb2[2] = ipc.yk_pb2[1];
    ipc.yk_pb2[1] = ipc.yk_pb2[0];

    ipc.Q_inst = ipc.yk_pb2[0];

}


/*******************************************************************************/
/*		Space_Vector_Modulation_Init				   	   	  	  			   */
/*******************************************************************************/



void Space_Vector_Modulation_Init(void)
{
    svm.va_ref = 0;
    svm.vb_ref = 0;
    svm.vc_ref = 0;
    svm.max = 0;
    svm.min = 0;
    svm.temp0 = 0;
    svm.vo_ref = 0;
}




void Space_Vector_Modulation(float ma, float mb, float mc)
{

    svm.va_ref = ma;
    svm.vb_ref = mb;
    svm.vc_ref = mc;


    // Calcula max(va, vb, vc)
    if ( svm.va_ref > svm.vb_ref) svm.temp0 = svm.va_ref;
    else svm.temp0 = svm.vb_ref;

    if (svm.temp0 > svm.vc_ref) svm.max = svm.temp0;
    else svm.max = svm.vc_ref;

    svm.temp0 = 0;

    // Calcula min(va, vb, vc)
    if ( svm.va_ref < svm.vb_ref) svm.temp0 = svm.va_ref;
    else svm.temp0 = svm.vb_ref;

    if (svm.temp0 < svm.vc_ref) svm.min = svm.temp0;
    else svm.min = svm.vc_ref;

    svm.temp0 = 0;

    //  Calculo da componente de modo comum para SPWM
    svm.vo_ref = -(svm.max+svm.min)/2;

    //  Calcula as novas razoes ciclicas
    svm.va_ref = svm.va_ref + svm.vo_ref;
    svm.vb_ref = svm.vb_ref + svm.vo_ref;
    svm.vc_ref = svm.vc_ref + svm.vo_ref;
}


/*******************************************************************************/
/*		Reactive_Power_Compensation_Init				   	   	  	  		   */
/*******************************************************************************/



void Reactive_Power_Compensation_Init(void)
{

    rpc.temp2 = 0;
    rpc.temp3 = 0;
    rpc.temp4 = 0;
    rpc.Qnominal = 2500;       			//Potência reativa nominal
    rpc.Qoffset = rpc.Qnominal*0.2; 	//Offset da curva de compensação de reativos
    rpc.Qmax = rpc.Qnominal*1.5;    	//Potência reativa máxiam
    rpc.norma_vp = 0;           		//Norma de sequência positiva
    rpc.norma_nominal = 0;      		//Norma nominal
    rpc.Q_ref = 0;              		//Referência de potência reativa
}



void Reactive_Power_Compensation(float norma_p, float norma_nominal, int enable)
{

    rpc.norma_vp = norma_p;
    rpc.norma_nominal = norma_nominal;
    rpc.output_enable = enable;

    rpc.temp2 = 1 - (rpc.norma_vp/rpc.norma_nominal);

    if (rpc.temp2 >= 2) rpc.temp2 = 2;
    if (rpc.temp2 <= -2) rpc.temp2 = -2;

    rpc.temp3 = -2*rpc.temp2*rpc.Qnominal + rpc.Qoffset;

    rpc.temp3 = rpc.temp3*rpc.output_enable;

    if (rpc.temp3 >= rpc.Qmax) rpc.temp3 = rpc.Qmax;
    if (rpc.temp3 <= -rpc.Qmax) rpc.temp3 = -rpc.Qmax;

    rpc.Q_ref = rpc.temp3;

}

/*******************************************************************************/
/*		Current_Control_Loop_Init						   	   	  	  		   */
/*******************************************************************************/


void Current_Control_Loop_Init(void)
{

    ccl.erro_i_alpha = 0;
    ccl.erro_i_beta = 0;
    ccl.pr_alpha_p = 0;
    ccl.pr_beta_p = 0;
    ccl.v_alpha_ref = 0;
    ccl.v_beta_ref = 0;
    ccl.uk_pr_alpha[0] = 0;
    ccl.yk_pr_alpha[0] = 0;
    ccl.uk_pr_beta[0] = 0;
    ccl.yk_pr_beta[0] = 0;
    ccl.uk_pr5_alpha[0] = 0;
    ccl.yk_pr5_alpha[0] = 0;
    ccl.uk_pr5_beta[0] = 0;
    ccl.yk_pr5_beta[0] = 0;
    ccl.uk_pr7_alpha[0] = 0;
    ccl.yk_pr7_alpha[0] = 0;
    ccl.uk_pr7_beta[0] = 0;
    ccl.yk_pr7_beta[0] = 0;
    ccl.i_alpha_max = CORRENTE_MAXIMA;
    ccl.i_beta_max = CORRENTE_MAXIMA;
    ccl.yk_pb1[0] = 0;
    ccl.uk_pb1[0] = 0;
    ccl.yk_pb2[0] = 0;
    ccl.uk_pb2[0] = 0;
    ccl.yk_pb3[0] = 0;
    ccl.uk_pb3[0] = 0;
    ccl.yk_pb4[0] = 0;
    ccl.uk_pb4[0] = 0;
    ccl.b0_pr_i = b0_pr;
    ccl.b1_pr_i = b1_pr;
    ccl.b2_pr_i = b2_pr;
    ccl.a1_pr_i = a1_pr;
    ccl.a2_pr_i = a2_pr;
    ccl.b0_pr5_i = b0_pr5;
    ccl.b1_pr5_i = b1_pr5;
    ccl.b2_pr5_i = b2_pr5;
    ccl.a1_pr5_i = a1_pr5;
    ccl.a2_pr5_i = a2_pr5;
    ccl.b0_pr7_i = b0_pr7;
    ccl.b1_pr7_i = b1_pr7;
    ccl.b2_pr7_i = b2_pr7;
    ccl.a1_pr7_i = a1_pr7;
    ccl.a2_pr7_i = a2_pr7;
    ccl.Kp_pr_i = Kp_pr;


}





void Current_Control_Loop(float ia, float ib, float ic, float vdc, float Valpha_p, float Vbeta_p, float i_alpha_ref, float i_beta_ref)
{

    //Passagem dos parâmetros
    ccl.ia = ia;
    ccl.ib = ib;
    ccl.ic = ic;
    ccl.vdc = vdc;
    ccl.Valpha_p = Valpha_p;
    ccl.Vbeta_p = Vbeta_p;
    ccl.i_alpha_ref = i_alpha_ref;
    ccl.i_beta_ref = i_beta_ref;


    // Transformada alpha-beta de corrente
    ccl.i_alpha = (ccl.ia - (0.5*ccl.ib) -  (0.5*ccl.ic))*0.81649658092772603273242802490196;                                                       // Calculo da corrente alfa
    ccl.i_beta = (0.86602540378443864676372317075294*ccl.ib-0.86602540378443864676372317075294*ccl.ic)*0.81649658092772603273242802490196;          // Calculo da corrente beta

    //Calculo do erro da malha de corrente
    ccl.erro_i_alpha = ccl.i_alpha_ref - ccl.i_alpha;
    ccl.erro_i_beta = ccl.i_beta_ref - ccl.i_beta;


    //------------------------------------------

    //Parcela proporcional do PR
    ccl.pr_alpha_p = ccl.erro_i_alpha*ccl.Kp_pr_i;
    ccl.pr_beta_p = ccl.erro_i_beta*ccl.Kp_pr_i;

    //------------------------------------------

    //Parcela ressonante do PR 60 Hz

    //PR alpha
    ccl.uk_pr_alpha[0] = ccl.erro_i_alpha;

    ccl.yk_pr_alpha[0] = ccl.b0_pr_i*ccl.uk_pr_alpha[0] + ccl.b1_pr_i*ccl.uk_pr_alpha[1] + ccl.b2_pr_i*ccl.uk_pr_alpha[2] - ccl.a1_pr_i*ccl.yk_pr_alpha[1] - ccl.a2_pr_i*ccl.yk_pr_alpha[2];

    ccl.uk_pr_alpha[2] = ccl.uk_pr_alpha[1];
    ccl.uk_pr_alpha[1] = ccl.uk_pr_alpha[0];
    ccl.yk_pr_alpha[2] = ccl.yk_pr_alpha[1];
    ccl.yk_pr_alpha[1] = ccl.yk_pr_alpha[0];

    // PR beta

    ccl.uk_pr_beta[0] = ccl.erro_i_beta;

    ccl.yk_pr_beta[0] = ccl.b0_pr_i*ccl.uk_pr_beta[0] + ccl.b1_pr_i*ccl.uk_pr_beta[1] + ccl.b2_pr_i*ccl.uk_pr_beta[2] - ccl.a1_pr_i*ccl.yk_pr_beta[1] - ccl.a2_pr_i*ccl.yk_pr_beta[2];

    ccl.uk_pr_beta[2] = ccl.uk_pr_beta[1];
    ccl.uk_pr_beta[1] = ccl.uk_pr_beta[0];
    ccl.yk_pr_beta[2] = ccl.yk_pr_beta[1];
    ccl.yk_pr_beta[1] = ccl.yk_pr_beta[0];


    //------------------------------------------

    //PR alpha 60*5 Hz
    ccl.uk_pr5_alpha[0] = ccl.erro_i_alpha;

    ccl.yk_pr5_alpha[0] = ccl.b0_pr5_i*ccl.uk_pr5_alpha[0] + ccl.b1_pr5_i*ccl.uk_pr5_alpha[1] + ccl.b2_pr5_i*ccl.uk_pr5_alpha[2] - ccl.a1_pr5_i*ccl.yk_pr5_alpha[1] - ccl.a2_pr5_i*ccl.yk_pr5_alpha[2];

    ccl.uk_pr5_alpha[2] = ccl.uk_pr5_alpha[1];
    ccl.uk_pr5_alpha[1] = ccl.uk_pr5_alpha[0];
    ccl.yk_pr5_alpha[2] = ccl.yk_pr5_alpha[1];
    ccl.yk_pr5_alpha[1] = ccl.yk_pr5_alpha[0];

    // PR beta 60*5 Hz

    ccl.uk_pr5_beta[0] = ccl.erro_i_beta;

    ccl.yk_pr5_beta[0] = ccl.b0_pr5_i*ccl.uk_pr5_beta[0] + ccl.b1_pr5_i*ccl.uk_pr5_beta[1] + ccl.b2_pr5_i*ccl.uk_pr5_beta[2] - ccl.a1_pr5_i*ccl.yk_pr5_beta[1] - ccl.a2_pr5_i*ccl.yk_pr5_beta[2];

    ccl.uk_pr5_beta[2] = ccl.uk_pr5_beta[1];
    ccl.uk_pr5_beta[1] = ccl.uk_pr5_beta[0];
    ccl.yk_pr5_beta[2] = ccl.yk_pr5_beta[1];
    ccl.yk_pr5_beta[1] = ccl.yk_pr5_beta[0];

    //------------------------------------------

    //PR alpha 60*7 Hz
    ccl.uk_pr7_alpha[0] = ccl.erro_i_alpha;

    ccl.yk_pr7_alpha[0] = ccl.b0_pr7_i*ccl.uk_pr7_alpha[0] + ccl.b1_pr7_i*ccl.uk_pr7_alpha[1] + ccl.b2_pr7_i*ccl.uk_pr7_alpha[2] - ccl.a1_pr7_i*ccl.yk_pr7_alpha[1] - ccl.a2_pr7_i*ccl.yk_pr7_alpha[2];

    ccl.uk_pr7_alpha[2] = ccl.uk_pr7_alpha[1];
    ccl.uk_pr7_alpha[1] = ccl.uk_pr7_alpha[0];
    ccl.yk_pr7_alpha[2] = ccl.yk_pr7_alpha[1];
    ccl.yk_pr7_alpha[1] = ccl.yk_pr7_alpha[0];

    // PR beta 60*7 Hz

    ccl.uk_pr7_beta[0] = ccl.erro_i_beta;

    ccl.yk_pr7_beta[0] = ccl.b0_pr7_i*ccl.uk_pr7_beta[0] + ccl.b1_pr7_i*ccl.uk_pr7_beta[1] + ccl.b2_pr7_i*ccl.uk_pr7_beta[2] - ccl.a1_pr7_i*ccl.yk_pr7_beta[1] - ccl.a2_pr7_i*ccl.yk_pr7_beta[2];

    ccl.uk_pr7_beta[2] = ccl.uk_pr7_beta[1];
    ccl.uk_pr7_beta[1] = ccl.uk_pr7_beta[0];
    ccl.yk_pr7_beta[2] = ccl.yk_pr7_beta[1];
    ccl.yk_pr7_beta[1] = ccl.yk_pr7_beta[0];


    //------------------------------------------

    ccl.v_alpha_ref = ccl.pr_alpha_p + ccl.yk_pr_alpha[0] + ccl.yk_pr5_alpha[0] + ccl.yk_pr7_alpha[0];
    ccl.v_beta_ref =  ccl.pr_beta_p + ccl.yk_pr_beta[0] + ccl.yk_pr5_beta[0] + ccl.yk_pr7_beta[0];

/*

    ccl.v_alpha_ref = ccl.pr_alpha_p + ccl.yk_pr_alpha[0];
    ccl.v_beta_ref =  ccl.pr_beta_p + ccl.yk_pr_beta[0];
*/
    //------------------------------------------

    //Feedforward
    ccl.v_alpha_ref = ccl.v_alpha_ref +  ccl.Valpha_p/ccl.vdc;
    ccl.v_beta_ref = ccl.v_beta_ref +  ccl.Vbeta_p/ccl.vdc;

    //------------------------------------------

    //Transformada alpha-beta - abc
    ccl.va_ref = 0.81649658092772603273242802490196*(ccl.v_alpha_ref);
    ccl.vb_ref = 0.81649658092772603273242802490196*(-0.5*ccl.v_alpha_ref +  0.86602540378443864676372317075294*ccl.v_beta_ref);
    ccl.vc_ref = 0.81649658092772603273242802490196*(-0.5*ccl.v_alpha_ref -  0.86602540378443864676372317075294*ccl.v_beta_ref);


    //------------------------------------------

    // Limitadores de razão cíclica

    if (ccl.va_ref > 1) ccl.va_ref = 1;
    if (ccl.va_ref < -1) ccl.va_ref = -1;
    if (ccl.vb_ref > 1) ccl.vb_ref = 1;
    if (ccl.vb_ref < -1) ccl.vb_ref = -1;
    if (ccl.vc_ref > 1) ccl.vc_ref = 1;
    if (ccl.vc_ref < -1) ccl.vc_ref = -1;

}

/*******************************************************************************/
/*		Voltage_Control_Loop_Init						   	   	  	  		   */
/*******************************************************************************/


#define PRECHARGE_CONTROL 0
#define VOLTAGE_CONTROL 1
#define OVERVOLTAGE_CONTROL 2


void Voltage_Control_Loop_Init(void)
{
    vcl.P_ref=0;
    vcl.vdc = 0;
    vcl.vdc_ref  = 0;
	vcl.vdc_ref2 = 0;
    vcl.erro_v  = 0;
    vcl.uk_v[0]  = 0;
    vcl.yk_v[0]  = 0;
    vcl.yk_v_aw[0]  = 0;
    vcl.temp1  = 0;
    vcl.dc_link_ok = 0;

    vcl.d_limite  = 100;
    vcl.idc_max  = 100;
    vcl.idc_nominal  = 25;
    vcl.P_nominal = 10000;
	vcl.P_ref_max  = vcl.P_nominal*1.2;
	vcl.norma_nominal  = 220;
	vcl.norma_vp = 0;

    vcl.kp_v  = kp_v_aw ;
    vcl.b0_v  = b0_v_aw;
    vcl.b1_v  = b1_v_aw;
    vcl.a1_v  = a1_v_aw;

    vcl.temp_aw = 0;
    vcl.erro_v2 = 0;
    vcl.temp_aw = 0;

    vcl.kp_v2 = kp_v_aw2;
    vcl.b0_v2 = b0_v_aw2;
    vcl.b1_v2 = b1_v_aw2;
    vcl.a1_v2 = a1_v_aw2;
    vcl.temp2 = 0;
    vcl.d_limite2 = vcl.idc_nominal*1.2;

    vcl.VDC_ANTI_WINDUP = 1;
	vcl.control_mode = VOLTAGE_CONTROL;

	vcl.uk_pb[0] = 0;
	vcl.uk_pb[1] = 0;
	vcl.uk_pb[2] = 0;
	vcl.yk_pb[0] = 0;
	vcl.yk_pb[1] = 0;
	vcl.yk_pb[2] = 0;

	vcl.b0_pb = b0_pb_360Hz;
    vcl.b1_pb = b1_pb_360Hz;
    vcl.b2_pb = b2_pb_360Hz;
    vcl.a1_pb = a1_pb_360Hz;
    vcl.a2_pb = a1_pb_360Hz;

	vcl.uk_pb2[0] = 0;
	vcl.uk_pb2[1] = 0;
	vcl.uk_pb2[2] = 0;
	vcl.yk_pb2[0] = 0;
	vcl.yk_pb2[1] = 0;
	vcl.yk_pb2[2] = 0;



}


#define OVC_HYSTERESIS 	1
#define OVC_CHOPPER 	2
#define OVC_MODE		OVC_HYSTERESIS
#define PRECHARGE_CONTROL 0
#define VOLTAGE_CONTROL 1
#define OVERVOLTAGE_CONTROL 2


//HMC_PENDING: Adicionar filtro passa faixa 120 Hz subtraindo a ondulação da referência de potência

void Voltage_Control_Loop(float vdc, float vdc_ref, float vdc_ref2, float norma_vp, float norma_nominal)
{


    //Passagem dos parâmetros
    vcl.vdc = vdc;
    vcl.vdc_ref = vdc_ref;
    vcl.vdc_ref2 = vdc_ref2;
    vcl.norma_vp = norma_vp;
    vcl.norma_nominal = norma_nominal;

	//Limita a corrente máxima que pode ser extraída do barramento CC	

	
		//Só vale para depois da pre-carga e inicializacao da norma
			
	if (vcl.norma_vp < 0.9*vcl.norma_nominal || vcl.norma_vp > 1.2*vcl.norma_nominal)
	{
		if (vcl.dc_link_ok == TRUE)
		{	
			vcl.control_mode = OVERVOLTAGE_CONTROL;

			
			if (vcl.norma_vp < 0.9*vcl.norma_nominal)
			{
				vcl.P_ref_max = (vcl.P_nominal*vcl.norma_vp/vcl.norma_nominal)*1.2;
					
			}

			else if (vcl.norma_vp >1.1*vcl.norma_nominal)
			{
				vcl.P_ref_max = (vcl.P_nominal*vcl.norma_nominal/vcl.norma_vp)*1.2;
			}
		
		}	
	}
	
	else 
	{	
		vcl.control_mode = VOLTAGE_CONTROL;
		vcl.P_ref_max = vcl.P_nominal*1.2;
	}

	//---------------------------------------------------------------------------------

	//Define a faixa de operação do controle de tensão
	if (vcl.control_mode == VOLTAGE_CONTROL || vcl.control_mode == OVERVOLTAGE_CONTROL)	
	{
	
	    // PI da malha de tensao
		vcl.erro_v = vcl.vdc_ref - vcl.vdc;

		vcl.uk_v[0] = vcl.erro_v;

		//---------
		if (vcl.VDC_ANTI_WINDUP == TRUE)
		{
			vcl.temp1 = (vcl.kp_v*vcl.uk_v[0]);     // Parcela proporcional do PI

			vcl.yk_v_aw[0] = (vcl.b0_v*vcl.uk_v[0]) + (vcl.b1_v*vcl.uk_v[1]) - (vcl.a1_v*vcl.yk_v_aw[1]);  // Parcela integral do PI

			vcl.yk_v_aw[0] = vcl.yk_v_aw[0];

			// Calculo do limitador dinamico

			if (vcl.temp1 < 0) vcl.d_limite = vcl.idc_max + vcl.temp1;

			else vcl.d_limite = vcl.idc_max - vcl.temp1;

			if (vcl.d_limite < 0) vcl.d_limite = 0;

			// Saturacao da parcela integral

			if (vcl.yk_v_aw[0] > vcl.d_limite) vcl.yk_v_aw[0] = vcl.d_limite;
			if (vcl.yk_v_aw[0] < - vcl.d_limite) vcl.yk_v_aw[0] = -vcl.d_limite;

			// Atualizacao do PI

			vcl.uk_v[2] = vcl.uk_v[1];
			vcl.uk_v[1] = vcl.uk_v[0];
			vcl.yk_v_aw[2] = vcl.yk_v_aw[1];
			vcl.yk_v_aw[1] = vcl.yk_v_aw[0];

			vcl.yk_v[0] = vcl.yk_v_aw[0] + vcl.temp1 +  vcl.idc_nominal; //Feedforward
			
	

		}

		else if (vcl.VDC_ANTI_WINDUP == FALSE)
		{

			vcl.yk_v_aw[0] = (vcl.b0_v*vcl.uk_v[0]) + (vcl.b1_v*vcl.uk_v[1])  - (vcl.a1_v*vcl.yk_v_aw[1]);  // Parcela integral do PI

			// Atualizacao do integrador
			vcl.uk_v[2] = vcl.uk_v[1];
			vcl.uk_v[1] = vcl.uk_v[0];
			vcl.yk_v_aw[2] = vcl.yk_v_aw[1];
			vcl.yk_v_aw[1] = vcl.yk_v_aw[0];

			if (vcl.yk_v_aw[0] > vcl.d_limite)   vcl.yk_v_aw[0] = vcl.d_limite;
			if (vcl.yk_v_aw[0] < -vcl.d_limite)  vcl.yk_v_aw[0] = -vcl.d_limite;

			vcl.yk_v[0] = vcl.yk_v_aw[0] + vcl.kp_v*vcl.uk_v[0] +  vcl.idc_nominal; //Feedforward

		}

		//-----------

		// Saturacao da saida

		if (vcl.yk_v[0] >= vcl.idc_max) vcl.yk_v[0] = vcl.idc_max;          //  Idcmax =  Idcnominal * 1.5
		if (vcl.yk_v[0] <= -vcl.idc_max) vcl.yk_v[0] = -vcl.idc_max;      // -Idcmax = -Idcnominal * 1.5

	
					
		vcl.P_ref = (vcl.P_nominal - (vcl.yk_v[0]*vcl.norma_vp));	


		
		/*Filtro passa alta para tirar oscilações de potência de alta frequência 
		OBS: As harmônicas de baixa frequência da tensão da rede se refletem na
		referência de potência ativa gerada pela malha de tensão do barramento cc*/

#if 0
		vcl.uk_pb[0] = vcl.P_ref;

		vcl.yk_pb[0] = (b0_pb_360Hz*vcl.uk_pb[0]) + (b1_pb_360Hz*vcl.uk_pb[1]) + (b2_pb_360Hz*vcl.uk_pb[2]) - (a1_pb_360Hz*vcl.yk_pb[1]) - (a2_pb_360Hz*vcl.yk_pb[2]);
		vcl.uk_pb[2] = vcl.uk_pb[1];
		vcl.uk_pb[1] = vcl.uk_pb[0];
		vcl.yk_pb[2] = vcl.yk_pb[1];
		vcl.yk_pb[1] = vcl.yk_pb[0];

	//	vcl.P_ref = vcl.P_ref - vcl.yk_pb[0];

	
		vcl.uk_pb2[0] = vcl.P_ref;
		
		vcl.yk_pb2[0] = (b0_pb_420Hz*vcl.uk_pb2[0]) + (b1_pb_420Hz*vcl.uk_pb2[1]) + (b2_pb_420Hz*vcl.uk_pb2[2]) - (a1_pb_420Hz*vcl.yk_pb2[1]) - (a2_pb_420Hz*vcl.yk_pb2[2]);
		vcl.uk_pb2[2] = vcl.uk_pb2[1];
		vcl.uk_pb2[1] = vcl.uk_pb2[0];
		vcl.yk_pb2[2] = vcl.yk_pb2[1];
		vcl.yk_pb2[1] = vcl.yk_pb2[0];


		vcl.P_ref = vcl.P_ref - vcl.yk_pb[0] - vcl.yk_pb2[0];
#endif			
	


	}




    //Malha de tensão durante sobretensão

	if (vcl.control_mode == OVERVOLTAGE_CONTROL)
	{

#if 1		
		
//		if (vcl.vdc < 380) vcl.P_ref = -500;
		
	
		// PI da malha de tensao de proteção de sobretensão

			vcl.erro_v2 = vcl.vdc_ref2 - vcl.vdc;

			vcl.uk_v2[0] = vcl.erro_v2;

			//---------

			vcl.temp_aw = (vcl.kp_v2*vcl.uk_v2[0]);     // Parcela proporcional do PI

			vcl.yk_v_aw2[0] = (vcl.b0_v2*vcl.uk_v2[0]) + (vcl.b1_v2*vcl.uk_v2[1]) - (vcl.a1_v2*vcl.yk_v_aw2[1]);  // Parcela integral do PI

			vcl.yk_v_aw2[0] = vcl.yk_v_aw2[0];

			// Calculo do limitador dinamico

			if (vcl.temp2 < 0) vcl.d_limite2 = vcl.idc_max + vcl.temp_aw;

			else vcl.d_limite2 = vcl.idc_max - vcl.temp_aw;

			if (vcl.d_limite2 < 0) vcl.d_limite2 = 0;

			// Saturacao da parcela integral

			if (vcl.yk_v_aw2[0] > vcl.d_limite2) vcl.yk_v_aw2[0] = vcl.d_limite2;
			if (vcl.yk_v_aw2[0] < - vcl.d_limite2) vcl.yk_v_aw2[0] = -vcl.d_limite2;

			// Atualizacao do PI

			vcl.uk_v2[2] = vcl.uk_v2[1];
			vcl.uk_v2[1] = vcl.uk_v2[0];
			vcl.yk_v_aw2[2] = vcl.yk_v_aw2[1];
			vcl.yk_v_aw2[1] = vcl.yk_v_aw2[0];

        vcl.yk_v2[0] = 0.05 - (vcl.yk_v_aw2[0] + vcl.temp_aw)/vcl.vdc_ref2;

        // Saturacao da saida
        if (vcl.yk_v2[0] >= 1)  vcl.yk_v2[0] = 1;
        if (vcl.yk_v2[0] < 0)   vcl.yk_v2[0] = 0;
		
		vcl.vdc_ref = vcl.vdc_ref2; 
#endif
		
	
	
	
	}

    //Incluir proteção limite máximo

    else
    {
        vcl.uk_v2[0] = 0;
        vcl.uk_v2[1] = 0;
        vcl.uk_v2[2] = 0;

        vcl.yk_v2[0] = 0;
        vcl.yk_v2[1] = 0;
        vcl.yk_v2[2] = 0;

        vcl.yk_v_aw2[0] = 0;
        vcl.yk_v_aw2[1] = 0;
        vcl.yk_v_aw2[2] = 0;

    }


	//Limitação de potência
	if (vcl.P_ref >= vcl.P_ref_max)	vcl.P_ref = vcl.P_ref_max;
	if (vcl.P_ref <= -vcl.P_ref_max) vcl.P_ref = -vcl.P_ref_max;




}


/*******************************************************************************/
/*		Current_Reference_Calculation_Init						   	   	 	   */
/*******************************************************************************/



void Current_Reference_Calculation_Init(void)
{
    crc.k1 = 0;
    crc.k2 = 0;
    crc.P_ref = 0;
    crc.Q_ref = 0;
    crc.Valpha_p = 0;
    crc.Vbeta_p = 0;
    crc.Valpha_n = 0;
    crc.Vbeta_n = 0;
    crc.norma_vp = 0;
    crc.norma_vn = 0;
    crc.norma_nominal = 0;

    crc.Valpha_p_o = 0;
    crc.Vbeta_p_o = 0;
    crc.Valpha_n_o = 0;
    crc.Vbeta_n_o = 0;
    crc.ip_alpha_p = 0;
    crc.ip_beta_p = 0;
    crc.ip_alpha_n = 0;
    crc.ip_beta_n = 0;
    crc.iq_alpha_p_o = 0;
    crc.iq_beta_p_o = 0;
    crc.iq_alpha_n_o = 0;
    crc.iq_beta_n_o = 0;
    crc.i_alpha_p_ref = 0;
    crc.i_beta_p_ref = 0;
    crc.i_alpha_n_ref = 0;
    crc.i_beta_n_ref = 0;
    crc.i_alpha_ref = 0;
    crc.i_beta_ref = 0;
    crc.i_alpha_max = CORRENTE_MAXIMA;
    crc.i_beta_max = CORRENTE_MAXIMA;
    crc.PNSC = 1;
    crc.BPSC = 0;



}


#define k_max	1				// 10000/((220-0)*220)*3.5

void Current_Reference_Calculation(float P_ref, float Q_ref, float Valpha_p, float Vbeta_p, float Valpha_n, float Vbeta_n, float norma_nominal)
{

    //Passagem dos parâmetros
    crc.P_ref = P_ref;
    crc.Q_ref = Q_ref;
    crc.Valpha_p = Valpha_p;
    crc.Vbeta_p = Vbeta_p;
    crc.Valpha_n = Valpha_n;
    crc.Vbeta_n = Vbeta_n;
    crc.norma_nominal = norma_nominal;




	crc.norma_vp = sqrt(Valpha_p*Valpha_p + Vbeta_p*Vbeta_p+0.00001);
	crc.norma_vn = sqrt(Valpha_n*Valpha_n + Vbeta_n*Vbeta_n+0.00001);

    crc.Valpha_p_o = - crc.Vbeta_p;         // Componente de tensao de sequencia positiva ortogonal de eixo direto
    crc.Vbeta_p_o = crc.Valpha_p;           // Componente de tensao de sequencia positiva ortogonal de eixo quadratura
    crc.Valpha_n_o = - crc.Vbeta_n;         // Componente de tensao de sequencia negativa ortogonal de eixo direto
    crc.Vbeta_n_o = crc.Valpha_n;           // Componente de tensao de sequencia negativa ortogonal de eixo quadratura


    // Calculo das parcelas de referências de corrente PNSC
    if (crc.PNSC == TRUE)
    {

		crc.k1 = crc.P_ref/(crc.norma_vp*crc.norma_vp - crc.norma_vn*crc.norma_vn +0.00001);
		crc.k2 = crc.Q_ref/(crc.norma_vp*crc.norma_vp - crc.norma_vn*crc.norma_vn +0.00001);

		if (crc.k1 >= k_max) crc.k1 = k_max;
		if (crc.k1 <= -k_max) crc.k1 = -k_max;
		if (crc.k2 >= k_max) crc.k2 = k_max;
		if (crc.k2 <= -k_max) crc.k2 = -k_max;
		
		crc.ip_alpha_p = (crc.k1*(crc.Valpha_p));       // Parcela de corrente ativa de eixo direto em sequencia positiva
        crc.ip_beta_p = (crc.k1*(crc.Vbeta_p));         // Parcela de corrente ativa de eixo quadratura em sequencia positiva
        crc.ip_alpha_n = - (crc.k1*(crc.Valpha_n));     // Parcela de corrente ativa de eixo direto em sequencia negativa
        crc.ip_beta_n = - (crc.k1*(crc.Vbeta_n));       // Parcela de corrente ativa de eixo quadratura em sequencia negativa

        crc.iq_alpha_p_o = (crc.k2*(crc.Valpha_p_o));    // Parcela de corrente reativa de eixo direto em sequencia positiva
        crc.iq_beta_p_o = (crc.k2*(crc.Vbeta_p_o));      // Parcela de corrente reativa de eixo quadratura em sequencia positiva
        crc.iq_alpha_n_o = - (crc.k2*(crc.Valpha_n_o));  // Parcela de corrente reativa de eixo direto em sequencia negativa
        crc.iq_beta_n_o = - (crc.k2*(crc.Vbeta_n_o));    // Parcela de corrente reativa de eixo quadratura em sequencia negativa
    }

    // Calculo das parcelas de referencia de corrente BPSC
    if (crc.BPSC == TRUE)
    {

		crc.k1 = crc.P_ref/(crc.norma_vp*crc.norma_vp+0.00001);
		crc.k2 = crc.Q_ref/(crc.norma_vp*crc.norma_vp+0.00001);

		if (crc.k1 >= k_max) crc.k1 = k_max;
		if (crc.k1 <= -k_max) crc.k1 = -k_max;
		if (crc.k2 >= k_max) crc.k2 = k_max;
		if (crc.k2 <= -k_max) crc.k2 = -k_max;


		crc.ip_alpha_p = (crc.k1*(crc.Valpha_p));       // Parcela de corrente ativa de eixo direto em sequencia positiva
        crc.ip_beta_p = (crc.k1*(crc.Vbeta_p));         // Parcela de corrente ativa de eixo quadratura em sequencia positiva
        crc.iq_alpha_p_o = (crc.k2*(crc.Valpha_p_o));   // Parcela de corrente reativa de eixo direto em sequencia positiva
        crc.iq_beta_p_o = (crc.k2*(crc.Vbeta_p_o));     // Parcela de corrente reativa de eixo quadratura em sequencia positiva

        crc.ip_alpha_n = 0;
        crc.ip_beta_n = 0;
        crc.iq_alpha_n_o = 0;
        crc.iq_beta_n_o = 0;
    }



    //------------------------------------------


    //Calculo das Referencias de corrente

    crc.i_alpha_p_ref = (crc.ip_alpha_p + crc.iq_alpha_p_o);    // Referencia de corrente de eixo direto em sequencia positiva
    crc.i_beta_p_ref = (crc.ip_beta_p + crc.iq_beta_p_o);       // Referencia de corrente de eixo quadratura em sequencia positiva
    crc.i_alpha_n_ref = (crc.ip_alpha_n + crc.iq_alpha_n_o);    // Referencia de corrente de eixo direto em sequencia netativa
    crc.i_beta_n_ref = (crc.ip_beta_n + crc.iq_beta_n_o);       // Referencia de corrente de eixo quadratura em sequencia netativa



    crc.i_alpha_ref = crc.i_alpha_p_ref + crc.i_alpha_n_ref;
    crc.i_beta_ref  = crc.i_beta_p_ref + crc.i_beta_n_ref;


    if (crc.i_alpha_ref > crc.i_alpha_max) crc.i_alpha_ref = crc.i_alpha_max;
    if (crc.i_beta_ref > crc.i_beta_max) crc.i_beta_ref = crc.i_beta_max;

    if (crc.i_alpha_ref < -crc.i_alpha_max) crc.i_alpha_ref = -crc.i_alpha_max;
    if (crc.i_beta_ref < -crc.i_beta_max) crc.i_beta_ref = -crc.i_beta_max;

}


/*******************************************************************************/
/*		Anti_Islanding_Control_Loop_Init						   	   	 	   */
/*******************************************************************************/



void Anti_Islanding_Control_Loop_Init(void)
{
    aicl.i_alpha_max = CORRENTE_MAXIMA;
    aicl.i_beta_max = CORRENTE_MAXIMA;
    aicl.k_ilhamento = 4.6;
    aicl.i_alpha_islanding = 0;
    aicl.i_beta_islanding = 0;
    aicl.uk_notch_60Hz[0] = 0;
    aicl.yk_notch_60Hz[0] = 0;
    aicl.count_islanding = 0;
    aicl.b0_notch = b0_notch_60Hz;
    aicl.b1_notch = b1_notch_60Hz;
    aicl.b2_notch = b2_notch_60Hz;
    aicl.a1_notch = a1_notch_60Hz;
    aicl.a2_notch = a2_notch_60Hz;
    aicl.islanding_enable = 0;
}




void Anti_Islanding_Control_Loop(float w_pll, float theta_pll)
{

    //Passagem dos parâmetros
    aicl.w_pll = w_pll;
    aicl.theta_pll = theta_pll;


    aicl.uk_notch_60Hz[0] = (aicl.w_pll);

    aicl.yk_notch_60Hz[0] = (aicl.b0_notch*aicl.uk_notch_60Hz[0]) + (aicl.b1_notch*aicl.uk_notch_60Hz[1]) + (aicl.b2_notch*aicl.uk_notch_60Hz[2]) - (aicl.a1_notch*aicl.yk_notch_60Hz[1]) - (aicl.a2_notch*aicl.yk_notch_60Hz[2]);
    aicl.uk_notch_60Hz[2] = aicl.uk_notch_60Hz[1];
    aicl.uk_notch_60Hz[1] = aicl.uk_notch_60Hz[0];
    aicl.yk_notch_60Hz[2] = aicl.yk_notch_60Hz[1];
    aicl.yk_notch_60Hz[1] = aicl.yk_notch_60Hz[0];

    if (aicl.count_islanding < ms_100) aicl.count_islanding++;

    if (aicl.count_islanding >= ms_100)
    {
        aicl.islanding_enable = TRUE;
    }

    if (aicl.islanding_enable == TRUE)
    {

        aicl.i_alpha_islanding = aicl.yk_notch_60Hz[0]*aicl.k_ilhamento;
        aicl.i_beta_islanding = aicl.yk_notch_60Hz[0]*aicl.k_ilhamento;


        if (aicl.i_alpha_islanding >= (aicl.i_alpha_max))  aicl.i_alpha_islanding =  (aicl.i_alpha_max);
        if (aicl.i_alpha_islanding <= (-aicl.i_alpha_max)) aicl.i_alpha_islanding = -(aicl.i_alpha_max);
        if (aicl.i_beta_islanding >= (aicl.i_beta_max))  aicl.i_beta_islanding =  (aicl.i_beta_max);
        if (aicl.i_beta_islanding <= (-aicl.i_beta_max)) aicl.i_beta_islanding = -(aicl.i_beta_max);



    }

    else
    {
        aicl.i_alpha_islanding = 0;
        aicl.i_beta_islanding = 0;
    }


    aicl.i_alpha_islanding =   aicl.i_alpha_islanding*sin(theta_pll);
    aicl.i_beta_islanding  = - aicl.i_beta_islanding*cos(theta_pll);


}



/*******************************************************************************/
/*		LVRT_protection_Init						   	   	 				   */
/*******************************************************************************/


void LVRT_protection_Init(void)
{
    lvrt.count_lvrt=0;
    lvrt.afundamento=0;
    lvrt.disconnect=0;

    lvrt.lvrt_eq=0;
    lvrt.norma_vp=0;
    lvrt.Vpu_nivel_1 = 0.2;
    lvrt.Vpu_nivel_2 = 0.85;
    lvrt.Vpu_nivel_3 = 0.9;
    lvrt.TEMPO_1 = 0.5*FS_INV;  // = 0.5/f_amostragem;
    lvrt.TEMPO_2 = 1*FS_INV;    // = 1.0/f_amostragem;
    lvrt.TEMPO_3 = 2*FS_INV;    // = 2.0/f_amostragem;
    lvrt.k_lvrt =(lvrt.Vpu_nivel_2-lvrt.Vpu_nivel_1)/(lvrt.TEMPO_2 - lvrt.TEMPO_1);
    lvrt.disconnect = 0;
    lvrt.afundamento = 0;

}



void LVRT_protection(float norma_vp, float norma_nominal)
{
    //Passagem dos parâmetros
    lvrt.norma_vp = norma_vp;
    lvrt.norma_nominal = norma_nominal;


    if (lvrt.norma_vp/lvrt.norma_nominal < lvrt.Vpu_nivel_3)
    {
        lvrt.afundamento = TRUE;
    }

    if (lvrt.norma_vp/lvrt.norma_nominal > lvrt.Vpu_nivel_3)
    {
        lvrt.afundamento = FALSE;
        lvrt.count_lvrt = 0;
        lvrt.lvrt_eq = 0;
    }

    if (lvrt.afundamento == TRUE)
    {
        lvrt.count_lvrt++;

        lvrt.lvrt_eq =  lvrt.Vpu_nivel_1;

        if (lvrt.count_lvrt >= lvrt.TEMPO_1 && lvrt.count_lvrt < lvrt.TEMPO_2)
        {
            lvrt.lvrt_eq =  lvrt.Vpu_nivel_1 +  lvrt.k_lvrt*(lvrt.count_lvrt-lvrt.TEMPO_1);
        }

        if (lvrt.count_lvrt >= lvrt.TEMPO_2 && lvrt.count_lvrt < lvrt.TEMPO_3)
        {
            lvrt.lvrt_eq = lvrt.Vpu_nivel_2;
        }

        if (lvrt.count_lvrt >= lvrt.TEMPO_3)
        {
            lvrt.lvrt_eq = lvrt.Vpu_nivel_3;
        }
    }

    if (lvrt.norma_vp/lvrt.norma_nominal <=  lvrt.lvrt_eq && lvrt.count_lvrt > lvrt.TEMPO_1)
    {
        lvrt.disconnect = 1;
    }

}





/****************************************************************************************************************************************************************************
*	Função: 	FREQ_Protection()
*	Descrição:
*
*****************************************************************************************************************************************************************************/

#define LIMITE_SUPERIOR_FREQUENCIA 63
#define LIMITE_INFERIOR_FREQUENCIA 56.5
#define FREQUENCIA_NOMINAL 60


void FREQ_Protection_Init(void)
{
	freq_ptc.f=0;
	freq_ptc.uk_freq[0]=0;
	freq_ptc.uk_freq[1]=0;
	freq_ptc.uk_freq[2]=0;

	freq_ptc.yk_freq[0]=0;
	freq_ptc.yk_freq[1]=0;
	freq_ptc.yk_freq[2]=0;
	freq_ptc.Ts=Tax;
	freq_ptc.freq_disconnect=0;
	freq_ptc.trava_prot_freq=0;
	freq_ptc.count_freq=0;
	freq_ptc.count_freq_reset=0;

}


void FREQ_Protection(float f)
{


	// Frequencia

	//A protecao de sobrefrequencia deve atuar apenas para a faixa 56.5 > f > 63 Hz.
	//Entre o intervalo 61.5 > f > 63 Hz deve manter a operacao por ate 10 s
	//Entre o intervalo 56,5 > f > 58.5 Hz deve manter a operacao por ate 10 s
	//Acima desses valores deve atuar a protecao de sobre ou subfrequencia e desligar o sistema da rede

	freq_ptc.f = f;

	//Integrador da sobrecarga (simulador do i^2*t do fusivel)

	if (freq_ptc.f >= LIMITE_SUPERIOR_FREQUENCIA)  // 63 Hz

	{
		freq_ptc.uk_freq[0] = freq_ptc.f*freq_ptc.f - FREQUENCIA_NOMINAL*FREQUENCIA_NOMINAL;        //Entrada do integrador de sobrecarga -> (id^2 - inominal^2)

	}

	if (freq_ptc.f <= LIMITE_INFERIOR_FREQUENCIA) // 56.5 Hz
	{
		freq_ptc.uk_freq[0] = FREQUENCIA_NOMINAL*FREQUENCIA_NOMINAL - freq_ptc.f*freq_ptc.f;
	}

	if (freq_ptc.f  < LIMITE_SUPERIOR_FREQUENCIA && freq_ptc.f > LIMITE_INFERIOR_FREQUENCIA) freq_ptc.uk_freq[0] = 0;


	// Lei de controle

	if (freq_ptc.freq_disconnect == 0)
	{
		freq_ptc.yk_freq[0]  = freq_ptc.uk_freq[0]*freq_ptc.Ts + freq_ptc.yk_freq[1];

		// Atualizacao do integrador

		freq_ptc.yk_freq[1] = freq_ptc.yk_freq[0];
	}

	//Quando a entrada do integrador for menor ou igual a zero, um contador de alguns ms e responsavel por resetalo

	if (freq_ptc.uk_freq[0] <= 0 && freq_ptc.trava_prot_freq == 0)
	{
		freq_ptc.count_freq = freq_ptc.count_freq + 1.0;

		if (freq_ptc.count_freq >= ms_100)		//100ms
			{
				freq_ptc.yk_freq[0] = 0;
				freq_ptc.yk_freq[1] = 0;
				freq_ptc.uk_freq[2] = 0;
				freq_ptc.count_freq = 0;
			}
	}

	if (freq_ptc.yk_freq[0] >= 31)	  				// ((56.5)^2 - (60)^2)*tempo_sc -> nesse caso, tempo_sc = 200ms
	{												// Quando o integrador atingir o valor que reprenta o tempo em que ele deve:
		freq_ptc.freq_disconnect = 1;			// Seta um bit acusando sobrecarga
		freq_ptc.yk_freq[0] = 0;
		freq_ptc.yk_freq[1] = 0;
		freq_ptc.trava_prot_freq = 1;
	}

	else if (freq_ptc.trava_prot_freq == 0)
	{
		freq_ptc.count_freq_reset++;

		if (freq_ptc.count_freq_reset == 50)
		{
			freq_ptc.freq_disconnect = 0;
			freq_ptc.count_freq_reset=0;
		}


	}

}







//#############################################################################
// End of file 
//#############################################################################
