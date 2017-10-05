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
	Uint8	Status;
	Uint8	Falha;
	Uint8	ComandoOn;
	Uint8	ComandoOff;

};

ModbusCoilsMap construct_ModbusCoilsMap();
#endif

#if MB_INPUTS_ENABLED
typedef struct ModbusInputsMap ModbusInputsMap;
struct ModbusInputsMap{
	Uint8 dummy0;
	Uint8 dummy1;
	Uint8 dummy2;
	Uint8 dummy3;
	Uint8 dummy4;
	Uint8 dummy5;
	Uint8 dummy6;
	Uint8 dummy7;
	Uint8 dummy8;
	Uint8 dummy9;
	Uint8 dummy10;
	Uint8 dummy11;
	Uint8 dummy12;
	Uint8 dummy13;
	Uint8 dummy14;
	Uint8 dummy15;
	Uint8 dummy16;
	Uint8 dummy17;
	Uint8 dummy18;
};

ModbusInputsMap construct_ModbusInputsMap();
#endif

#if MB_HOLDING_REGISTERS_ENABLED
typedef struct ModbusHoldingRegistersMap ModbusHoldingRegistersMap;
struct ModbusHoldingRegistersMap {
	float32	CorrenteF1;
	float32	CorrenteF2;
	float32	CorrenteF3;
	float32	CorrenteMedia;
	float32	TensaoF1NRede;
	float32	TensaoF2NRede;
	float32	TensaoF3NRede;
	float32	TensaoFNMediaRede;
	float32	FrequenciaDaRede;
	float32	FluxoDePotenciaAtiva;
	float32	FluxoDePotenciaReativa;
	float32	FluxoDePotenciaAparente;
	float32	FatorDePotencia;
	float32	TensaoF1NMicrorrede;
	float32	TensaoF2NMicrorrede;
	float32	TensaoF3NMicrorrede;
	float32	TensaoFNMediaMicrorrede;
	float32	FrequenciaDaMicrorrede;
	int32	EnergiaAtivaImportada;
	int32	EnergiaAtivaExportada;
	int32	ModoDeConexao;

};

ModbusHoldingRegistersMap construct_ModbusHoldingRegistersMap();
#endif

#if MB_INPUT_REGISTERS_ENABLED
typedef struct ModbusInputRegistersMap ModbusInputRegistersMap;
struct ModbusInputRegistersMap {
	float32 dummy0;
	float32 dummy1;
	float32 dummy2;
	float32 dummy3;
	float32 dummy4;
};

ModbusInputRegistersMap construct_ModbusInputRegistersMap();
#endif

#endif /* MODBUSVARMAP_H_ */
