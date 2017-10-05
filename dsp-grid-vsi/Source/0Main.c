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

//#include "DSP2833x_Device.h"
#include "DSP28x_ControlBoard.h"
#include "stdio.h"
#include "Define.h"
#include "Structs.h" 
#include "C28x_FPU_FastRTS.h"
#include "math.h"
#include "MSO_Coeff.h"

#include "ModbusSlave.h"
#include "GridVsiFunctions.h"





/*******************************************************************************/
/*		Protótipos das Funções 	 								   	   	  	   */
/*******************************************************************************/
void MODULATION(struct INVERSOR *inv);
void INIT_SYSTEM(void);
void InitSysCtrl(void);
void InitFlash(void);
void INIT_EPWM(void);
void INIT_INTERRUPT(void);
void INIT_PIE_VEC_TABLE(void);
void INIT_PIE_CTRL(void);
void ENABLE_INTERRUPT(void);
void INIT_ADC(void);
void INIT_GPIO(void);

void WatchDog_Led2(void);
void WatchDog_Led3(void);
void Sin_Generator(void);
void Current_Sin_Gen(float Ipk);
void State_Machine(void);
void pre_carga_1(void);
void pre_carga_2(void);




//----------------------------------------------------/
// Proteção
//----------------------------------------------------/

extern void PROTECAO_IAC(float *i);
extern void PROTECAO_VDC(float *vdc);
extern void PROTECAO_VAC(float *vac);
extern void TURN_OFF(void);
extern void TZONE(void);
extern void BLINK_LEDS(void);
extern void CLEAR_LEDS(void);
//----------------------------------------------------/
// Outras
//----------------------------------------------------/
void INIT_VARIAVEIS(void);
void RE_INIT_VARIAVEIS(void);
void INIT_COM_REGISTERS(void);

extern void ESTAGIO_0(void);
extern void ESTAGIO_1(void);
extern void ESTAGIO_2(void);

void RMS_CALC(void);
float rms_filter(float sample);

void interrupt MAIN_ISR(void);

/*******************************************************************************/
/*		DEFINES								     		  					   */
/*******************************************************************************/



#define INIT			0
#define PRE_LOAD1		1
#define PRE_LOAD2		2
#define CONTROL_LOOP	3
#define TURNOFF			4



/*******************************************************************************/
/*		FLASH								     		  					   */
/*******************************************************************************/
/*
undefined          first referenced
  symbol                in file
 ---------          ----------------
 _INIT_FLASH        ./0Main.obj
 _RamfuncsLoadEnd   ./0Main.obj
 _RamfuncsLoadStart ./0Main.obj
 _RamfuncsRunStart  ./0Main.obj */

#if DEBUG
/* Just a definition test */
#endif

#if FLASH // Disable 28335_RAM_lnk.cmd and enable F28335.cmd
// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped using
// the linker cmd file.

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

#pragma CODE_SECTION(MAIN_ISR, "ramfuncs");
#pragma CODE_SECTION(Sin_Generator, "ramfuncs");
#pragma CODE_SECTION(Current_Sin_Gen, "ramfuncs");
#pragma CODE_SECTION(RMS_CALC, "ramfuncs");
#pragma CODE_SECTION(MODULATION, "ramfuncs");
#pragma CODE_SECTION(WatchDog_Led2, "ramfuncs");
#pragma CODE_SECTION(WatchDog_Led3, "ramfuncs");
#pragma CODE_SECTION(PROTECAO_IAC, "ramfuncs");
#pragma CODE_SECTION(PROTECAO_VAC, "ramfuncs");
#pragma CODE_SECTION(PROTECAO_VDC, "ramfuncs");


// These are defined by the linker (see F28335.cmd)
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsLoadSize;
#endif



//----------------------------------------------------/
// ModBus
//----------------------------------------------------/

ModbusSlave mb;


/*******************************************************************************/
/*		Variáveis Globais	    			    		  					   */
/*******************************************************************************/

/** Gráficos **/
#if UseGraphs

#pragma DATA_SECTION(graf , "GRAF1");

struct GRAFICOS graf;

#endif

/*******************************************************************************/

float teste1=0,teste2,teste3;
int teste_int,teste_int2,teste_int3;
int DA,DB,DC;


int32 count_led=0, count_led2=0;
int loopCount=0;




//################## VARIÁVEIS ###################//


//struct FT2_DELTA calib; 

struct LOG evlog;
struct INVERSOR inv;
struct MEAS_RMS rms;
struct CONTROLE CTRL;
struct TRIGONOMETRICO trig;
struct PLL pll;
struct PI PI_alfa,PI_beta;
struct PI pi_vdc;
struct PID pid_ialfa,pid_ibeta;

struct PR PR1_alfa,PR1_beta;
struct PR PR5_alfa,PR5_beta;
struct PR PR7_alfa,PR7_beta;
struct PR PR11_alfa,PR11_beta;
struct PR PR13_alfa,PR13_beta;
struct PR PR1i_alfa,PR1i_beta;
struct PR PRS_zalfa, PRS_zbeta;

struct PR CI_alfa, CI_beta;

