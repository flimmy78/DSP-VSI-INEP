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



#ifndef MODBUSSETTINGS_H_
#define MODBUSSETTINGS_H_

#include "DataTypes.h"
#include "ModbusDefinitions.h"
#include "Serial.h"

// Modbus settings ========================================
#define MB_SLAVE_ID				0x01
#define MB_CHECKS				true	// ID check and CRC check (enabled by default)
#define MB_BUFFER_SIZE			256		// Size of content buffer on ModbusData - Depends on the size of your memory map
#define MB_BROADCAST_EXTRA_ID	255		// Broadcast exclusive ID (it will work with Broadcast ID 0 too)
#define MB_LIBMODBUS_TESTS		false

// Memory map settings ====================================
#if MB_LIBMODBUS_TESTS == false
#define MB_DATA_MAP						"ModbusDataMapCACC.h"
#define MB_32_BITS_REGISTERS			true
#define MB_COILS_ENABLED				1
#define MB_INPUTS_ENABLED				0
#define	MB_HOLDING_REGISTERS_ENABLED	1
#define MB_INPUT_REGISTERS_ENABLED		0
#else
#define MB_DATA_MAP						"ModbusDataMapTests.h" // Use it when you run libmodbus tests
#define MB_32_BITS_REGISTERS			false // Use it when you run libmodbus tests
#define MB_COILS_ENABLED				1
#define MB_INPUTS_ENABLED				1
#define	MB_HOLDING_REGISTERS_ENABLED	1
#define MB_INPUT_REGISTERS_ENABLED		1
#endif

// Device settings (DSP f28335)
#define CPU_FREQ			150
//#define LOW_SPEED_CLOCK 	37500000
#define LOW_SPEED_CLOCK 	15000000

// Serial settings ========================================
#define SERIAL_BAUDRATE 	38400
#define SERIAL_PARITY 		SERIAL_PARITY_NONE
#define SERIAL_BITS_NUMBER 	8

#define SERIAL_START_STOP_NUMBER_BITS	2
#if SERIAL_PARITY == SERIAL_PARITY_NONE
#define SERIAL_PARITY_NUMBER_BITS		0
#else
#define SERIAL_PARITY_NUMBER_BITS		1
#endif

// Timer settings =========================================
// Time constant

// Configure the 3.5c time for timer
// For baudrates higher than 19200 is recommended a fixed value
#if SERIAL_BAUDRATE > 19200
#define mbT35 (unsigned long) 1750
#define mbT15 (unsigned long) 750
#else
// Sum up the bits number of a common serial frame
#define SERIAL_FRAME_SIZE \
		SERIAL_START_STOP_NUMBER_BITS \
		+ SERIAL_BITS_NUMBER \
		+ SERIAL_PARITY_NUMBER_BITS
#define mbT35 (unsigned long) ( (unsigned long)(SERIAL_FRAME_SIZE) * (unsigned long)(3500000 / SERIAL_BAUDRATE) )
#define mbT15 (unsigned long) ( (unsigned long)(SERIAL_FRAME_SIZE) * (unsigned long)(1500000 / SERIAL_BAUDRATE) )
#endif

// Debug settings =========================================
#define DEBUG_UTILS_PROFILING				0		// Include the necessary files to the linker!!
#define DEBUG_LOG_ENABLED					0

// Will be used at Log.h
#define MB_DATA_REQUEST_DEBUG_ENABLED		0
#define MB_DATA_RESPONSE_DEBUG_ENABLED		0
#define MB_DATA_HANDLER_DEBUG_ENABLED		0
#define MB_SLAVE_DEBUG_ENABLED				0
#define SERIAL_DEBUG_ENABLED				0
#define TIMER_DEBUG_ENABLED					0

#endif /* MODBUSSETTINGS_H_ */
