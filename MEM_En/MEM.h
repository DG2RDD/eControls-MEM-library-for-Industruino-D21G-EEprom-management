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

 /**
 * @ file	MEM.h
 * @brief	Extended I2C EEPROM functions.
 * @author	SE2R, Didier DORGUIN
 * @date	01/03/2018
 * @version	1.00
 */
 
#ifndef MEM_h
#define MEM_h
#include "Arduino.h"
#include <I2C_eeprom.h>

class MEM
{
public :
	MEM();
	void M_INIEEP();
	void M_FLTSET(float VAL[], int RNG, int AEP);
	void M_INTSET(int VAL[], int RNG, int AEP);
	void M_UINSET(unsigned int VAL[], int RNG, int AEP);
	void M_FLTGET(float VAL[], int RNG, int AEP);
	void M_INTGET(int VAL[], int RNG, int AEP);
	void M_UINGET(unsigned int VAL[], int RNG, int AEP);
	void M_FLTUPD(float VAL[], int RNG, int AEP);
	void M_INTUPD(int VAL[], int RNG, int AEP);
	void M_UINUPD(unsigned int VAL[], int RNG, int AEP);
};
#endif