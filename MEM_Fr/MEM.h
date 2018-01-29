/* ------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : 03/01/2018 - Fonctions de mémorisation et relecture de mémoires EEPROM I2C - Fichier de code source                 Version 1.00   *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * Fonction de cette bibliothèque                                                                                                            *
 *        M_INIEEP - Fonction dde démarrage de la mémoire EEPROM I2C                                                              20/10/2017 *
 *        M_FLTSET - Fonction d'écriture d'un Float en mémoire                                                                    03/01/2018 *
 *        M_INTSET - Fonction d'écriture d'un Integer en mémoire                                                                  03/01/2018 *
 *        M_UINSET - Fonction d'écriture d'un unsigned Integer en mémoire                                                         03/01/2018 *
 *        M_FLTGET - Fonction de lecture d'un Float en mémoire                                                                    03/01/2018 *
 *        M_INTGET - Fonction de lecture d'un Integer en mémoire                                                                  03/01/2018 *
 *        M_UINGET - Fonction de lecture d'un Unsigned Integer en mémoire                                                         03/01/2018 *
 *        M_FLTUPD - Fonction de maintien à jour de la valeur d'un Float en mémoire                                               03/01/2018 *
 *        M_INTUPD - Fonction de maintien à jour de la valeur d'un Integer en mémoire                                             03/01/2018 *
 *        M_UINUPD - Fonction de maintien à jour de la valeur d'un unsigned Integer en mémoire                                    03/01/2018 *
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
 * @brief	Bibliothèque de fonctions de gestion de la sauvegarde EEPROM I2C.
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