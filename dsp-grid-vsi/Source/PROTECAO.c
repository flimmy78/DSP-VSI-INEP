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

extern struct CONTROLE CTRL;
extern struct LOG evlog;
extern struct INVERSOR inv;
#if UseGraphs
extern struct GRAFICOS graf; 
#endif
extern struct TESTES teste; 
extern struct TRIGONOMETRICO trig;
extern struct PID pid_id;
extern struct PID pid_iq;
extern struct PI  pi_vdc;

extern void INIT_VARIAVEIS(void);
extern void INIT_INTERRUPT(void);
extern void ENABLE_INTERRUPT(void);

void PROTECAO_IAC(float *i);
void PROTECAO_VDC(float *vdc);
void PROTECAO_VAC(float *vac);
void TURN_OFF(void);
void TZONE(void);


//----------------------------------------------------------------------------/
// Rectifier
//----------------------------------------------------------------------------/

void PROTECAO_IAC(float *i)
{
	//------------------------------------/
	// Software forced Trip
	//------------------------------------/
	EALLOW;
	EPwm2Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm4Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm6Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EDIS;
	//------------------------------------/
	// Log Eventos
	//------------------------------------/
	evlog.event_id=10;

	evlog.ib_grid=inv.ib_grid;
	evlog.ic_grid=inv.ic_grid;
	evlog.ib_inv=inv.ib_inv;
	evlog.ic_inv=inv.ic_inv;
	evlog.vab=inv.vab;
	evlog.vca=inv.vca;
	evlog.vdc=inv.vdc;

	CTRL.ENABLE=0;
	CTRL.STATE=10;
}

//----------------------------------------------------------------------------/
// DC BUS Protection
//----------------------------------------------------------------------------/

void PROTECAO_VDC(float *vdc)
{
	//------------------------------------/
	// Software forced Trip
	//------------------------------------/
	EALLOW;
	EPwm2Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm4Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm6Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EDIS;
	//------------------------------------/
	// Log Eventos
	//------------------------------------/
	evlog.event_id=11;

	evlog.ib_grid=inv.ib_grid;
	evlog.ic_grid=inv.ic_grid;
	evlog.ib_inv=inv.ib_inv;
	evlog.ic_inv=inv.ic_inv;
	evlog.vab=inv.vab;
	evlog.vca=inv.vca;
	evlog.vdc=inv.vdc;

	CTRL.ENABLE=0;
	CTRL.STATE=10;
}



//----------------------------------------------------------------------------/
// Grid Voltage Protection
//----------------------------------------------------------------------------/

void PROTECAO_VAC(float *vac)
{
	//------------------------------------/
	// Software forced Trip
	//------------------------------------/
	EALLOW;
	EPwm2Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm4Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm6Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EDIS;
	DRTM;
	DINT;
	//------------------------------------/
	// Log Eventos
	//------------------------------------/
	evlog.event_id=12;

	evlog.ib_grid=inv.ib_grid;
	evlog.ic_grid=inv.ic_grid;
	evlog.ib_inv=inv.ib_inv;
	evlog.ic_inv=inv.ic_inv;
	evlog.vab=inv.vab;
	evlog.vca=inv.vca;
	evlog.vdc=inv.vdc;

	CTRL.ENABLE=0;
	CTRL.STATE=10;
}

//----------------------------------------------------------------------------/
// TRIP ZONE routine? ?
//----------------------------------------------------------------------------/

void TZONE(void)
{

	//------------------------------------/
	// Log Eventos
	//------------------------------------/
	evlog.event_id=13;

	evlog.ib_grid=inv.ib_grid;
	evlog.ic_grid=inv.ic_grid;
	evlog.ib_inv=inv.ib_inv;
	evlog.ic_inv=inv.ic_inv;
	evlog.vab=inv.vab;
	evlog.vca=inv.vca;
	evlog.vdc=inv.vdc;

	CTRL.ENABLE=0;
	CTRL.STATE=10;
}

//----------------------------------------------------------------------------/
// User Turn off routine
//----------------------------------------------------------------------------/

void TURN_OFF(void)
{
	//------------------------------------/
	// Software forced Trip
	//------------------------------------/
	EALLOW;
	EPwm2Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm4Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EPwm6Regs.TZFRC.bit.OST = 1;			// Force one shot triger via software
	EDIS;
	//------------------------------------/
	// Log Eventos
	//------------------------------------/
	evlog.event_id=13;

	evlog.ib_grid=inv.ib_grid;
	evlog.ic_grid=inv.ic_grid;
	evlog.ib_inv=inv.ib_inv;
	evlog.ic_inv=inv.ic_inv;
	evlog.vab=inv.vab;
	evlog.vca=inv.vca;
	evlog.vdc=inv.vdc;

	CTRL.ENABLE=0;
	CTRL.STATE=10;
}

//----------------------------------------------------------------------------/
// Blink Led Routine
//----------------------------------------------------------------------------/

BLINK_LEDS()
{

	static unsigned int t1;

	if(++t1 >= (FS_INV<<1))
	{
		t1=0;
		switch(evlog.event_id)
		{

		case 10:{ // Iac
			LED_GREEN=LED_GREEN^1;
			break;}

		case 11:{ // Vdc
			LED_YELLOW=LED_YELLOW^1;
			break;}

		case 12:{ // Vca
			LED_ORANGE=LED_ORANGE^1;
			break;}

		case 13:{ // TZ
			LED_GREEN=LED_GREEN^1;
			LED_YELLOW=LED_YELLOW^1;
			LED_ORANGE=LED_ORANGE^1;
			break;}
		}
	}

}

//----------------------------------------------------------------------------/
// Blink Led Routine
//----------------------------------------------------------------------------/

CLEAR_LEDS()
{
	CLEAR_LED_YELLOW=1;
	CLEAR_LED_RED=1;
	CLEAR_LED_ORANGE=1;
	CLEAR_LED_GREEN=1;
}

