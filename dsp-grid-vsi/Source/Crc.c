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


// Cyclic Redundancy Check Encoding

#include "Crc.h"

unsigned int generateCrc(unsigned int * buf, int len, bool swap)
{
	unsigned int crc = 0xFFFF;
	unsigned int temp = 0;
	int pos = 0;
	int i = 0;

	for (pos = 0; pos < len; pos++) {
		// XOR byte into least sig. byte of crc
		crc ^= (unsigned int) buf[pos];

		// Loop over each bit
		for (i = 8; i != 0; i--) {

			// If the LSB is set
			if ((crc & 0x0001) != 0) {
				crc >>= 1; 		// Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else
				crc >>= 1;		// Just shift right
		}
	}

	// Swype bytes
	if(swap == true) {
		temp = crc;
		crc = (crc & 0xFF00) >> 8;
		crc = ( (temp & 0x00FF) << 8 ) | crc;
	}

	return crc;
}
