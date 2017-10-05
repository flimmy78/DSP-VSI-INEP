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



#ifndef MODBUS_SERIAL_H_
#define MODBUS_SERIAL_H_

#include "DataTypes.h"

typedef struct Serial Serial;

// Parity constants
typedef enum {
	SERIAL_PARITY_NONE,
	SERIAL_PARITY_EVEN,
	SERIAL_PARITY_ODD
} SerialParity;

struct Serial {
	Uint16 bitsNumber;
	Uint16 parityType;
	Uint32 baudrate;

	Uint16 fifoWaitBuffer;

	void (*clear)();
	Uint16 (*rxBufferStatus)();
	void (*setSerialRxEnabled)(bool status);
	void (*setSerialTxEnabled)(bool status);
	void (*init)(Serial *self);
	void (*transmitData)(Uint16 * data, Uint16 size);
	Uint16 (*getRxBufferedWord)();
	bool (*getRxError)();
};

void serial_clear();
inline Uint16 serial_rxBufferStatus();
inline void serial_setSerialRxEnabled(bool status);
inline void serial_setSerialTxEnabled(bool status);
inline void serial_init(Serial *self);
inline void serial_transmitData(Uint16 * data, Uint16 size);
inline Uint16 serial_getRxBufferedWord();
inline bool serial_getRxError();
Serial construct_Serial();

#endif
