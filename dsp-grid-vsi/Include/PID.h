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
/* PID algorithm				  			    		  					   */
/*******************************************************************************/


/*------------------------------------------------------------------------------
	Object definition
------------------------------------------------------------------------------*/
typedef struct
	{ 
	void (*calc)();   		// Ptr to calc fn
	void (*init)();   		// Ptr to init fn     
	float e;   				// Input: e 
 	float u;				// Output: u	
	float x0;				// Internal: x(k) 
 	float x1;				// Internal: x(k-1)
 	float x2;				// Internal: x(k-2)
 	float A1;				// Internal: Variable for A1 coefficient
 	float A2; 				// Internal: Variable for A2 coefficient
	float B0;				// Internal: Variable for B0 coefficient	
 	float B1;				// Internal: Variable for B1 coefficient
 	float B2;				// Internal: Variable for B2 coefficient	
	} PID;	            

typedef PID *PID_handle;

/*------------------------------------------------------------------------------
	Prototypes for the function
------------------------------------------------------------------------------*/

void PID_calc(PID_handle);
void PID_init(PID_handle);

/*------------------------------------------------------------------------------
	Default coefficients for object initialization
------------------------------------------------------------------------------*/

#define PID_DEFAULTS { (void (*)())PID_calc,\
			 (void (*)())PID_init,\
             0,             \
             0,             \
             0,             \
             0,             \
             0,             \
             0,             \
             0,             \
			 0,             \
             0,             \
             0}
             

