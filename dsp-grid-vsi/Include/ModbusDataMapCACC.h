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
	Uint8	Liga;
	Uint8	Desliga;

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
	float32	CorrenteF1Saida;
	float32	CorrenteF2Saida;
	float32	CorrenteF3Saida;
	float32	CorrenteMediaSaida;
	float32	TensaoF1F2Saida;
	float32	TensaoF2F3Saida;
	float32	TensaoF1F3Saida;
	float32	TensaoFFMediaSaida;
	float32	PotenciaAtivaTotal;
	float32	PotenciaReativaTotal;
	float32	PotenciaAparenteTotal;
	float32	FatorDePotenciaTotal;
	float32	FrequenciaCa;
	float32	TemperaturaDoInversores;
	float32	TensaoCc;
	float32	CorrenteCc;
	float32	PotenciaCc;
	int32	EnergiaAtivaImportada;
	int32	EnergiaAtivaExportada;
	int32	PotenciaMaxima;
	int32	CorrenteMaxima;
	int32	SetPointDePotenciaAtiva;
	int32	SetPointDePotenciaReativa;
	int32	OffsetDoDroop;
	int32	GanhoDoDroop;
	int32	ModoDeOperacao;
	int32	FrequenciaDeOperacao;
	int32	AmplitudeDeTensaoCa;

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
