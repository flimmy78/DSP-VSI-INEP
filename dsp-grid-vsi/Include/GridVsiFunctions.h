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

#include "DataTypes.h"

#ifndef _GRIDVSIFUNCTIONS_H_
#define _GRIDVSIFUNCTIONS_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <math.h>
#include "DSP28x_ControlBoard.h"
#include "stdio.h"
#include "C28x_FPU_FastRTS.h"
#include "math.h"

//Parâmetros
#define PI_RAD      3.1415926535898
#define TWO_PI      6.2831853071796
#define PI_DIV_TWO  1.5707963267949  
#define OMEGA       376.99111843078
#define TRUE        1
#define FALSE       0

//Tempos de contagem convertidos para milisegundos para uma frequência de interrupção de 20kHz
#define ms_100  2000
#define ms_200  4000
#define ms_300  6000
#define ms_400  8000
#define ms_500  10000
#define ms_600  12000
#define ms_700  14000
#define ms_800  16000
#define ms_900  18000
#define ms_1000 20000


//Corrente máxima de pico
#define CORRENTE_MAXIMA 100


//Frequência de amostragem
#define Tsample Tax;



/****************************************************************************************************************************************************************************
*   Função:     DSOG_PLL()
*   Descrição:
*
*****************************************************************************************************************************************************************************/


struct DSOG_PLL
{

    float Va;
    float Vb;
    float Vc;
    float Ts;
    float Valpha;
    float Vbeta;
    float erro_alpha;
    float erro_beta;
    float erro_fll;
    float Valpha_out;
    float Vbeta_out;
    float erro_alpha_1;
    float erro_beta_1;
    float Valpha_out_90;
    float Vbeta_out_90;
    float w_pll;
    float uk_int1[1];
    float yk_int1[2];
    float uk_int2[1];
    float yk_int2[2];
    float uk_int3[1];
    float yk_int3[2];
    float uk_int4[1];
    float yk_int4[2];
    float uk_int5[1];
    float yk_int5[2];
    float Valpha_p;
    float Valpha_n;
    float Vbeta_p;
    float Vbeta_n;
    float theta_dsog;
    float theta_aux;
    float norma_vp;
    float norma_vn;
    float f_pll;
    float norma_w;
	float k_dsog;

    float uk_pb1[3];
    float yk_pb1[3];
    float uk_pb2[3];
    float yk_pb2[3];

    float b0_pb;
    float b1_pb;
    float b2_pb;
    float a1_pb;
    float a2_pb;

    int count_theta;
    int count;
    int count_theta2;
    int count_pll;
    int pll_sinc_ok;

//}; DSOG_PLL dsog_pll;
};




struct DSOG_PLL_INPUTS
{
    float va;
    float vb;
    float vc;
};



struct DSOGPLL_OUTPUTS
{
    float valpha;
    float vbeta;
    float valpha_p;
    float valpha_n;
    float vbeta_p;
    float vbeta_n;
    float norma_vp;
    float norma_vn;
    float theta;
    float w;
	float f;
    int pll_sinc_ok;
};




//Declaração das funções
void DSOG_PLL_Init(void);
void DSOG_PLL(struct DSOG_PLL_INPUTS *i, struct DSOGPLL_OUTPUTS *o);





/****************************************************************************************************************************************************************************
*   Função:     Instantaneous_Power_Calculation()
*   Descrição:
*
*****************************************************************************************************************************************************************************/


void Instantaneous_Power_Calculation(float valpha, float vbeta, float ialpha, float ibeta);
void Instantaneous_Power_Calculation_Init(void);


struct IPC
{

    float P_inst;
    float Q_inst;
    float Valpha;
    float Vbeta;
    float i_alpha;
    float i_beta;

    float uk_pb1[3];
    float yk_pb1[3];
    float uk_pb2[3];
    float yk_pb2[3];

    float b0_pb;
    float b1_pb;
    float b2_pb;
    float a1_pb;
    float a2_pb;



};






/****************************************************************************************************************************************************************************
*   Função:     SpaceVectorPWM()
*   Descrição:  Calcula as razões cíclicas em SVPWM
*****************************************************************************************************************************************************************************/




struct SVM 
{

