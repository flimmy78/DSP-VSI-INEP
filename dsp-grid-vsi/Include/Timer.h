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




#ifndef MODBUS_TIMER_H_
#define MODBUS_TIMER_H_

#include "DataTypes.h"

typedef struct Timer Timer;

struct Timer {
	Uint32 reloadTime;
	bool timerEnabled;

	void (*resetTimer)();
	bool (*expiredTimer)(Timer *self);
	void (*setTimerReloadPeriod)(Timer *self, Uint32 time);
	void (*init)(Timer *self, Uint32 time);
	void (*stop)();
	void (*start)();
};

inline void timer_resetTimer();
inline bool timer_expiredTimer(Timer *self);
inline void timer_setTimerReloadPeriod(Timer *self, Uint32 time);
inline void timer_init(Timer *self, Uint32 time);
inline void timer_stop();
inline void timer_start();

Timer construct_Timer();

#endif
