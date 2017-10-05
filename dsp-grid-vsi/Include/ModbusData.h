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

#ifndef MODBUS_DATA_RESPONSE_H_
#define MODBUS_DATA_RESPONSE_H_

#include "ModbusSettings.h"

typedef struct ModbusData ModbusData;

struct ModbusData {
	Uint16 slaveAddress;
	Uint16 functionCode;
	Uint16 contentIdx;
	Uint16 content[MB_BUFFER_SIZE];
	Uint16 size;
	Uint16 crc;

	void (*clear)(ModbusData *self);
	Uint16 * (*getTransmitString)(ModbusData *self);
	Uint16 * (*getTransmitStringWithoutCRC)(ModbusData *self);
};

inline void data_clear(ModbusData *self);
inline Uint16 * data_getTransmitString(ModbusData *self);
inline Uint16 * data_getTransmitStringWithoutCRC(ModbusData *self);
ModbusData construct_ModbusData();

#endif
