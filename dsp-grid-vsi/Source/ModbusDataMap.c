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

#include "ModbusSettings.h"
#include MB_DATA_MAP
#include "Log.h"

#if MB_COILS_ENABLED
ModbusCoilsMap construct_ModbusCoilsMap(){
	ModbusCoilsMap coilsMap = {0};
	return coilsMap;
}
#endif

#if MB_INPUTS_ENABLED
ModbusInputsMap construct_ModbusInputsMap(){
	ModbusInputsMap inputsMap = {0};
	return inputsMap;
}
#endif

#if MB_INPUT_REGISTERS_ENABLED
ModbusInputRegistersMap construct_ModbusInputRegistersMap(){
	ModbusInputRegistersMap registersMap = {0};
	return registersMap;
}
#endif

#if MB_HOLDING_REGISTERS_ENABLED
ModbusHoldingRegistersMap construct_ModbusHoldingRegistersMap(){
	ModbusHoldingRegistersMap registersMap = {0};
	return registersMap;
}
#endif
