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

#ifndef MODBUS_H_
#define MODBUS_H_

// DON'T MODIFY THE CODE BELOW!

typedef enum {
	profiling_MB_TIMER_T35_WAIT = 0,
	profiling_MB_RECEIVE,
	profiling_MB_PROCESS,
	profiling_MB_TRANSMIT
} ModbusProfiling;

// Read codes
 typedef enum {
	MB_FUNC_READ_COIL = 1,
	MB_FUNC_READ_INPUT,
	MB_FUNC_READ_HOLDINGREGISTERS,
	MB_FUNC_READ_INPUTREGISTERS,
	MB_FUNC_FORCE_COIL,
	MB_FUNC_WRITE_HOLDINGREGISTER,
	MB_FUNC_FORCE_NCOILS = 15,
	MB_FUNC_WRITE_NREGISTERS = 16
} ModbusFunctionCode;

// State machine constants
typedef enum {
	MB_CREATE,
	MB_START,
	MB_TIMER_T35_WAIT,
	MB_IDLE,
	MB_RECEIVE,
	MB_PROCESS,
	MB_TRANSMIT,
	MB_DESTROY
} ModbusState;

// Error codes
typedef enum {
	MB_ERROR_ILLEGALFUNC = 1,
	MB_ERROR_ILLEGALADDR,
	MB_ERROR_ILLEGALDATA,
	MB_ERROR_SLVFAILURE,
	MB_ERROR_ACKNOWLEDGE,
	MB_ERROR_SLVBUSY,
	MB_ERROR_NEGACKNOWLEDGE,
	MB_ERROR_MEMPARITY,
	MB_ERROR_GATEWAYPATHUN
} ModbusError;

typedef enum {
	MB_READ_ADDRESS_HIGH,
	MB_READ_ADDRESS_LOW,
	MB_READ_TOTALDATA_HIGH,
	MB_READ_TOTALDATA_LOW
} ModbusContentRequestReadIndexes;


typedef enum {
	MB_WRITE_ADDRESS_HIGH,
	MB_WRITE_ADDRESS_LOW,
	MB_WRITE_VALUE_HIGH,
	MB_WRITE_VALUE_LOW
} ModbusContentRequestWriteIndexes;

typedef enum {
	MB_WRITE_N_ADDRESS_HIGH,
	MB_WRITE_N_ADDRESS_LOW,
	MB_WRITE_N_QUANTITY_HIGH,
	MB_WRITE_N_QUANTITY_LOW,
	MB_WRITE_N_BYTES,
	MB_WRITE_N_VALUES_START_HIGH,
	MB_WRITE_N_VALUES_START_LOW
} ModbusContentRequestWriteNIndexes;

// Size constants (with CRC) ==============================

#define MB_DATA_MAX_SIZE			0x270E
#define MB_DATA_MAX_REQUEST_SIZE	0x7D

#define MB_SIZE_COMMON_DATA			4 // Slave address (1 byte) + Function Code (1 byte) + CRC (2 bytes)
#define MB_SIZE_CONTENT_NORMAL		4
// Response sizes
#define MB_SIZE_RESP_READ_MINIMUM	MB_SIZE_COMMON_DATA + 1 // MB_SIZE_COMMON_DATA + Number of requested registers (1 byte)
#define MB_SIZE_RESP_WRITE			MB_SIZE_COMMON_DATA + MB_SIZE_CONTENT_NORMAL // MB_SIZE_COMMON_DATA + Data address (2 bytes) + Value writen (2 bytes)
#define MB_SIZE_RESP_WRITE_N		MB_SIZE_COMMON_DATA + MB_SIZE_CONTENT_NORMAL // MB_SIZE_COMMON_DATA + Data address (2 bytes) + Number of writen values (2 bytes)
#define MB_SIZE_RESP_EXCEPTION		MB_SIZE_COMMON_DATA + 1
// Request sizes
#define MB_SIZE_REQ_WRITE_N_MINIMUM	MB_SIZE_COMMON_DATA + 5 // Data addr (2 bytes) + Number of registers (2 bytes) + Following data (1 byte)
#define MB_SIZE_REQ_READ			MB_SIZE_COMMON_DATA + MB_SIZE_CONTENT_NORMAL
#define MB_SIZE_REQ_WRITE			MB_SIZE_COMMON_DATA + MB_SIZE_CONTENT_NORMAL

// Size constants (without CRC) ===========================

#define MB_SIZE_COMMON_DATA_WITHOUTCRC			MB_SIZE_COMMON_DATA - 2
// Response sizes
#define MB_SIZE_RESP_READ_MINIMUM_WITHOUTCRC	MB_SIZE_RESP_READ_MINIMUM - 2
#define MB_SIZE_RESP_WRITE_WITHOUTCRC			MB_SIZE_RESP_WRITE - 2
#define MB_SIZE_RESP_WRITE_N_WITHOUTCRC			MB_SIZE_RESP_WRITE_N - 2
#define MB_SIZE_RESP_EXCEPTION_WITHOUTCRC		MB_SIZE_RESP_EXCEPTION - 2
// Request sizes
#define MB_SIZE_REQ_WRITE_N_MINIMUM_WITHOUTCRC	MB_SIZE_REQ_WRITE_N_MINIMUM - 2
#define MB_SIZE_REQ_READ_WITHOUTCRC				MB_SIZE_REQ_READ - 2
#define MB_SIZE_REQ_WRITE_WITHOUTCRC			MB_SIZE_REQ_WRITE - 2

#endif /* MODBUS_H_ */