    float temp0;
    float vo_ref;
    float max;
    float min;
    float va_ref;
    float vb_ref;
    float vc_ref;
};




void Space_Vector_Modulation(float ma, float mb, float mc);
void Space_Vector_Modulation_Init(void);





/****************************************************************************************************************************************************************************
*   Função:     Reactive_Power_Compensation()
*   Descrição:
*
*****************************************************************************************************************************************************************************/


void Reactive_Power_Compensation_Init(void);
void Reactive_Power_Compensation(float norma_p, float norma_nominal, int enable);


struct RPC
{

    float temp2;
    float temp3;
    float temp4;
    float Qnominal;
    float Qoffset;
    float Qmax;
    float norma_vp;
    float norma_nominal;
    float Q_ref;

    int output_enable;

};








/****************************************************************************************************************************************************************************
*   Função:     Current_Control_Law()
*   Descrição:
*
*****************************************************************************************************************************************************************************/



void Current_Control_Loop(float ia, float ib, float ic, float vdc, float Valpha_p, float Vbeta_p, float i_alpha_ref, float i_beta_ref);
void Current_Control_Loop_Init(void);


struct CCL
{

    float ia;
    float ib;
    float ic;
    float vdc;
    float Valpha_p;
    float Vbeta_p;
    float i_alpha;
    float i_beta;
    float va_ref;
    float vb_ref;
    float vc_ref;
    float erro_i_alpha;
    float erro_i_beta;
    float pr_alpha_p;
    float pr_beta_p;
    float v_alpha_ref;
    float v_beta_ref;
    float uk_pr_alpha[3];
    float yk_pr_alpha[3];
    float uk_pr_beta[3];
    float yk_pr_beta[3];

    float uk_pr3_alpha[3];
    float yk_pr3_alpha[3];
    float uk_pr3_beta[3];
    float yk_pr3_beta[3];

	float uk_pr4_alpha[3];
    float yk_pr4_alpha[3];
    float uk_pr4_beta[3];
    float yk_pr4_beta[3];

    float uk_pr5_alpha[3];
    float yk_pr5_alpha[3];
    float uk_pr5_beta[3];
    float yk_pr5_beta[3];
    float uk_pr7_alpha[3];
    float yk_pr7_alpha[3];
    float uk_pr7_beta[3];
    float yk_pr7_beta[3];
    float i_alpha_max;
    float i_beta_max;
    float i_alpha_ref;
    float i_beta_ref;
    float yk_pb1[3];
    float uk_pb1[3];
    float yk_pb2[3];
    float uk_pb2[3];
    float yk_pb3[3];
    float uk_pb3[3];
    float yk_pb4[3];
    float uk_pb4[3];
    float b0_pr_i;
    float b1_pr_i;
    float b2_pr_i;
    float a1_pr_i;
    float a2_pr_i;
	
	float b0_pr3_i;
    float b1_pr3_i;
    float b2_pr3_i;
    float a1_pr3_i;
    float a2_pr3_i;

	float b0_pr4_i;
    float b1_pr4_i;
    float b2_pr4_i;
    float a1_pr4_i;
    float a2_pr4_i;



    float b0_pr5_i;
    float b1_pr5_i;
    float b2_pr5_i;
    float a1_pr5_i;
    float a2_pr5_i;
    float b0_pr7_i;
    float b1_pr7_i;
    float b2_pr7_i;
    float a1_pr7_i;
    float a2_pr7_i;
    float Kp_pr_i;


};





/****************************************************************************************************************************************************************************
*   Função:     Voltage_Control_Law()
*   Descrição:
*
*****************************************************************************************************************************************************************************/

struct VCL
{