struct LPF1 LPF1_P, LPF1_Q, LPF1_V;
struct LPF1 LPF1_g1, LPF1_g2, LPF1_g3, LPF1_g4, LPF1_g5, LPF1_g6;
struct LPF2 LPF2_g1,LPF2_g2,LPF2_g3,LPF2_g4;

struct GTF1 CVAC_alfa,CVAC_beta;

struct TEMP temp;



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






//##### INICIO DOS TESTES

void main(void)
{

	// INIT_SYSTEM();

	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2833x_SysCtrl.c file.
	InitSysCtrl();

#if FLASH

	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	// Call Flash Initialization to setup flash waitstates
	// This function must reside in RAM

	//	INIT_FLASH();
	// Call Flash Initialization to setup flash waitstates
	// This function must reside in RAM
	InitFlash();

#endif


	INIT_GPIO();
	INIT_INTERRUPT();
	INIT_PIE_CTRL();
	INIT_PIE_VEC_TABLE();
	INIT_ADC();
	INIT_EPWM();
	INIT_VARIAVEIS();

	//Reposicionar




	INIT_COM_REGISTERS();

	LED2kitDAT=0;
	LED3kitDAT=0;

	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	/*
LED_GREEN=1;
LED_YELLOW=1;
LED_ORANGE=1;
LED_RED=1;

	 */
	/*******************************************************************************/
	// Modbus
	/*******************************************************************************/
#if MODBUS_ON
	mb = construct_ModbusSlave();
#endif
	/*******************************************************************************/

	ENABLE_INTERRUPT();


	/*******************************************************************************/
	// Infinite Loop
	/*******************************************************************************/
	while(1) // Loop Infinito
	{

		loopCount++;



#if MODBUS_ON 	
		//---------------------
		mb.loopStates(&mb);
		//--------------------
#endif

	};

	/*******************************************************************************/
} // End of main() routine


