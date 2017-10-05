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

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_CpuTimers.h"
#include "Timer.h"
#include "Log.h"
#include "ModbusSettings.h"

struct CPUTIMER_VARS CpuTimer0;

void timer_resetTimer(){
	CpuTimer0Regs.TCR.bit.TRB = 1;
	TIMER_DEBUG();
}

bool timer_expiredTimer(Timer *self){
	Uint32 timerZeroed = CpuTimer0Regs.TCR.bit.TIF;
	TIMER_DEBUG();

	if (timerZeroed == true) {
		return true;
	}
	else {
		return false;
	}
}

void timer_setTimerReloadPeriod(Timer *self, Uint32 time){
	TIMER_DEBUG();

	self->stop();
	self->reloadTime = time;

	CpuTimer0.CPUFreqInMHz = CPU_FREQ;
	CpuTimer0.PeriodInUSec = time;
	CpuTimer0.RegsAddr->PRD.all = (Uint32) time * CPU_FREQ;
}


void timer_init(Timer *self, Uint32 time){
	// START: GOT FROM TEXAS FILES //////////////////////////////////////
	// CPU Timer 0
    // Initialize address pointers to respective timer registers:
    CpuTimer0.RegsAddr = &CpuTimer0Regs;
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;
    // Make sure timer is stopped:
    CpuTimer0Regs.TCR.bit.TSS = 1;
    // Reload all counter register with period value:
    CpuTimer0Regs.TCR.bit.TRB = 1;
    // Reset interrupt counters:
    CpuTimer0.InterruptCount = 0;
    // END: GOT FROM TEXAS FILES ////////////////////////////////////////

	// Config the timer reload period
	self->reloadTime = time;
	CpuTimer0.CPUFreqInMHz = CPU_FREQ;
	CpuTimer0.PeriodInUSec = time;
	CpuTimer0Regs.PRD.all = (Uint32) time * CPU_FREQ;
//	CpuTimer0.RegsAddr->PRD.all = 262500;//(long) time * CPU_FREQ;

	// Run mode settings
	CpuTimer0Regs.TCR.bit.SOFT = 1;
	CpuTimer0Regs.TCR.bit.FREE = 1;     // Timer Free Run

	// If needed, you can set interruptions and other things here
	//	CpuTimer0.RegsAddr->TCR.bit.TIE = 1;      // 0 = Disable/ 1 = Enable Timer Interrupt

	TIMER_DEBUG();
}

void timer_stop(){
	CpuTimer0Regs.TCR.bit.TSS = 1;
	TIMER_DEBUG();
}

void timer_start(){
	CpuTimer0Regs.TCR.bit.TSS = 0;
	TIMER_DEBUG();
}

Timer construct_Timer(){
	Timer timer;

	timer.timerEnabled = false;
	timer.reloadTime = 0;

	timer.resetTimer = timer_resetTimer;
	timer.expiredTimer = timer_expiredTimer;
	timer.setTimerReloadPeriod = timer_setTimerReloadPeriod;
	timer.init = timer_init;
	timer.stop = timer_stop;
	timer.start = timer_start;

	TIMER_DEBUG();

	return timer;
}
