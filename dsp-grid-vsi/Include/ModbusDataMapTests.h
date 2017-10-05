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

#ifndef MODBUSVARMAP_H_
#define MODBUSVARMAP_H_

#include "ModbusSettings.h"

#if MB_COILS_ENABLED
typedef struct ModbusCoilsMap ModbusCoilsMap;
struct ModbusCoilsMap{
	Uint8	dummy1;
	Uint8	dummy2;
	Uint8	dummy3;
	Uint8	dummy4;
	Uint8	dummy5;
	Uint8	dummy6;
	Uint8	dummy7;
	Uint8	dummy8;
	Uint8	dummy9;
	Uint8	dummy10;
	Uint8	dummy11;
	Uint8	dummy12;
	Uint8	dummy13;
	Uint8	dummy14;
	Uint8	dummy15;
	Uint8	dummy16;
	Uint8	dummy17;
	Uint8	dummy18;
	Uint8	dummy19;
	Uint8	dummy20;
	Uint8	dummy21;
	Uint8	dummy22;
	Uint8	dummy23;
	Uint8	dummy24;
	Uint8	dummy25;
	Uint8	dummy26;
	Uint8	dummy27;
	Uint8	dummy28;
	Uint8	dummy29;
	Uint8	dummy30;
	Uint8	dummy31;
	Uint8	dummy32;
	Uint8	dummy33;
	Uint8	dummy34;
	Uint8	dummy35;
	Uint8	dummy36;
	Uint8	dummy37;
	Uint8	dummy38;
	Uint8	dummy39;
	Uint8	dummy40;
	Uint8	dummy41;
};

ModbusCoilsMap construct_ModbusCoilsMap();
#endif

#if MB_INPUTS_ENABLED
typedef struct ModbusInputsMap ModbusInputsMap;
struct ModbusInputsMap{
	Uint8	dummy1;
	Uint8	dummy2;
	Uint8	dummy3;
	Uint8	dummy4;
	Uint8	dummy5;
	Uint8	dummy6;
	Uint8	dummy7;
	Uint8	dummy8;
	Uint8	dummy9;
	Uint8	dummy10;
	Uint8	dummy11;
	Uint8	dummy12;
	Uint8	dummy13;
	Uint8	dummy14;
	Uint8	dummy15;
	Uint8	dummy16;
	Uint8	dummy17;
	Uint8	dummy18;
	Uint8	dummy19;
	Uint8	dummy20;
	Uint8	dummy21;
	Uint8	dummy22;
	Uint8	dummy23;
	Uint8	dummy24;
	Uint8	dummy25;
	Uint8	dummy26;
	Uint8	dummy27;
	Uint8	dummy28;
	Uint8	dummy29;
};

ModbusInputsMap construct_ModbusInputsMap();
#endif

#if MB_HOLDING_REGISTERS_ENABLED
typedef struct ModbusHoldingRegistersMap ModbusHoldingRegistersMap;
struct ModbusHoldingRegistersMap {
	Uint16	dummy1;
	Uint16	dummy2;
	Uint16	dummy3;
	Uint16	dummy4;
	Uint16	dummy5;
	Uint16	dummy6;
	Uint16	dummy7;
	Uint16	dummy8;
	Uint16	dummy9;
	Uint16	dummy10;
	Uint16	dummy11;
	Uint16	dummy12;
	Uint16	dummy13;
	Uint16	dummy14;
	Uint16	dummy15;
	Uint16	dummy16;
	Uint16	dummy17;
	Uint16	dummy18;
	Uint16	dummy19;
	Uint16	dummy20;
	Uint16	dummy21;
	Uint16	dummy22;
	Uint16	dummy23;
	Uint16	dummy24;
	Uint16	dummy25;
	Uint16	dummy26;
	Uint16	dummy27;
	Uint16	dummy28;
//	Uint16	dummy29;
};

ModbusHoldingRegistersMap construct_ModbusHoldingRegistersMap();
#endif

#if MB_INPUT_REGISTERS_ENABLED
typedef struct ModbusInputRegistersMap ModbusInputRegistersMap;
struct ModbusInputRegistersMap {
	Uint16	dummy1;
	Uint16	dummy2;
	Uint16	dummy3;
	Uint16	dummy4;
	Uint16	dummy5;
	Uint16	dummy6;
	Uint16	dummy7;
	Uint16	dummy8;
	Uint16	dummy9;
	Uint16	dummy10;
	Uint16	dummy11;
	Uint16	dummy12;
	Uint16	dummy13;
	Uint16	dummy14;
	Uint16	dummy15;
	Uint16	dummy16;
	Uint16	dummy17;
	Uint16	dummy18;
	Uint16	dummy19;
	Uint16	dummy20;
	Uint16	dummy21;
	Uint16	dummy22;
	Uint16	dummy23;
	Uint16	dummy24;
	Uint16	dummy25;
};

ModbusInputRegistersMap construct_ModbusInputRegistersMap();
#endif

#endif /* MODBUSVARMAP_H_ */
