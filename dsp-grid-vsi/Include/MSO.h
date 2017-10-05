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
/* Phase-Locked-Loop algorithm    			    		  					   */
/*******************************************************************************/

/*------------------------------------------------------------------------------
	Object definition
------------------------------------------------------------------------------*/
typedef struct
	{ 
	void (*calc)();   		// Ptr to calc fn
	void (*init)();   		// Ptr to init fn     
	float xalfa;   			// Input: X_Alfa 
 	float xbeta;			// Input: X_Beta	
	float yalfa;			// Internal: Y_Alfa 
 	float ybeta;			// Internal: Y_Beta
 	float e0;				// Internal: three-phase real power
 	float e1;				// Internal: three-phase real power preview
 	float u0;
 	float u1; 
	float wt1;				// Internal: theta in previous calculation	
 	float wt;				// Output: theta =u1
 	float B0;				// Internal filter loop coefficient	
 	float B1;   			// Internal filter loop coefficient
	} PLL;	            

typedef PLL *PLL_handle;

/*------------------------------------------------------------------------------
	Prototypes for the function
------------------------------------------------------------------------------*/

void PLL_calc(PLL_handle);
void PLL_init(PLL_handle);

/*------------------------------------------------------------------------------
	Default coefficients for object initialization
------------------------------------------------------------------------------*/

#define PLL_DEFAULTS {  (void (*)(Uint32))PLL_calc,\
			 (void (*)(Uint32))PLL_init,\
             0,             \
             0,             \
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
	float e0;   			// Input: e 
 	float u0;				// Output: u	
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
             

/*******************************************************************************/
/* PI algorithm				  			    		  					   		*/
/*******************************************************************************/


/*------------------------------------------------------------------------------
	Object definition
------------------------------------------------------------------------------*/

typedef struct
	{ 
	void (*calc)();   		// Ptr to calc fn
	void (*init)();   		// Ptr to init fn     
	float e0;   			// Input: e
	float e1; 
 	float u0;				// Output: u	
 	float B0;				// Internal: Variable for A1 coefficient
 	float B1; 				// Internal: Variable for A2 coefficient	
	} PI;	            

typedef PI *PI_handle;

/*------------------------------------------------------------------------------
	Prototypes for the function
------------------------------------------------------------------------------*/

void PI_calc(PI_handle);
void PI_init(PI_handle);

/*------------------------------------------------------------------------------
	Default coefficients for object initialization
------------------------------------------------------------------------------*/

#define PI_DEFAULTS { (void (*)())PI_calc,\
			 (void (*)())PI_init,\
             0,             \
             0,             \
			 0,             \
             0,             \
             0}
            
/*******************************************************************************/
/* Clarke Transformation algorithm    			    		  					   */
/*******************************************************************************/

/*------------------------------------------------------------------------------
	Object definition
------------------------------------------------------------------------------*/
/*
typedef struct
	{ 
	void (*calc)();   		// Ptr to calc fn 
	float xalfa;   			// Input: X_Alfa 
 	float xbeta;			// Input: X_Beta	
	float yalfa;			// Internal: Y_Alfa 
 	float ybeta;			// Internal: Y_Beta
 	float e0;				// Internal: three-phase real power
 	float e1;				// Internal: three-phase real power preview
 	float u0;
 	float u1; 
	float wt1;				// Internal: theta in previous calculation	
 	float wt;				// Output: theta =u1
 	float B0;				// Internal filter loop coefficient	
 	float B1;   			// Internal filter loop coefficient
	} PLL;	            

typedef PLL *PLL_handle;
*/
/*------------------------------------------------------------------------------
	Prototypes for the function
------------------------------------------------------------------------------*/
/*
void Clarke_calc(PLL_handle);

*/
