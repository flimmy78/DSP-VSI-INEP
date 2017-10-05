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



#include "ModbusDefinitions.h"
#include "ModbusData.h"
#include "Log.h"

// Clears all data of Modbus Data
void data_clear(ModbusData *self){
	MB_DATA_RESPONSE_DEBUG();
	self->slaveAddress = 0;
	self->functionCode = 0;
	self->size = 0;
	self->contentIdx = 0;
	self->crc = 0;
}

// Return a string with the data that will be transmited
// Mostly used for the last step of process: MB_TRANSMIT (serial TX)
 Uint16 * data_getTransmitString(ModbusData *self){
	static Uint16 string[MB_BUFFER_SIZE] = {0};
	Uint16 stringIndex = 0;
	Uint16 contentIterator;

	string[stringIndex++] = self->slaveAddress;
	string[stringIndex++] = self->functionCode;
	
	// Loop throught the "general content" part of data frame
	for(contentIterator = 0; contentIterator < (self->size - MB_SIZE_COMMON_DATA); contentIterator++){
		string[stringIndex++] = (self->content[contentIterator]) & 0x00FF;
	}
	
	string[stringIndex++] = (self->crc & 0xFF00) >> 8;
	string[stringIndex++] = self->crc & 0x00FF;

	MB_DATA_RESPONSE_DEBUG();
	return string;
}

// Return a string with the data that will be transmited (but without CRC)
// Mostly used to create the CRC (get this string and the size of it and then generate the CRC)
 Uint16 * data_getTransmitStringWithoutCRC(ModbusData *self){
	static Uint16 string[MB_BUFFER_SIZE] = {0};
	Uint16 stringIndex = 0;
	Uint16 contentIterator;

	string[stringIndex++] = self->slaveAddress;
	string[stringIndex++] = self->functionCode;

	// Loop throught the "general content" part of data frame
	for(contentIterator = 0; contentIterator < (self->size - MB_SIZE_COMMON_DATA); contentIterator++){
		string[stringIndex++] = (self->content[contentIterator]);
	}

	MB_DATA_RESPONSE_DEBUG();
	return string;
}

ModbusData construct_ModbusData(){
	ModbusData modbusData;

	modbusData.slaveAddress = 0;
	modbusData.functionCode = 0;
	modbusData.contentIdx = 0;
	modbusData.crc = 0;
	modbusData.size = 0;

	modbusData.clear = data_clear;
	modbusData.getTransmitString = data_getTransmitString;
	modbusData.getTransmitStringWithoutCRC = data_getTransmitStringWithoutCRC;

	MB_DATA_RESPONSE_DEBUG();

	return modbusData;
}
