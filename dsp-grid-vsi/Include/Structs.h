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

//-----------------------------------------------------------------------------/
// Estrutura de depuração gráfica
//-----------------------------------------------------------------------------/  

struct GRAFICOS
{
	float graf1[PT];
	float graf2[PT];
	float graf3[PT];
	float *g1;
	float *g2;
	float *g3;
	int g;
	int dec;
};


//-----------------------------------------------------------------------------/
// Estrutura das variáveis do conversor
//-----------------------------------------------------------------------------/  

struct INVERSOR
{
	float vdc;
	float vab;
	float vca;
	float vbc;
	float ia_inv;
	float ib_inv;
	float ic_inv;
	float ia_grid;
	float ib_grid;
	float ic_grid;
	float m;
	float da;				// razão cíclica fase a
	float db;				// razão cíclica fase b
	float dc;				// razão cíclica fase c
	float d0;				// razão cíclica eixo alfa
	float dalfa;			// razão cíclica eixo alfa
	float dbeta;			// razão cíclica eixo beta
	float valfa;			// tensão alfa sobre capacitores do filtro LCL
	float valfa_RMS;		// tensão alfa sobre capacitores do filtro LCL
	float valfa_acc;        //
	float valfa_ref;		// tensão alfa de referência para controle de tensão
	float valfa_refn;		// referência nominal para valfa
	float valfa_erro;       // erro eixo alfa
	float vbeta;			// tensão alfa sobre capacitores do filtro LCL
	float vbeta_RMS;		// tensão alfa sobre capacitores do filtro LCL
	float vbeta_acc;
	float vbeta_ref;		// tensão beta de referência para controle de tensão
	float vbeta_refn;		// referência nominal para vbeta
	float vbeta_erro;       // erro eixo beta
	float vref;				// vetor espacial de referência de tensão
	float ialfa_inv;		// corrente alfa no indutor do inversor
	float ialfa_grid;		// corrente alfa no indutor da rede
	float ialfa_grid_acc;	// corrente alfa no indutor da rede
	float ialfa_grid_RMS;	// corrente alfa no indutor da rede
	float igrid;
	float izero_grid;       // componente de sequencia zero
	float ialfa_ref;		// corrente alfa de referência
	float ibeta_inv;		// corrente beta no indutor do inversor
	float ibeta_grid;		// corrente beta no indutor da rede
	float ibeta_grid_acc;
	float ibeta_grid_RMS;
	float ibeta_ref;		// corrente beta de referência
	float iref;				// vetor espacial de referência
	float p;				// potência ativa
	float p_avg;            // potência ativa média
	float q;				// portência reativa
	float q_avg;			// portência reativa média
	float s;				// potência aparente
	float z_i;				// impedância virtual - parte imaginária
	float z_r;				// impedância virtual - parte real
	float rlim;
	float vp;       		// Vref Droop
	float v_seqp;
	float v_seqn;
	float v_seqnd;
	float v_seqnq;
	float w_avg;             //  Frequência média medida com PLL e filtro fc=10 Hz
	float phi_seqn;
	float iac_trip_level;
	float vac_trip_level;
	float vdc_trip_level;
	int lim_case;
	int count;
	//---------------------------

#if GRIDVSI

	//Grid-Tie-VSI
	float valfa_p;
	float valfa_n;
	float vbeta_p;
	float vbeta_n;
	float norma_vp;
	float norma_vn;
	float theta;
	float w;
	float f;
	float pll_sinc_ok;
	float p_ref;
	float q_ref;
	float norma_nominal;
	float ialfa_islanding_ref;
	float ibeta_islanding_ref;
	float vdc_ref;
	float vdc_ref2;
	float crowbar_ref;

	int vdip;
	int lvrt_disconnect;
	int freq_disconnect;
	int dc_link_ok;
	int Estado;
	int first_time;
	int contatora_bypass;
	int contatora_inv;
	int control_on;
	int enable;

#endif



	//---------------------------
	float mgcc_vref;
	float mgcc_wref;
	float mgcc_pref;
};    

//-----------------------------------------------------------------------------/
// Estrutura de testes
//-----------------------------------------------------------------------------/  

struct TESTES
{
	float D;
	float amp;
	float wt;
	float t1;
	float t2;
	float t3;
	float t4;
	float t5;

};