/*******************************************************************************/
// MAIN Interrupt Service Routine
/*******************************************************************************/
interrupt void MAIN_ISR()
{

	LED_RED=1;
	SYNC=1;

	WatchDog_Led2();
	WatchDog_Led3();


	//-----------------------------------------------
	// Manual turnoff switch verification
	//-----------------------------------------------

	if(SWITCH_TURNOFF)  // Test for manual turn off switch
	{
		TURN_OFF();
	}

	//-----------------------------------------------


	teste_int=AdcRegs.ADCST.bit.SEQ1_BSY;

	//----------------------------------------------------------------------------/
	//	Reset interrupt an acknowledgement flags
	//----------------------------------------------------------------------------/

	CTRL.AD_EOC=0;						// clear EOC time out flag
	EPwm2Regs.ETCLR.bit.INT=1;			//Limpa flag permitindo de INT periferica
	EPwm4Regs.ETCLR.bit.INT=1;			//Limpa flag permitindo de INT periferica
	PieCtrlRegs.PIEACK.all= PIEACK_G3;  // Reseta o bit de acknowledgement

	//----------------------------------------------------------------------------/
	//	Protection
	//----------------------------------------------------------------------------/

#if PROTECTION

	if(++CTRL.MF==1)
	{
		CTRL.MF=0;

#define PIAC_MAX 10  // Valor máximo de pico de corrente
#define PVAC_MAX 280.0 //Mais um comentario na proteção
#define PVDC_MAX 400.0


		if(fabs(inv.ib_inv)>PIAC_MAX)	PROTECAO_IAC(&inv.ib_inv);
		if(fabs(inv.ic_inv)>PIAC_MAX)	PROTECAO_IAC(&inv.ic_inv);
		if(fabs(inv.ib_grid)>PIAC_MAX)	PROTECAO_IAC(&inv.ib_grid);
		if(fabs(inv.ic_grid)>PIAC_MAX)	PROTECAO_IAC(&inv.ic_grid);

		if(fabs(inv.vab)>PVAC_MAX)		PROTECAO_VAC(&inv.vab);
		if(fabs(inv.vca)>PVAC_MAX)		PROTECAO_VAC(&inv.vca);

		if(inv.vdc>PVDC_MAX) 			PROTECAO_VDC(&inv.vdc);

	}

#endif

	//----------------------------------------------------------------------------/
	//	Read A/D channels (1) or software emulation (0) (analog input variables)
	//----------------------------------------------------------------------------/

#if AD1_EMU0

	LABEL_ADTEST:  //

	if(AdcRegs.ADCST.bit.SEQ1_BSY)// loop a espera do fim da conversão
	{
		if(++CTRL.AD_EOC>20)
			TURN_OFF(); // depende da frequencia do clock
		goto LABEL_ADTEST;
	}



	teste_int2=AdcRegs.ADCST.bit.SEQ1_BSY;

	inv.ib_inv=-((AdcRegs.ADCRESULT0>>5)+(AdcRegs.ADCRESULT7>>5)-OFFSET_IB_INV)*KIAC_DEF; 
	inv.ic_inv=-((AdcRegs.ADCRESULT1>>5)+(AdcRegs.ADCRESULT8>>5)-OFFSET_IC_INV)*KIAC_DEF; 

	inv.ib_grid=((AdcRegs.ADCRESULT2>>5)+(AdcRegs.ADCRESULT9>>5)-OFFSET_IB_GRID)*KIAC_DEF; 
	inv.ic_grid=((AdcRegs.ADCRESULT3>>5)+(AdcRegs.ADCRESULT10>>5)-OFFSET_IC_GRID)*KIAC_DEF; 

	inv.vab=-((AdcRegs.ADCRESULT5>>4)-OFFSET_VAB)*KVAC_DEF;
	inv.vca= ((AdcRegs.ADCRESULT6>>4)-OFFSET_VCA)*KVAC_DEF;

	inv.vdc=((AdcRegs.ADCRESULT4>>4))*KVDC_DEF; 


	inv.vbc= -inv.vab-inv.vca;
	inv.ia_inv=-(inv.ib_inv+inv.ic_inv);
	inv.ia_grid=-(inv.ib_grid+inv.ic_grid);


#else  //----Software emulation----//
/*
	inv.vab= 269.44387*pll.ialfa;
	inv.vca= 269.44387*pll.ibeta;
	inv.vbc= 0.0;
	inv.vdc= 0.0; 

	inv.ib_inv= 0.0;
	inv.ic_inv= 0.0;

	inv.ib_grid= 5*pll.ialfa+sin(pll.wt*5); 
	inv.ic_grid= 5*pll.ialfa+sin(pll.wt*11);

	inv.ia_inv=-(inv.ib_inv+inv.ic_inv);
	inv.ia_grid=-(inv.ib_grid+inv.ic_grid);
*/

	Sin_Generator();



#endif

#if GRIDVSI

	//Logica de sincronismo

	dsog_pll_in.va = inv.vab;
	dsog_pll_in.vb = inv.vbc;
	dsog_pll_in.vc = inv.vca;

	DSOG_PLL(&dsog_pll_in, &dsog_pll_out);

	inv.valfa = dsog_pll_out.valpha;
	inv.vbeta = dsog_pll_out.vbeta;
	inv.valfa_p = dsog_pll_out.valpha_p;
	inv.valfa_n = dsog_pll_out.valpha_n;
	inv.vbeta_p = dsog_pll_out.vbeta_p;
	inv.vbeta_n = dsog_pll_out.vbeta_n;
	inv.norma_vp = dsog_pll_out.norma_vp;
	inv.norma_vn = dsog_pll_out.norma_vn;
	inv.theta = dsog_pll_out.theta;
	inv.w = dsog_pll_out.w;
	inv.f = dsog_pll_out.f;
	inv.pll_sinc_ok = dsog_pll_out.pll_sinc_ok;

//--------------------------------------------------------------------------------------------------------------------------------------
	//Executa maquina de estados
	State_Machine();

//--------------------------------------------------------------------------------------------------------------------------------------


#else
	//-------------------------------------------------------//
	// Transformações de coordenadas
	//-------------------------------------------------------//
	inv.valfa= 0.408248290463863*(inv.vab - inv.vca);  // 1/sqrt(6)
	inv.vbeta= -0.707106781*(inv.vab+inv.vca);         // 1/sqrt(2)

	inv.ialfa_inv=-1.224744871*(inv.ib_inv+inv.ic_inv);
	inv.ibeta_inv=0.707106781*(inv.ib_inv-inv.ic_inv);

	inv.ialfa_grid=-1.224744871*(inv.ib_grid+inv.ic_grid);
	inv.ibeta_grid=0.707106781*(inv.ib_grid-inv.ic_grid);

	//*******************************************************//
	// Potências instantâneas
	//*******************************************************//
	inv.p = inv.valfa*inv.ialfa_grid + inv.vbeta*inv.ibeta_grid;
	inv.q = -inv.valfa*inv.ibeta_grid + inv.vbeta*inv.ialfa_grid;

	//-------------------------------------
	//LPF - Potência P     fc=1 Hz
	//-------------------------------------
	inv.p_avg=inv.p*B0_LPF1+LPF1_g2.e1*B1_LPF1-LPF1_g2.u1*A1_LPF1;
	LPF1_g2.e1=inv.p;
	LPF1_g2.u1=inv.p_avg;
	//-------------------------------------
	//LPF - Potência Q    fc=1 Hz
	//-------------------------------------

	inv.q_avg=inv.q*B0_LPF1+LPF1_g3.e1*B1_LPF1-LPF1_g3.u1*A1_LPF1;
	LPF1_g3.e1=inv.q;
	LPF1_g3.u1=inv.q_avg;

	//*******************************************************//
	// PLL para pré-sincronização
	//*******************************************************//
	pll.valfa = inv.valfa*0.005248638811;
	pll.vbeta = inv.vbeta*0.005248638811;

	//-----------------------------------------------/
	// Potência Trifásica
	//-----------------------------------------------/
	pll.e0 = (pll.vbeta * pll.ialfa) + (pll.valfa * pll.ibeta);
	//	pll.e0=0;// teste em MA
	//-----------------------------------------------/
	// Controlador PI + INT
	//-----------------------------------------------/
	pll.w+=pll.e0*B0_PLL+pll.e1*B1_PLL;
	pll.e1=pll.e0;
	pll.wt+=pll.w*TS_PLL;
	if(pll.wt>PIX1 ) pll.wt=pll.wt-PIX2;
	sincos(pll.wt,&(pll.ialfa),&(pll.ibeta));
	//--------------------------------------------------------/
	// Filtro passa baixa segunda ordem fc=10 Hz
	// Amplitude tensão seq. positiva
	//--------------------------------------------------------/
	LPF2_g1.x2=LPF2_g1.x1;
	LPF2_g1.x1=LPF2_g1.x0;
	LPF2_g1.x0=(inv.valfa*pll.ialfa - inv.vbeta*pll.ibeta)-LPF2_g1.x1*A1_LPF2_10-LPF2_g1.x2*A2_LPF2_10;
	inv.v_seqp=LPF2_g1.x0*B0_LPF2_10+LPF2_g1.x1*B1_LPF2_10+LPF2_g1.x2*B2_LPF2_10;
	//--------------------------------------------------------/
	// Filtro passa baixa segunda ordem fc=10 Hz
	// Amplitude tensão seq. negativa
	//--------------------------------------------------------/
	LPF2_g2.x2=LPF2_g2.x1;
	LPF2_g2.x1=LPF2_g2.x0;
	LPF2_g2.x0=(inv.valfa*pll.ialfa + inv.vbeta*pll.ibeta)-LPF2_g2.x1*A1_LPF2_1-LPF2_g2.x2*A2_LPF2_1;
	inv.v_seqnd=LPF2_g2.x0*B0_LPF2_1+LPF2_g2.x1*B1_LPF2_1+LPF2_g2.x2*B2_LPF2_1;
	//-------------------------------------
	LPF2_g3.x2=LPF2_g3.x1;
	LPF2_g3.x1=LPF2_g3.x0;
	LPF2_g3.x0=(inv.valfa*pll.ibeta - inv.vbeta*pll.ialfa)-LPF2_g3.x1*A1_LPF2_1-LPF2_g3.x2*A2_LPF2_1;
	inv.v_seqnq=LPF2_g3.x0*B0_LPF2_1+LPF2_g3.x1*B1_LPF2_1+LPF2_g3.x2*B2_LPF2_1;
	//--------------------------------------------------------/
	inv.v_seqn=(inv.v_seqnd*inv.v_seqnd + inv.v_seqnq*inv.v_seqnq);
	if(inv.v_seqnd<0.000001)inv.v_seqnd=0.000001; // proteção para divsão por zero
	inv.phi_seqn=atan2(inv.v_seqnq,inv.v_seqnd);
	//--------------------------------------------------------/
	// Filtro passa baixa segunda ordem fc=10 Hz
	// Frequência filtrada
	//--------------------------------------------------------/
	LPF2_g4.x2=LPF2_g4.x1;
	LPF2_g4.x1=LPF2_g4.x0;
	LPF2_g4.x0=(pll.w-377.0) -LPF2_g4.x1*A1_LPF2_10-LPF2_g4.x2*A2_LPF2_10;
	inv.w_avg=LPF2_g4.x0*B0_LPF2_10+LPF2_g4.x1*B1_LPF2_10+LPF2_g4.x2*B2_LPF2_10;
	inv.w_avg+=377.0;
	//----------------------------------------------------------------------------/
	//	Other calculations
	//----------------------------------------------------------------------------/



	RMS_CALC();

	//CTRL.STATE=2; // não liberar o estágio seguinte

	//----------------------------------------------------------------------------/
	//	State Machine
	//----------------------------------------------------------------------------/

	switch(CTRL.STATE)
	{

	//---------------------------------------------------------/
	//	State 0
	//---------------------------------------------------------/

	case 0:
	{
		/*
	if(CTRL.ENABLE)
	{ESTAGIO_0();
	}
		 */

		//---------------------------
		// Espera comando do mgcc ou usuário
		//---------------------------
		if((CTRL.SW_CNT+=SWITCH_RESET)==(TIMER_INV<<4)) // sw reset => SW2
		{
			CTRL.SW_CNT=0;
			CTRL.ENABLE=1;
			CTRL.STATE=1;
		}
		break;
	}
	//---------------------------------------------------------/
	//	State 1
	//---------------------------------------------------------/
	case 1:
	{
		/*
	if(CTRL.PWM)
	{	
//	ESTAGIO_1();

	//------------------------------------------
	// Clear tripzone flags - Enable PWM otputs
	//------------------------------------------
	EALLOW;
	EPwm2Regs.TZCLR.bit.OST = 1;			// Clear one shot triger via software
	EPwm4Regs.TZCLR.bit.OST = 1;			// Clear one shot triger via software
	EPwm6Regs.TZCLR.bit.OST = 1;			// Clear one shot triger via software
	EDIS;

		 */

		//---------------------------
		// Considera que não tem rede e é a primeira unidade
		//---------------------------

		inv.vp=0;
		CTRL.STATE=2;
		LED2kitDAT=1;
		break;
	}
	//---------------------------------------------------------/
	//	State 2
	//---------------------------------------------------------/
	case 2:
	{
		inv.vp+=0.02861; // rampa de partida
		if(inv.vp>inv.mgcc_vref)
			inv.vp=inv.mgcc_vref;

		ESTAGIO_2();
		//------------------------------------------
		// Clear tripzone flags - Enable PWM otputs
		//------------------------------------------
		EALLOW;
		EPwm2Regs.TZCLR.bit.OST = 1;			// Clear one shot triger via software
		EPwm4Regs.TZCLR.bit.OST = 1;			// Clear one shot triger via software
		EPwm6Regs.TZCLR.bit.OST = 1;			// Clear one shot triger via software
		EDIS;

		if(CTRL.ENABLE==0)
		{
			EALLOW;
			EPwm2Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
			EPwm4Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
			EPwm6Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
			EDIS;
			CTRL.STATE=10;
		}
		break;
	}

	//---------------------------------------------------------/
	//	State 10 - PROTECAO/ERRO
	//---------------------------------------------------------/
	case 10:
	{
		BLINK_LEDS();
		//----------------------
		// Reinicializa sistema
		//----------------------
		if((CTRL.SW_CNT+=SWITCH_RESET)==(TIMER_INV<<4))
		{
			CLEAR_LEDS();
			CTRL.ENABLE=1;
			CTRL.STATE=1;
			RE_INIT_VARIAVEIS();
		}
		break;
	}	
	//---------------------------------------------------------/
	//	Default State
	//---------------------------------------------------------/
	default:
	{
		TURN_OFF();
		break;
	}
	} // end of state machine


#endif

	//---------------------------------------------------------
	// Output
	//---------------------------------------------------------

	inv.da = (0.81649658*inv.dalfa)*0.002631578947; 						   // 1/380
	inv.db = (-0.40824829*inv.dalfa  + 0.707106781*inv.dbeta)*0.002631578947;  // 1/380
	inv.dc = (-0.40824829*inv.dalfa  - 0.707106781*inv.dbeta)*0.002631578947;  // 1/380

	MODULATION(&inv);

	if((inv.da+inv.d0)<0)inv.da=0;
	if((inv.db+inv.d0)<0)inv.db=0;
	if((inv.dc+inv.d0)<0)inv.dc=0;

	//-------------------------------------------------------//
	// Atualização das razões cíclicas - Inversor
	//-------------------------------------------------------//

	EPwm6Regs.CMPA.half.CMPA=(unsigned int) ((inv.da+inv.d0)*TIMER_INV);
	EPwm4Regs.CMPA.half.CMPA=(unsigned int) ((inv.db+inv.d0)*TIMER_INV);
	EPwm2Regs.CMPA.half.CMPA=(unsigned int) ((inv.dc+inv.d0)*TIMER_INV);

	//----------------------------------------------------------------------------/
	//	ModBus
	//----------------------------------------------------------------------------/
	//TESTE

#if MODBUS_ON
	/*
mb.holdingRegisters.FrequenciaCa=inv.w_avg*0.159154943;
mb.holdingRegisters.TensaoCc=inv.vdc;
mb.holdingRegisters.PotenciaAtivaTotal=inv.p_avg;
mb.holdingRegisters.PotenciaReativaTotal=inv.q_avg;
	 */

	//O MGCC envia valor de tensão de linha RMS = nominal =190.55 RMS
	// que é a própria tensão de pico em alfa beta

	/*
inv.mgcc_vref=mb.holdingRegisters.AmplitudeDeTensaoCa; 

if(inv.mgcc_vref>200.0)inv.mgcc_vref=200.0;
if(inv.mgcc_vref<0.0)inv.mgcc_vref=0.0;
	 */
	//CTRL.ENABLE=mb.coils.Liga;
	/*
inv.mgcc_wref= mb.holdingRegisters.FrequenciaDeOperacao*0.6283185307;// frequência enviada em int *10

if(inv.mgcc_wref>380.13)inv.mgcc_wref=380.13;
if(inv.mgcc_wref<373.84)inv.mgcc_wref=373.84;

inv.mgcc_pref =mb.holdingRegisters.SetPointDePotenciaAtiva;
	 */


	/*
	//------------------------------------/
	// Restart System
	//------------------------------------/

	INIT_VARIAVEIS();
	INIT_INTERRUPT();  
	ENABLE_INTERRUPT();
	 */

#endif


#if 0
	inv.mgcc_vref=190.0; //190.52
	inv.mgcc_wref=377.0;
#endif

	//----------------------------------------------------------------------------/
	//	HW Debug
	//----------------------------------------------------------------------------/

	LED_RED=0;
	SYNC=0;

	//----------------------------------------------------------------------------/
	//	Suporte Gráfico
	//----------------------------------------------------------------------------/
#if UseGraphs
	if(++graf.dec==dec_max)
	{
		graf.dec=0;

		graf.graf1[graf.g]=*graf.g1;
		graf.graf2[graf.g]=*graf.g2;
		graf.graf3[graf.g]=*graf.g3;

		if(++graf.g==PT)
		{
			graf.g=0;
		}
	}
#endif



}//EOF


