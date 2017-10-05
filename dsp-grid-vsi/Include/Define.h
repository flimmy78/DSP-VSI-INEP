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
/*	FLAGS Compilação condicional   			     		  					   */
/*******************************************************************************/

#define DEBUG 0
#define FLASH 1

#define INVERSOR_1 0
#define INVERSOR_2 1

#define PROTECTION 1   // Protection on=1 
#define AD1_EMU0   0   // AD=1, EMU=0

#define MODBUS_ON  0
#define CLOSEDLOOP 1 // 1= closed loop operation, 0 open loop dx=vxref

#define DROOP 0
#define IMPVIRTUAL 0
#define FPB 0
#define GRIDVSI	1

#define PR5CTRL 0 // Controlar a harmônica de ordem 5
#define PR7CTRL 0 // Controlar a harmônica de ordem 7
#define PR11CTRL 0 // Controlar a harmônica de ordem 11

/*******************************************************************************/
/*		Arquivos Header						     		  					   */
/*******************************************************************************/


#define CPU_RATE    6.66667L    
#define DELAY_US(A) DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)
#define PIX1  		(float)3.1415926535897932384626433832795
#define PIX2 		(float)3.1415926535897932384626433832795*2

#define ct1		  	(float)0.40824829046386301636621401245098	// 1/sqrt(6) 
#define ct2		  	(float)0.81649658092772603273242802490196	// 2/sqrt(6) 
#define ct3		  	(float)0.70710678118654752440084436210485	// 1/sqrt(2) 

#define PIEACK_G3	0x0004


/*******************************************************************************/
// OBS IMPORTANTE: OS PERIODOS DOS CONVERSORES DEVEM SER PREFERENCIALEMNTE MULTIPLOS!


#define FCLK		150000000L
#define FS_INV		19980L
#define TIMER_INV 	(unsigned int)(FCLK/(2*FS_INV))

#define PHASE_PWM1 	0
#define PHASE_PWM2 	0
#define PHASE_PWM3 	0
#define PHASE_PWM4 	0
#define PHASE_PWM5 	0//(unsigned int)((float)TIMER_RET*0.6666666666666) // in falling edge PHSDIR=0
#define PHASE_PWM6 	0//(unsigned int)((float)TIMER_RET*0.6666666666666) // in rising edge  PHSDIR=1

#define DEAD_TIMEs 	0.000001	// entrar com o tempo morto desejado em segundos
#define DEAD_TIME  	(unsigned int) ((float)DEAD_TIMEs*FCLK)
#define DEAD_BAND_OUT 3 // 0 é o bypass do dead band; 3 é o full dead band


//-------------------------------------------------------//
//  Suporte Gráfico	     		  					   
//-------------------------------------------------------//
#define UseGraphs 1
#define PT	666
#define dec_max 1

/*******************************************************************************/
/*	GPIO									     		  					   */
/*******************************************************************************/

#define LED1		 	GpioDataRegs.GPBDAT.bit.GPIO60  
#define LED2	 		GpioDataRegs.GPBDAT.bit.GPIO61 
#define LED3			GpioDataRegs.GPBDAT.bit.GPIO62 
#define LED4			GpioDataRegs.GPBDAT.bit.GPIO63 

#define LED_GREEN		GpioDataRegs.GPBDAT.bit.GPIO62 
#define LED_YELLOW		GpioDataRegs.GPBDAT.bit.GPIO63 
#define LED_ORANGE		GpioDataRegs.GPBDAT.bit.GPIO60 
#define LED_RED			GpioDataRegs.GPBDAT.bit.GPIO61 

#define CLEAR_LED_GREEN	  	GpioDataRegs.GPBCLEAR.bit.GPIO62 
#define CLEAR_LED_YELLOW  	GpioDataRegs.GPBCLEAR.bit.GPIO63 
#define CLEAR_LED_ORANGE  	GpioDataRegs.GPBCLEAR.bit.GPIO60 
#define CLEAR_LED_RED		GpioDataRegs.GPBCLEAR.bit.GPIO61 

#define LED_2KIT  		GpioDataRegs.GPADAT.bit.GPIO31	//LED_2KIT
#define	LED_3KIT		GpioDataRegs.GPBDAT.bit.GPIO34	//LED_3KIT

#define SWITCH_TURNOFF  !GpioDataRegs.GPBDAT.bit.GPIO58  // SW1
#define SWITCH_RESET	!GpioDataRegs.GPBDAT.bit.GPIO59  // SW2

#define RELAY			GpioDataRegs.GPBDAT.bit.GPIO49

/*******************************************************************************/
/*	Modulation								     		  					   */
/*******************************************************************************/


/*******************************************************************************/
/*		FLASH								     		  					   */
/*******************************************************************************/


#if FLASH

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);


//---------------------------------------------------------------------------
// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location
// in either Flash or XINTF to a different RUN location in internal
// RAM
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

#endif


/*******************************************************************************/
/*	Condicionamento							     		  					   */
/*******************************************************************************/


#define KVAC_DEF (float)(1/( (470.0/(470.0+5.0*39000.0))*(4096.0/3.0)))
#define KVDC_DEF (float)(0.974733872/( (560.0/(560.0+5.0*18000.0))*(4096.0/3.0)))
#define KIAC_DEF (float)(1/( (2.125/85)*(15.0/9.1)*(4096.0/3.0)))	 


#if INVERSOR_1

#define OFFSET_IB_INV 2050.0
#define	OFFSET_IC_INV 2049.0

#define	OFFSET_IB_GRID 2046.0
#define	OFFSET_IC_GRID 2042.0

#define	OFFSET_VAB 2038.0
#define	OFFSET_VCA 2041.0

#endif

#if INVERSOR_2

#define OFFSET_IB_INV 2054.0
#define	OFFSET_IC_INV 2048.0

#define	OFFSET_IB_GRID 2042.0
#define	OFFSET_IC_GRID 2050.0

#define	OFFSET_VAB 2038.0
#define	OFFSET_VCA 2041.0

#endif


/*******************************************************************************/
/*	Depuração em Hardware					     		  					   */
/*******************************************************************************/

#define SYNC			GpioDataRegs.GPADAT.bit.GPIO0 