//-----------------------------------------------------------------------------/
// Emulação
//-----------------------------------------------------------------------------/  

struct EMU
{
	float wt;
	float t1;
	float t2;
	float t3;
};

//-----------------------------------------------------------------------------/
// Estrutura de variáveis temporárias
//-----------------------------------------------------------------------------/  

struct TEMP
{
	float t1f;
	float t2f;
	float t3f;
	float t4f;
	float t5f;


	int t1i;
	int t2i;
	int t3i;

	Uint8 t1c; //  8 bits
	Uint8 t2c;
	Uint8 t3c;
};


//-----------------------------------------------------------------------------/
// Estrutura de controle do conversor
//-----------------------------------------------------------------------------/  

struct CONTROLE
{
	Uint8 ESTAGIO;
	Uint8 RELE;
	Uint8 MF; // ???
	Uint8 INIT;
	Uint8 ENABLE;
	Uint8 STATE;
	int AD_EOC;
	Uint8 PWM;
	float TIME;
	long TIMER_E0;  // Tempo para iniciar estagio 0
	unsigned int SW_CNT;
};


struct STAGE_STRUCT   // Struct for each stage
{
	Uint8 Value;
	Uint8 State;
	long PreTimer;
};



//-----------------------------------------------------------------------------/
// Estrutura de log de eventos
//-----------------------------------------------------------------------------/  

struct LOG
{
	unsigned int event_id;
	float event_value;
	float ib_grid;
	float ic_grid;
	float ib_inv;
	float ic_inv;
	float vab;
	float vca;
	float vdc;

	unsigned int state;
};

//-----------------------------------------------------------------------------/
// Estrutura para geração de sinais trigonométricos
//-----------------------------------------------------------------------------/  

struct TRIGONOMETRICO
{
	float wt;
	float amp;
	float senoA;
	float senoB;
	float senoC;
	float coseA;
	float coseB;
	float coseC;
};

//-----------------------------------------------------------------------------/
// Estrutura do PLL
//-----------------------------------------------------------------------------/  

struct PLL
{
	float valfa;
	float vbeta;
	float ialfa;
	float ibeta;
	float mod;
	float e0;
	float e1;
	float u1;
	float w;
	float wt;
	float wtx;
	int sector;
	float seq;		// variável que contém sinal para inversão de sequência de fase
	Uint8 ctrl;      // variável com campos booleanos para guardar status de testes
}; 


//--------------------------------------------------------/
// PI Controller - Direct form I
//--------------------------------------------------------/
struct PI
{
	float e0;
	float e1;
	float u0;
};
//--------------------------------------------------------/
// PID Controller - Direct form II
//--------------------------------------------------------/
struct PID
{
	float e0;
	float x0;
	float x1;
	float x2;
	float u0;
};
//--------------------------------------------------------/
// Second order Low-pass Filter - Direct form II
//--------------------------------------------------------/
struct LPF2
{
	float e0;
	float x0;
	float x1;
	float x2;
	float u0;
};

//--------------------------------------------------------/
// PR Controller - Delta operator
//--------------------------------------------------------/
struct PR
{
	float e0;
	float e1;
	float e2;
	float u0;
};

//--------------------------------------------------------/
// LFP1 Filter - Direct form I
//--------------------------------------------------------/
struct LPF1
{
	float e0;
	float e1;
	float u0;
	float u1;
};


//--------------------------------------------------------/
// General Transfer Function - first order 
//--------------------------------------------------------/
struct GTF1
{
	float e0;
	float e1;
	float u0;
	float u1;
};

//--------------------------------------------------------/
// General Transfer Function - first order 
//--------------------------------------------------------/
struct MEAS_RMS
{
#define MAX_SAMPLES 170  // Cuidado ao alterar esse valor (166 nominal)

	float buff1[MAX_SAMPLES]; //
	float buff2[MAX_SAMPLES];
	float buff3[MAX_SAMPLES];
	float buff4[MAX_SAMPLES];

	float acc1;
	float acc2;
	float acc3;
	float acc4;
//	float acc5;
//	float acc6;

//	float IbINV;
//	float IcINV;
	float IbGRID;
	float IcGRID;
	float Vab;
	float Vca;

	unsigned int idx1;
	unsigned int idx2;
	unsigned int idx3;
	unsigned int idx4;

	unsigned int state;

};