/****************************************************************************************************************************************************************************
*	Função: 	State_Machine()
*	Descrição:
*
*****************************************************************************************************************************************************************************/



void State_Machine(void)
{
	// Maquina de estados do conversor

	switch (inv.Estado)
	{

		case INIT:	//Inicialização depois do boot

			inv.first_time = 1;
			inv.contatora_bypass = 0;
			inv.contatora_inv=0;
			inv.control_on = 0;
			inv.enable = 0;
			inv.Estado = PRE_LOAD1;

		break;

		case PRE_LOAD1: //Pre-carga

			//Estagio 1 da pre-carga
			pre_carga_1();

		break;

		case PRE_LOAD2:

			//Estagio 2 da pre-carga
			pre_carga_2();

		break;

		case CONTROL_LOOP:	//Loop Controle


			if (inv.control_on == TRUE)
			{

				//Executa o algoritmo da malha de tensão

				inv.vdc_ref = 400;

				//Malha de tensão
				Voltage_Control_Loop(inv.vdc, inv.vdc_ref, inv.vdc_ref2, inv.norma_vp, inv.norma_nominal);
				inv.p_ref = vcl.P_ref;
				inv.crowbar_ref = vcl.yk_v2[0];


				#define RPC 1

				#if RPC
				if (inv.pll_sinc_ok == TRUE && inv.dc_link_ok == TRUE)
				{
					//Compensação de potência reativa
					//Reactive_Power_Compensation(inv.norma_vp, inv.norma_nominal, inv.vdip);
					inv.q_ref = rpc.Q_ref;
				}
				#endif

				#define RLC_LOAD 0

				#if RLC_LOAD	/*Teste da malha de corrente com carga RL
				//Sin_Generator();
				//Current_Sin_Gen(10);
				*/

				/*
				//Calculo das referencias de corrente a partir de P e Q
				inv.vdc = 400;
				inv.p_ref = 0; //Ver Sin_Generator
				*/
				#endif


				//Calculo das referencias de corrente
				Current_Reference_Calculation(inv.p_ref, inv.q_ref, inv.valfa_p, inv.vbeta_p, inv.valfa_n, inv.vbeta_n, inv.norma_nominal);
				inv.ialfa_ref = crc.i_alpha_ref;
				inv.ibeta_ref = crc.i_beta_ref;

				//--------------

				#if 0
				//Proteção anti-ilhamento

				Anti_Islanding_Control_Loop(inv.w, inv.theta);

				inv.ialfa_islanding_ref = aicl.i_alpha_islanding;
				inv.ibeta_islanding_ref = 	aicl.i_beta_islanding;

				inv.ialfa_ref = inv.ialfa_ref + inv.ialfa_islanding_ref;
				inv.ibeta_ref  = inv.ibeta_ref  + inv.ibeta_islanding_ref;

				#endif


				//Executa algoritmo que calcula a malha de controle de corrente
				Current_Control_Loop(inv.ia_inv, inv.ib_inv, inv.ic_inv, inv.vdc, inv.valfa_p, inv.vbeta_p, inv.ialfa_ref, inv.ibeta_ref);
				inv.da = ccl.va_ref;
				inv.db = ccl.vb_ref;
				inv.dc = ccl.vc_ref;
				inv.ialfa_inv = ccl.i_alpha;
				inv.ibeta_inv = ccl.i_beta;

				//--------------

				//Calculo das potências instantâneas
				Instantaneous_Power_Calculation(inv.valfa, inv.vbeta, inv.ialfa_inv, inv.ibeta_inv);
				inv.p_avg = ipc.P_inst;
				inv.q_avg = ipc.Q_inst;



				#if 0

				RMS_CALC();

				//Proteção LVRT
				LVRT_protection(inv.norma_vp, inv.norma_nominal);
				inv.vdip = lvrt.afundamento;
				inv.lvrt_disconnect = lvrt.disconnect;

				//Proteção Limites Frequência
				FREQ_Protection(inv.f);
				inv.freq_disconnect = freq_ptc.freq_disconnect;

				if (inv.lvrt_disconnect == TRUE || inv.freq_disconnect == TRUE)
				{
					inv.enable = 0;
					inv.Estado = TURNOFF;
				}

				else
				{
					inv.Estado = CONTROL_LOOP;
				}

				#endif

			}


		break;



		case TURNOFF:
			//Desliga e aguarda rearme
			//Inserir lógica de descarga do barramento CC


		break;

	}
}




