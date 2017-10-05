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


#ifndef MODBUS_SLAVE_H_
#define MODBUS_SLAVE_H_

#include "ModbusDefinitions.h"
#include "ModbusData.h"
#include "ModbusDataHandler.h"
#include MB_DATA_MAP
#include "Serial.h"
#include "Timer.h"
#include "Crc.h"

// typedef struct ModbusSlave ModbusSlave;

struct ModbusSlave {
	ModbusState state;

	ModbusData dataRequest;
	ModbusData dataResponse;

#if MB_COILS_ENABLED
	ModbusCoilsMap coils;
#endif
#if MB_INPUTS_ENABLED
	ModbusInputsMap inputs;
#endif
#if MB_HOLDING_REGISTERS_ENABLED
	ModbusHoldingRegistersMap holdingRegisters;
#endif
#if MB_INPUT_REGISTERS_ENABLED
	ModbusInputRegistersMap inputRegisters;
#endif

	Serial serial;
	Timer timer;

	ModbusDataHandler dataHandler;

	void (*loopStates)(ModbusSlave *self);
	void (*create)(ModbusSlave *self);
	void (*start)(ModbusSlave *self);
	void (*timerT35Wait)(ModbusSlave *self);
	void (*idle)(ModbusSlave *self);
	void (*receive)(ModbusSlave *self);
	void (*process)(ModbusSlave *self);
	void (*transmit)(ModbusSlave *self);
	void (*destroy)(ModbusSlave *self);

	bool jumpProcessState;
};

void slave_loopStates(ModbusSlave *self);
inline void slave_create(ModbusSlave *self);
inline void slave_start(ModbusSlave *self);
inline void slave_timerT35Wait(ModbusSlave *self);
inline void slave_receive(ModbusSlave *self);
inline void slave_process(ModbusSlave *self);
inline void slave_transmit(ModbusSlave *self);
inline void slave_destroy(ModbusSlave *self);
ModbusSlave construct_ModbusSlave();

extern ModbusSlave mb;

#endif