    float norma_vp;
    float P_ref;
	float P_nominal;
    float vdc;
    float vdc_ref;
    float erro_v;
    float uk_v[3];
    float yk_v[3];
    float uk_v2[3];
    float yk_v2[3];
    float yk_v_aw[3];
    float uk_v_aw[3];
    float yk_v_aw2[3];
    float uk_v_aw2[3];
    float temp1;
    float d_limite;
    float idc_max;
    float idc_nominal;
    float P_ref_max;
    float norma_nominal;
    float kp_v;
    float b0_v;
    float b1_v;
    float b2_v;
    float a1_v;
    float a2_v;
    float temp_aw;
    float vdc_ref2;
    float erro_v2;
    float kp_v2;
    float b0_v2;
    float b1_v2;
    float a1_v2;
    float temp2;
    float d_limite2;
	float uk_pb[3];
	float yk_pb[3];
	float kp_pb;
    float b0_pb;
    float b1_pb;
    float b2_pb;
    float a1_pb;
    float a2_pb;
	float uk_pb2[3];
	float yk_pb2[3];
	

    int VDC_ANTI_WINDUP;
	int control_mode; 		//0 = pre-charge, 1 = normal operation, 2 = overvoltage
	int dc_link_ok;

};



void Voltage_Control_Loop(float vdc, float vdc_ref, float vdc_ref2, float norma_vp, float norma_nominal); 
void Voltage_Control_Loop_Init(void);







/****************************************************************************************************************************************************************************
*   Função:     Current_Reference_Calculation()
*   Descrição:
*
*****************************************************************************************************************************************************************************/

void Current_Reference_Calculation(float P_ref, float Q_ref, float Valpha_p, float Vbeta_p, float Valpha_n, float Vbeta_n, float norma_nominal);
void Current_Reference_Calculation_Init(void);


struct CRC
{
    float k1;
    float k2;
    float P_ref;
    float Q_ref;
    float Valpha_p;
    float Vbeta_p;
    float Valpha_n;
    float Vbeta_n;
    float norma_vp;
    float norma_vn;
    float norma_nominal;
    float Valpha_p_o;
    float Vbeta_p_o;
    float Valpha_n_o;
    float Vbeta_n_o;
    float ip_alpha_p;
    float ip_beta_p;
    float ip_alpha_n;
    float ip_beta_n;
    float iq_alpha_p_o;
    float iq_beta_p_o;
    float iq_alpha_n_o;
    float iq_beta_n_o;
    float i_alpha_p_ref;
    float i_beta_p_ref;
    float i_alpha_n_ref;
    float i_beta_n_ref;
    float i_alpha_ref;
    float i_beta_ref;
    float i_alpha_max;
    float i_beta_max;
    int PNSC;
    int BPSC;





};






/****************************************************************************************************************************************************************************
*   Função:     Current_Reference_Calculation()
*   Descrição:
*
*****************************************************************************************************************************************************************************/

void Anti_Islanding_Control_Loop(float w_pll, float theta_pll);
void Anti_Islanding_Control_Loop_Init(void);


struct AICL
{
    float i_alpha_max;
    float i_beta_max;
    float k_ilhamento;
    float i_alpha_islanding;
    float i_beta_islanding;
    float uk_notch_60Hz[3];
    float yk_notch_60Hz[3];
    float b0_notch;
    float b1_notch;
    float b2_notch;
    float a1_notch;
    float a2_notch;
    float w_pll;
    float theta_pll;

    int count_islanding;
    int islanding_enable;

};





/****************************************************************************************************************************************************************************
*   Função:     LVRT_Protection()
*   Descrição:
*
*****************************************************************************************************************************************************************************/


void LVRT_protection(float norma_vp, float norma_nominal);
void LVRT_protection_Init(void);

struct LVRT
{

    int count_lvrt;
    int afundamento;
    int disconnect;

    float lvrt_eq;
    float norma_vp;
    float norma_nominal;
    float Vpu_nivel_1;
    float Vpu_nivel_2;
    float Vpu_nivel_3;
    float TEMPO_1;
    float TEMPO_2;
    float TEMPO_3;
    float k_lvrt;


};

/****************************************************************************************************************************************************************************
*   Função:     FREQ_Protection()
*   Descrição:
*
*****************************************************************************************************************************************************************************/

void FREQ_Protection(float w);
void FREQ_Protection_Init(void);


struct FREQ_PTC
{
	float f;
	float uk_freq[3];
	float yk_freq[3];
	float Ts;


	int freq_disconnect;
	int trava_prot_freq;
	int count_freq;
	int count_freq_reset;
};





#ifdef __cplusplus
};
#endif

#endif /* _GRIDVSIFUNCTIONS_H_ */