/****************************************************************************************************************************************************************************
*	Função: 	pre_carga1()
*	Descrição:
*
*****************************************************************************************************************************************************************************/

int pre_carga1=TRUE, pre_carga2=FALSE,  erro_pc=0, count_erro_pc=0;
int count_pre_carga=0;


#define Vrede_pico	311

void pre_carga_1(void)
{

	if(pre_carga1 == TRUE)
	{
		inv.contatora_bypass = FALSE;
		inv.contatora_inv = TRUE;

		count_pre_carga++;

		if (count_pre_carga <= ms_600)
		{

			if (/*count_pre_carga >= ms_100 && */inv.vdc > 0.9*Vrede_pico)
			{
				count_pre_carga = ms_100;
				pre_carga1 = FALSE;
				pre_carga2 = TRUE;
				inv.vdc_ref = Vrede_pico;
				inv.Estado = PRE_LOAD2;
			}

		}

		else
		{
			//sinalizar erro de pre-carga
		}
	}


}

/****************************************************************************************************************************************************************************
*	Função: 	pre_carga2()
*	Descrição:
*
*****************************************************************************************************************************************************************************/


#define vdc_ref_nominal 400


void pre_carga_2(void)
{

	if (pre_carga2 == TRUE)
	{

		if (inv.vdc_ref < vdc_ref_nominal)
		{
			inv.vdc_ref=inv.vdc_ref+0.1;
		}

		else
		{
			inv.vdc_ref = vdc_ref_nominal;
		}


		if (inv.vdc >= vdc_ref_nominal)
		{
			inv.Estado = CONTROL_LOOP;
			inv.dc_link_ok = TRUE;
		}

		inv.q_ref = 0;
		inv.contatora_inv = TRUE;
		inv.contatora_bypass = TRUE;
		inv.control_on = TRUE;
		inv.enable = TRUE;

		//Executa o algoritmo da malha de tensão
		Voltage_Control_Loop(inv.vdc, inv.vdc_ref, inv.vdc_ref2, inv.norma_vp, inv.norma_nominal);
		inv.p_ref = vcl.P_ref;
		inv.q_ref = 0;
		inv.crowbar_ref = vcl.yk_v2[0];

		//Limitação da potência durante pre-carga
		if (inv.p_ref  > 1000)  inv.p_ref = 1000;
		if (inv.p_ref  < -1000) inv.p_ref = -1000;

		//Calculo das referencias de corrente
		Current_Reference_Calculation(inv.p_ref, inv.q_ref, inv.valfa_p, inv.vbeta_p, inv.valfa_n, inv.vbeta_n, inv.norma_nominal);
		inv.ialfa_ref = crc.i_alpha_ref;
		inv.ibeta_ref = crc.i_beta_ref;


		//Executa algoritmo que calcula a malha de controle de corrente
		Current_Control_Loop(inv.ia_inv, inv.ib_inv, inv.ic_inv, inv.vdc, inv.valfa_p, inv.vbeta_p, inv.ialfa_ref, inv.ibeta_ref);
		inv.da = ccl.va_ref;
		inv.db = ccl.vb_ref;
		inv.dc = ccl.vc_ref;
		inv.ialfa_inv = ccl.i_alpha;
		inv.ibeta_inv = ccl.i_beta;

		//--------------

		//Calculo das potências instantâneas
		Instantaneous_Power_Calculation(inv.valfa, inv.vbeta, inv.ialfa_inv, inv.ibeta_inv);
		inv.p_avg = ipc.P_inst;
		inv.q_avg = ipc.Q_inst;


	}

 }








