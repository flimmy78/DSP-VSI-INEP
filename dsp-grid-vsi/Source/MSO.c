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
#include "MSO.h"
#include "C28x_FPU_FastRTS.h"
/*******************************************************************************/
/* Phase-Locked-Loop algorithm    			    		  					   */
/*******************************************************************************/

void PLL_calc(PLL *v)
{	


  v->e0  = (v->xbeta * v->yalfa)+(v->xalfa * v->ybeta);

  v->u0	+= (v->B0 * v->e0) + (v->B1 * v->e1);

  v->e1  =  v->e0;

  v->wt += v->u0 + v->u1;

  v->u1  =v->u0;

  if(v->wt > PIX1)v->wt = v->wt - PIX2;

//  v->yalfa = sin(v->wt);
  
//  v->ybeta = cos(v->wt);
  
  sincos(v->wt, &(v->yalfa), &(v->ybeta));


}// fim da rotina de calculo do PID


/*******************************************************************************/
/* PID algorithm				  			    		  					   */
/*******************************************************************************/

void PID_calc(PID *v)
{	
    
v->x2= v->x1;

v->x1= v->x0;

v->x0 = v->e0 - (v->A1 * v->x1) - (v->A2 * v->x2);

v->u0 = (v->B0 * v->x0)  + (v->B1 * v->x1) + (v->B2 * v->x2);

// Tem que verificar como realizar o anti-windup para forma direta II

}// fim da rotina de calculo do PID


/*******************************************************************************/
/* PI algorithm				  			    		  					   */
/*******************************************************************************/

void PI_calc(PI *v)
{	

v->u0 += (v->e0 * v->B0)  + (v->e1 * v->B1);
v->e1 = v->e0;

}// fim da rotina de calculo do PI

