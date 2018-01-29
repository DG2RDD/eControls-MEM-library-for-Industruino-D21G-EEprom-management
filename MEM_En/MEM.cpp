/* ------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : 03/01/2018 - Extended Read and write to I2C EEPROM functions - Source code                                          Version 1.00   *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * Functions in this library                                                                                                                 *
 *        M_INIEEP - I2C EEPROM memory startup function                                                                           20/10/2017 *
 *        M_FLTSET - Float I2C EEPROM memory write function                                                                       03/01/2018 *
 *        M_INTSET - Integer I2C EEPROM memory write function                                                                     03/01/2018 *
 *        M_UINSET - Unsigned Integer I2C EEPROM memory write function                                                            03/01/2018 *
 *        M_FLTGET - Float I2C EEPROM memory read function                                                                        03/01/2018 *
 *        M_INTGET - Integer I2C EEPROM memory read function                                                                      03/01/2018 *
 *        M_UINGET - Unsigned Integer I2C EEPROM memory read function                                                             03/01/2018 *
 *        M_FLTUPD - Float I2C EEPROM memory update function                                                                      03/01/2018 *
 *        M_INTUPD - Integer I2C EEPROM memory update function                                                                    03/01/2018 *
 *        M_UINUPD - Unsigned Integer I2C EEPROM memory update function                                                           03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R , Licensed under the Apache License, Version 2.0 (the "License");                                                          *
 * You may not use this file except in compliance with the License. You may obtain a copy of the License at :                                *
 *                                        http://www.apache.org/licenses/LICENSE-2.0                                                         *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,     *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions  *
 * and limitations under the License.                                                                                                        *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/

#include "Arduino.h"
#include "MEM.h"
I2C_eeprom E50(0x50, 255);
I2C_eeprom E51(0x51, 255);
I2C_eeprom E52(0x52, 255);
I2C_eeprom E53(0x53, 255);

MEM::MEM() {}

void MEM::M_INIEEP() {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INIEEP - I2C EEPROM memory startup function                                                                           20/10/2017 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 20/10/2017 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
E50.begin();
E51.begin();
E52.begin();
E53.begin();
return; }

void MEM::M_FLTSET(float VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTSET - Float I2C EEPROM memory write function                                                                       03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTSET(float VAL[], int RNG, int AEP)                                                                                            *
 *                VAL : Float value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1)                                     *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to write in I2C EEPROM (this byte ant the 3 next bytes are written)          *
 *                         0- 256 : bytes 0 to 256 of memory E50 are used                                                                    *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are used                                                                    *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are used                                                                    *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are used                                                                    *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_FLT { float FLT[1]; byte TAB[4]; };
union U_FLT UST;
UST.FLT[0] = VAL[RNG];
switch (round(AEP / 1000)) {
case 0 :
	E50.writeByte(AEP, UST.TAB[0]); delay(1);
	E50.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	E50.writeByte(AEP + 2, UST.TAB[2]); delay(1);
	E50.writeByte(AEP + 3, UST.TAB[3]); delay(1);
	break;
case 1 :
	E51.writeByte(AEP, UST.TAB[0]); delay(1);
	E51.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	E51.writeByte(AEP + 2, UST.TAB[2]); delay(1);
	E51.writeByte(AEP + 3, UST.TAB[3]); delay(1);
	break;
case 2 :
	E52.writeByte(AEP, UST.TAB[0]); delay(1);
	E52.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	E52.writeByte(AEP + 2, UST.TAB[2]); delay(1);
	E52.writeByte(AEP + 3, UST.TAB[3]); delay(1);
	break;
case 3 :
	E53.writeByte(AEP, UST.TAB[0]); delay(1);
	E53.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	E53.writeByte(AEP + 2, UST.TAB[2]); delay(1);
	E53.writeByte(AEP + 3, UST.TAB[3]); delay(1);
	break; }
return; }

void MEM::M_INTSET(int VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTSET - Integer I2C EEPROM memory write function                                                                     03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTSET(int VAL[], int RNG, int AEP)                                                                                              *
 *                VAL : Signed integer value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1, value -32767 to +32767)    *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to write in I2C EEPROM (this byte ant the next byte are written)             *
 *                         0- 256 : bytes 0 to 256 of memory E50 are used                                                                    *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are used                                                                    *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are used                                                                    *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are used                                                                    *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_INT { int INT[1]; byte TAB[2]; };
union U_INT UST;
UST.INT[0] = max( min(VAL[RNG], 32767), -32767);
switch (round(AEP / 1000)) {
case 0 :
	E50.writeByte(AEP, UST.TAB[0]); delay(1);
	E50.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break;
case 1 :
	E51.writeByte(AEP, UST.TAB[0]); delay(1);
	E51.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break;
case 2 :
	E52.writeByte(AEP, UST.TAB[0]); delay(1);
	E52.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break;
case 3 :
	E53.writeByte(AEP, UST.TAB[0]); delay(1);
	E53.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break; }
return; }

void MEM::M_UINSET(unsigned int VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINSET - Unsigned Integer I2C EEPROM memory write function                                                            03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINSET(unsigned int VAL[], int RNG, int AEP)                                                                                     *
 *                VAL : Unsigned integer value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1, value 0 to 65536)        *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to write in I2C EEPROM (this byte ant the next byte are written)             *
 *                         0- 256 : bytes 0 to 256 of memory E50 are used                                                                    *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are used                                                                    *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are used                                                                    *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are used                                                                    *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_INT {unsigned int INT[1]; byte TAB[2]; };
union U_INT UST;
UST.INT[0] = max( min(VAL[RNG], 65536), 0 );
switch (round(AEP / 1000)) {
case 0 :
	E50.writeByte(AEP, UST.TAB[0]); delay(1);
	E50.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break;
case 1 :
	E51.writeByte(AEP, UST.TAB[0]); delay(1);
	E51.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break;
case 2 :
	E52.writeByte(AEP, UST.TAB[0]); delay(1);
	E52.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break;
case 3 :
	E53.writeByte(AEP, UST.TAB[0]); delay(1);
	E53.writeByte(AEP + 1, UST.TAB[1]); delay(1);
	break; }
return; }

void MEM::M_FLTGET(float VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTGET - Float I2C EEPROM memory read function                                                                        03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTGET(float VAL[], int RNG, int AEP)                                                                                            *
 *                VAL : Float value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1)                                     *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to read in I2C EEPROM (this byte ant the 3 next bytes are read)              *
 *                         0- 256 : bytes 0 to 256 of memory E50 are read                                                                    *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are read                                                                    *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are read                                                                    *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are read                                                                    *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_FLT { float FLT[1]; byte TAB[4]; };
union U_FLT UGT;
switch (round(AEP / 1000)) {
case 0 :
	UGT.TAB[0] = E50.readByte(AEP);
	UGT.TAB[1] = E50.readByte(AEP + 1);
	UGT.TAB[2] = E50.readByte(AEP + 2);
	UGT.TAB[3] = E50.readByte(AEP + 3);
	break;
case 1 :
	UGT.TAB[0] = E51.readByte(AEP);
	UGT.TAB[1] = E51.readByte(AEP + 1);
	UGT.TAB[2] = E51.readByte(AEP + 2);
	UGT.TAB[3] = E51.readByte(AEP + 3);
	break;
case 2 :
	UGT.TAB[0] = E52.readByte(AEP);
	UGT.TAB[1] = E52.readByte(AEP + 1);
	UGT.TAB[2] = E52.readByte(AEP + 2);
	UGT.TAB[3] = E52.readByte(AEP + 3);
	break;
case 3 :
	UGT.TAB[0] = E53.readByte(AEP);
	UGT.TAB[1] = E53.readByte(AEP + 1);
	UGT.TAB[2] = E53.readByte(AEP + 2);
	UGT.TAB[3] = E53.readByte(AEP + 3);
	break; }
VAL[RNG] = UGT.FLT[0];
return; }

void MEM::M_INTGET(int VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTGET - Integer I2C EEPROM memory read function                                                                      03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTGET(int VAL[], int RNG, int AEP)                                                                                              *
 *                VAL : Signed integer value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1, value -32767 to +32767)    *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to read in I2C EEPROM (this byte ant the next byte are read)                 *
 *                         0- 256 : bytes 0 to 256 of memory E50 are read                                                                    *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are read                                                                    *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are read                                                                    *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are read                                                                    *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_INT { int INT[1]; byte TAB[2]; };
union U_INT UGT;
switch (round(AEP / 1000)) {
case 0 :
	UGT.TAB[0] = E50.readByte(AEP);
	UGT.TAB[1] = E50.readByte(AEP + 1);
	break;
case 1 :
	UGT.TAB[0] = E51.readByte(AEP);
	UGT.TAB[1] = E51.readByte(AEP + 1);
	break;
case 2 :
	UGT.TAB[0] = E52.readByte(AEP);
	UGT.TAB[1] = E52.readByte(AEP + 1);
	break;
case 3 :
	UGT.TAB[0] = E53.readByte(AEP);
	UGT.TAB[1] = E53.readByte(AEP + 1);
	break; }
	if (UGT.INT[0] <= 32768) { VAL[RNG] = UGT.INT[0]; } else { VAL[RNG] = (UGT.INT[0] - 65536);}
return; }

void MEM::M_UINGET(unsigned int VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINGET - Unsigned Integer I2C EEPROM memory read function                                                             03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINGET(unsigned int VAL[], int RNG, int AEP)                                                                                     *
 *                VAL : Unsigned integer value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1, value 0 to 65536)        *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to read in I2C EEPROM (this byte ant the next byte are read)                 *
 *                         0- 256 : bytes 0 to 256 of memory E50 are read                                                                    *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are read                                                                    *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are read                                                                    *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are read                                                                    *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_INT {unsigned int INT[1]; byte TAB[2]; };
union U_INT UGT;
switch (round(AEP / 1000)) {
case 0 :
	UGT.TAB[0] = E50.readByte(AEP);
	UGT.TAB[1] = E50.readByte(AEP + 1);
	break;
case 1 :
	UGT.TAB[0] = E51.readByte(AEP);
	UGT.TAB[1] = E51.readByte(AEP + 1);
	break;
case 2 :
	UGT.TAB[0] = E52.readByte(AEP);
	UGT.TAB[1] = E52.readByte(AEP + 1);
	break;
case 3 :
	UGT.TAB[0] = E53.readByte(AEP);
	UGT.TAB[1] = E53.readByte(AEP + 1);
	break; }
VAL[RNG] = UGT.INT[0];
return; }

void MEM::M_FLTUPD(float VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTUPD - Float I2C EEPROM memory update function                                                                      03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTUPD(float VAL[], int RNG, int AEP)                                                                                            *
 *                VAL : Float value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1)                                     *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to update in I2C EEPROM (this byte ant the 3 next bytes are updated)         *
 *                         0- 256 : bytes 0 to 256 of memory E50 are updated                                                                 *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are updated                                                                 *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are updated                                                                 *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are updated                                                                 *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_FLT { float FLT[1]; byte TAB[4]; };
union U_FLT UMT;
switch (round(AEP / 1000)) {
case 0 :
	UMT.TAB[0] = E50.readByte(AEP);
	UMT.TAB[1] = E50.readByte(AEP + 1);
	UMT.TAB[2] = E50.readByte(AEP + 2);
	UMT.TAB[3] = E50.readByte(AEP + 3);
	if (UMT.FLT[0] != VAL[RNG]) {
		UMT.FLT[0] = VAL[RNG];
		E50.writeByte(AEP, UMT.TAB[0]); delay(1);
		E50.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
		E50.writeByte(AEP + 2, UMT.TAB[2]); delay(1);
		E50.writeByte(AEP + 3, UMT.TAB[3]); delay(1);
	}
	break;
case 1 :
	UMT.TAB[0] = E51.readByte(AEP);
	UMT.TAB[1] = E51.readByte(AEP + 1);
	UMT.TAB[2] = E51.readByte(AEP + 2);
	UMT.TAB[3] = E51.readByte(AEP + 3);
	if (UMT.FLT[0] != VAL[RNG]) {
		UMT.FLT[0] = VAL[RNG];
		E51.writeByte(AEP, UMT.TAB[0]); delay(1);
		E51.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
		E51.writeByte(AEP + 2, UMT.TAB[2]); delay(1);
		E51.writeByte(AEP + 3, UMT.TAB[3]); delay(1);
	}
case 2 :
	UMT.TAB[0] = E52.readByte(AEP);
	UMT.TAB[1] = E52.readByte(AEP + 1);
	UMT.TAB[2] = E52.readByte(AEP + 2);
	UMT.TAB[3] = E52.readByte(AEP + 3);
	if (UMT.FLT[0] != VAL[RNG]) {
		UMT.FLT[0] = VAL[RNG];
		E52.writeByte(AEP, UMT.TAB[0]); delay(1);
		E52.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
		E52.writeByte(AEP + 2, UMT.TAB[2]); delay(1);
		E52.writeByte(AEP + 3, UMT.TAB[3]); delay(1);
	}
	break;
case 3 :
	UMT.TAB[0] = E53.readByte(AEP);
	UMT.TAB[1] = E53.readByte(AEP + 1);
	UMT.TAB[2] = E53.readByte(AEP + 2);
	UMT.TAB[3] = E53.readByte(AEP + 3);
	if (UMT.FLT[0] != VAL[RNG]) {
		UMT.FLT[0] = VAL[RNG];
		E53.writeByte(AEP, UMT.TAB[0]); delay(1);
		E53.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
		E53.writeByte(AEP + 2, UMT.TAB[2]); delay(1);
		E53.writeByte(AEP + 3, UMT.TAB[3]); delay(1);
	}
	break; }
return; }

void MEM::M_INTUPD(int VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTUPD - Integer I2C EEPROM memory update function                                                                    03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTUPD(int VAL[], int RNG, int AEP)                                                                                              *
 *                VAL : Signed integer value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1, value -32767 to +32767)    *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to update in I2C EEPROM (this byte ant the next byte are updated)            *
 *                         0- 256 : bytes 0 to 256 of memory E50 are updated                                                                 *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are updated                                                                 *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are updated                                                                 *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are updated                                                                 *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_INT {int INT[1]; byte TAB[4]; };
union U_INT UMT;
int TMP;
switch (round(AEP / 1000)) {
case 0 :
	UMT.TAB[0] = E50.readByte(AEP);
	UMT.TAB[1] = E50.readByte(AEP + 1);
	if (UMT.INT[0] <= 32768) { TMP = UMT.INT[0]; } else { TMP = (UMT.INT[0] - 65536);}
	if (TMP != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E50.writeByte(AEP, UMT.TAB[0]); delay(1);
		E50.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
	break;
case 1 :
	UMT.TAB[0] = E51.readByte(AEP);
	UMT.TAB[1] = E51.readByte(AEP + 1);
	if (UMT.INT[0] <= 32768) { TMP = UMT.INT[0]; } else { TMP = (UMT.INT[0] - 65536);}
	if (TMP != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E51.writeByte(AEP, UMT.TAB[0]); delay(1);
		E51.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
case 2 :
	UMT.TAB[0] = E52.readByte(AEP);
	UMT.TAB[1] = E52.readByte(AEP + 1);
	if (UMT.INT[0] <= 32768) { TMP = UMT.INT[0]; } else { TMP = (UMT.INT[0] - 65536);}
	if (TMP != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E52.writeByte(AEP, UMT.TAB[0]); delay(1);
		E52.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
	break;
case 3 :
	UMT.TAB[0] = E53.readByte(AEP);
	UMT.TAB[1] = E53.readByte(AEP + 1);
	if (UMT.INT[0] <= 32768) { TMP = UMT.INT[0]; } else { TMP = (UMT.INT[0] - 65536);}
	if (TMP != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E53.writeByte(AEP, UMT.TAB[0]); delay(1);
		E53.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
	break; }
return; }

void MEM::M_UINUPD(unsigned int VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINUPD - Unsigned Integer I2C EEPROM memory update function                                                           03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTUPD(unsigned int VAL[], int RNG, int AEP)                                                                                     *
 *                VAL : Unsigned integer value to keep in I2C EEPROM memory (Has to be an array, minimum size of 1, value 0 to 65536)        *
 *                RNG : Positive integer - Rank of the memorized value in array VAL[]                                                        *
 *                AEP : Positive integer - Number of first byte to update in I2C EEPROM (this byte ant the next byte are updated)            *
 *                         0- 256 : bytes 0 to 256 of memory E50 are updated                                                                 *
 *                      1000-1256 : bytes 0 to 256 of memory E51 are updated                                                                 *
 *                      2000-2256 : bytes 0 to 256 of memory E52 are updated                                                                 *
 *                      3000-3256 : bytes 0 to 256 of memory E53 are updated                                                                 *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Tested platforms : Industruino D21G                                                                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Benchmark Tested with Industruino D21G                                                                            *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
union U_UIN {unsigned int INT[1]; byte TAB[4]; };
union U_UIN UMT;
switch (round(AEP / 1000)) {
case 0 :
	UMT.TAB[0] = E50.readByte(AEP);
	UMT.TAB[1] = E50.readByte(AEP + 1);
	if (UMT.INT[0] != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E50.writeByte(AEP, UMT.TAB[0]); delay(1);
		E50.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
	break;
case 1 :
	UMT.TAB[0] = E51.readByte(AEP);
	UMT.TAB[1] = E51.readByte(AEP + 1);
	if (UMT.INT[0] != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E51.writeByte(AEP, UMT.TAB[0]); delay(1);
		E51.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
case 2 :
	UMT.TAB[0] = E52.readByte(AEP);
	UMT.TAB[1] = E52.readByte(AEP + 1);
	if (UMT.INT[0] != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E52.writeByte(AEP, UMT.TAB[0]); delay(1);
		E52.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
	break;
case 3 :
	UMT.TAB[0] = E53.readByte(AEP);
	UMT.TAB[1] = E53.readByte(AEP + 1);
	if (UMT.INT[0] != VAL[RNG]) {
		UMT.INT[0] = VAL[RNG];
		E53.writeByte(AEP, UMT.TAB[0]); delay(1);
		E53.writeByte(AEP + 1, UMT.TAB[1]); delay(1);
	}
	break; }
return; }