//#############################################################################
// End of File
//#############################################################################



#define INITIAL 1  /* Initial value of the filter memory. */
#define SAMPLES 166

float rms_filter(float sample)
{
      static float rmsValue = INITIAL;
      static float sum_squares = SAMPLES*INITIAL*INITIAL;

    sum_squares -= sum_squares/SAMPLES; // Substract 1 sample from the accumulator
    sum_squares += sample*sample;  // square the instantanous current and Add it to the accumulator

    rmsValue = sum_squares/SAMPLES; // Get the mean square value.
    rmsValue = sqrt(rmsValue);         // Get RMS value

    return rmsValue;
}



// #define RMSIDX 166

void RMS_CALC()
{

	LED_GREEN=1;
	switch(rms.state)
	{
	case 1: // inv.vab
	{
		rms.acc1 = rms.acc1 - (rms.buff1[rms.idx1]*rms.buff1[rms.idx1]) + inv.vab*inv.vab;

		rms.buff1[rms.idx1] = inv.vab;
		if(++rms.idx1==166)
			rms.idx1=0;
#if MODBUS_ON
		mb.holdingRegisters.TensaoF1F2Saida=sqrt(rms.acc1*0.006024096386);
#else
       rms.Vab = sqrt(rms.acc1*0.006024096386);
#endif
		rms.state=2;
		break;
	}

	case 2: //inv.vca
	{
		rms.acc2=rms.acc2 - (rms.buff2[rms.idx2]*rms.buff2[rms.idx2]) + inv.vca*inv.vca;
		rms.buff2[rms.idx2] = inv.vca;
		if(++rms.idx2==166)
			rms.idx2=0;
#if MODBUS_ON
		mb.holdingRegisters.TensaoF2F3Saida=sqrt(rms.acc2*0.006024096386);
#else
       rms.Vca = sqrt(rms.acc2*0.006024096386);
#endif
		rms.state=3;
		break;
	}

	case 3: //inv.ib_grid
	{
		rms.acc3=rms.acc3 - (rms.buff3[rms.idx3]*rms.buff3[rms.idx3]) + inv.ib_grid*inv.ib_grid;
		rms.buff3[rms.idx3] = inv.ib_grid;
		if(++rms.idx3==166)
			rms.idx3=0;
#if MODBUS_ON
		mb.holdingRegisters.CorrenteF1Saida=sqrt(rms.acc3*0.006024096386);
#else
       rms.IbGRID = sqrt(rms.acc3*0.006024096386);
#endif
		rms.state=4;
		break;
	}

	case 4: // inv.ic_grid
	{
		rms.acc4=rms.acc4 - (rms.buff4[rms.idx4]*rms.buff4[rms.idx4]) + inv.ic_grid*inv.ic_grid;
		rms.buff4[rms.idx4] = inv.ic_grid;
		if(++rms.idx4==166)
			rms.idx4=0;
#if MODBUS_ON
		mb.holdingRegisters.CorrenteF2Saida=sqrt(rms.acc4*0.006024096386);
#else
       rms.IcGRID = sqrt(rms.acc4*0.006024096386);
#endif
		rms.state=1;
		break;
	}

	default:
	{
		rms.state=1;
		break;
	}
	}
	LED_GREEN=0;
}



