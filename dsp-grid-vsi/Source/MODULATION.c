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

int sign(float in);

float min, max;
float dax,dbx,dcx;
float dax_abs,dbx_abs,dcx_abs;


void MODULATION(struct INVERSOR *inv)
{


     if((inv->da > inv->db) && (inv->da > inv->dc) ) max=inv->da;
else if((inv->db > inv->da) && (inv->db > inv->dc) ) max=inv->db;
else  max=inv->dc;

     if((inv->da < inv->db) && (inv->da < inv->dc) ) min=inv->da;
else if((inv->db < inv->da) && (inv->db < inv->dc) ) min=inv->db;
else  min=inv->dc;

	inv->d0=(-0.5*(max+min-1.0));

	return;
}



int sign(float x)
{

if(x<0)return -1;
else return 1;
}


