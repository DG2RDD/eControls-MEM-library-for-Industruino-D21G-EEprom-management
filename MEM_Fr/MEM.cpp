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

#include "Arduino.h"
#include "MEM.h"
I2C_eeprom E50(0x50, 255);
I2C_eeprom E51(0x51, 255);
I2C_eeprom E52(0x52, 255);
I2C_eeprom E53(0x53, 255);

MEM::MEM() {}

void MEM::M_INIEEP() {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INIEEP - Fonction dde démarrage de la mémoire EEPROM I2C                                                              20/10/2017 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 20/10/2017 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
E50.begin();
E51.begin();
E52.begin();
E53.begin();
return; }

void MEM::M_FLTSET(float VAL[], int RNG, int AEP) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTSET - Fonction d'écriture d'un Float en mémoire                                                                    03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTSET(float VAL[], int RNG, int AEP)                                                                                            *
 *                VAL : Float, Valeur à mémoriser (Nécessairement un tableau de taille au moins 1)                                           *
 *                RNG : Entier positif - Rang de la valeur à mémoriser dans le tableau VAL[]                                                 *
 *                AEP : Entier positif - Adresse du premier octet de mémorisation en EEPROM (cet octet et les 3 suivants sont écrits)        *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_INTSET - Fonction d'écriture d'un Integer en mémoire                                                                  03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTSET(int VAL[], int RNG, int AEP)                                                                                              *
 *                VAL : Entier signé, Valeur à mémoriser (Nécessairement un tableau de taille au moins 1, valeur -32767 à +32767)            *
 *                RNG : Entier positif - Rang de la valeur à mémoriser dans le tableau VAL[]                                                 *
 *                AEP : Entier positif - Adresse du premier octet d'écriture en EEPROM (cet octet et le suivant sont écrits)                 *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_UINSET - Fonction d'écriture d'un Unsigned Integer en mémoire                                                         03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINSET(unsigned int VAL[], int RNG, int AEP)                                                                                     *
 *                VAL : Entier non signé, Valeur à mémoriser (Nécessairement un tableau de taille au moins 1, valeur 0 à 65536)              *
 *                RNG : Entier positif - Rang de la valeur à mémoriser dans le tableau VAL[]                                                 *
 *                AEP : Entier positif - Adresse du premier octet d'écriture en EEPROM (cet octet et le suivant sont écrits)                 *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_FLTGET - Fonction de lecture d'un Float en mémoire                                                                    03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTGET(float VAL[], int RNG, int AEP)                                                                                            *
 *                VAL : Float, Valeur mémorisée à relire (Nécessairement un tableau de taille au moins 1)                                    *
 *                RNG : Entier positif - Rang de la valeur à mémoriser dans le tableau VAL[]                                                 *
 *                AEP : Entier positif - Adresse du premier octet d'écriture en EEPROM (cet octet et les 3 suivants sont lus)                *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_INTGET - Fonction de lecture d'un Integer en mémoire                                                                  03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTGET(int VAL[], int RNG, int AEP)                                                                                              *
 *                VAL : entier, Valeur mémorisée à relire (Nécessairement un tableau de taille au moins 1)                                   *
 *                RNG : Entier - Rang de la valeur mémorisée dans le tableau VAL[]                                                           *
 *                AEP : Entier - Adresse du premier octet de lecture en EEPROM (cet octet et le suivant sont lus)                            *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_UINGET - Fonction de lecture d'un Integer en mémoire                                                                  03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_UINGET(unsigned int VAL[], int RNG, int AEP)                                                                                     *
 *                VAL : entier non signé, Valeur mémorisée à relire (Nécessairement un tableau de taille au moins 1)                         *
 *                RNG : Entier - Rang de la valeur mémorisée dans le tableau VAL[]                                                           *
 *                AEP : Entier - Adresse du premier octet de lecture en EEPROM (cet octet et le suivant sont lus)                            *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_FLTUPD - Fonction de maintien à jour de la valeur d'un Float en mémoire                                               03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_FLTUPD(float VAL[], int RNG, int AEP)                                                                                            *
 *                VAL : Float, Valeur à maintenir à jour en EEPROM (Nécessairement un tableau de taille au moins 1)                          *
 *                RNG : Entier - Rang de la valeur à maintenir à jour dans le tableau VAL[]                                                  *
 *                AEP : Entier - Adresse du premier octet de mémorisation en EEPROM (cet octet et les 3 suivants sont écrits)                *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_INTUPD - Fonction de maintien à jour de la valeur d'un Integer en mémoire                                             03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTUPD(int VAL[], int RNG, int AEP)                                                                                              *
 *                VAL : Entier, Valeur à maintenir à jour en EEPROM (Nécessairement un tableau de taille au moins 1)                         *
 *                RNG : Entier - Rang de la valeur à maintenir à jour dans le tableau VAL[]                                                  *
 *                AEP : Entier - Adresse du premier octet de mémorisation en EEPROM (cet octet et les 3 suivants sont écrits)                *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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
 *        M_UINUPD - Fonction de maintien à jour de la valeur d'un Integer en mémoire                                             03/01/2018 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        M_INTUPD(unsigned int VAL[], int RNG, int AEP)                                                                                     *
 *                VAL : Entier non signé, Valeur à maintenir à jour en EEPROM (Nécessairement un tableau de taille au moins 1)               *
 *                RNG : Entier - Rang de la valeur à maintenir à jour dans le tableau VAL[]                                                  *
 *                AEP : Entier - Adresse du premier octet de mémorisation en EEPROM (cet octet et les 3 suivants sont écrits)                *
 *                         0- 256 : Les octets 0 à 256 de la mémoire E50 sont utilisés                                                       *
 *                      1000-1256 : Les octets 0 à 256 de la mémoire E51 sont utilisés                                                       *
 *                      2000-2256 : Les octets 0 à 256 de la mémoire E52 sont utilisés                                                       *
 *                      3000-3256 : Les octets 0 à 256 de la mémoire E53 sont utilisés                                                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * 03/01/2018 : SE2R, DD : Testée et validée sur banc Industruino D21G                                                                       *
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