//----------------------------------------------------------------------------/
//	Calibration & offset
//----------------------------------------------------------------------------/


//	teste.t1 = (AdcRegs.ADCRESULT0>>5)+(AdcRegs.ADCRESULT9>>5);  // inv.ia
//	teste.t1 = (AdcRegs.ADCRESULT1>>5)+(AdcRegs.ADCRESULT10>>5); // inv.ib
//	teste.t1 = (AdcRegs.ADCRESULT5>>5)+(AdcRegs.ADCRESULT6>>5);	 // ret.ia
//	teste.t1 = ret.ib;//(AdcRegs.ADCRESULT7>>5)+(AdcRegs.ADCRESULT8>>5);  // ret.ib
//	calib.e0 = (AdcRegs.ADCRESULT2>>4);							 // inv.vab
//	calib.e0 = (AdcRegs.ADCRESULT3>>4);							 // inv.vbc

//  calib.e2+= (calib.e1 * Delta);
//  calib.e1+= (calib.e0 * Delta);
//  calib.e0 =  teste.t1  - (calib.e1 * A1_CAL) - (calib.e2 *  A2_CAL);
//  calib.u0 = (calib.e0 * B0_CAL) + (calib.e1 * B1_CAL) + (calib.e2 * B2_CAL); 


/****************************************************************************************************************************************************************************
*	Função: 	WatchDog_Leds()
*	Descrição: 	Controla os leds do Kit
*****************************************************************************************************************************************************************************/



void WatchDog_Led2(void)
{


	count_led++;

	if (count_led <= ms_100)
	{
		LED_2KIT = 1;
	}

	if (count_led >= ms_200 && count_led <= ms_300)
	{
		LED_2KIT = 0;

	}

	if (count_led > ms_300)
	{
		count_led = 0;
	}

	//-----------------------------


}

void WatchDog_Led3(void)
{
	count_led2++;

	if (count_led2 <= ms_500)
	{
		LED_3KIT = 1;
	}

	if (count_led2 >= ms_500 && count_led2 <= ms_1000)
	{
		LED_3KIT = 0;

	}

	if (count_led2 > ms_1000)
	{
		count_led2 = 0;
	}
}

/****************************************************************************************************************************************************************************
*	Função: 	Sin_Generator()
*	Descrição: 	Gerador de 3 senos defasados entre si de 120º
*****************************************************************************************************************************************************************************/

#define F_GRID 60	//60Hz
int count_sin=0;
float Vpk = 179.6;
float Ipk = 10;

void Sin_Generator(void)
{


	float sin1, sin2, sin3;
	int SIN_PERIOD = (unsigned int)(FS_INV/F_GRID); 				//SIN_PERIOD = f_sample/f_sin

	count_sin++;

	if (count_sin > SIN_PERIOD) count_sin = 0;

	sin1 = count_sin*TWO_PI/SIN_PERIOD;
	sin2 = count_sin*TWO_PI/SIN_PERIOD + 0.6666*TWO_PI;
	sin3 = count_sin*TWO_PI/SIN_PERIOD - 0.6666*TWO_PI;



	inv.vab = (Vpk*sin(sin1));
	inv.vbc = (Vpk*sin(sin2));
	inv.vca = (Vpk*sin(sin3));

	inv.ia_inv = Ipk*sin(inv.theta);
	inv.ib_inv = Ipk*sin(inv.theta + 0.6666*TWO_PI);
	inv.ic_inv=-(inv.ia_inv+inv.ib_inv);

	inv.ia_grid = inv.ia_inv;
	inv.ib_grid = inv.ib_inv;
	inv.ic_grid = -(inv.ia_grid+inv.ib_grid);



}


/****************************************************************************************************************************************************************************
*	Função: 	Current_Sin_Gen()
*	Descrição: 	Gerador referências de corrente para teste com carga RL off-grid
*****************************************************************************************************************************************************************************/

int count_sin2=0;



void Current_Sin_Gen(float Ipk)
{

	float sin1, sin2, Ipk_ref;
	int SIN_PERIOD = (unsigned int)(FS_INV/F_GRID); 				//SIN_PERIOD = f_sample/f_sin

	Ipk_ref = Ipk;

	count_sin2++;

	if (count_sin2 > SIN_PERIOD) count_sin2 = 0;

	sin1 = count_sin2*TWO_PI/SIN_PERIOD;
	sin2 = count_sin2*TWO_PI/SIN_PERIOD - PI_DIV_TWO;

	inv.ialfa_ref = Ipk_ref*sin(sin1);
	inv.ibeta_ref = Ipk_ref*sin(sin2);

}
