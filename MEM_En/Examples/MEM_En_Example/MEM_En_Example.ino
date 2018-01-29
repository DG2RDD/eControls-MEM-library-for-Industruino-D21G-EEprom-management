/* ------------------------------------------------------------------------------------------------------------------------------------------*
 * DG2R : 03/01/2018 - MEM extended I2C EEPROM library example                                                              Industruino D21G *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * Used library MEM_En                                                                                                            03/01/2018 *
 * Used library / Bibliothèque utilisée UC1701 - Copyright (c) 2014 Rustem Iskuzhin                                                     2014 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/

// Libraries inclusion ----------------------------------------------------------------------------------------------------------------------*
#include <Wire.h>         // Library  - Comm ports control
#include <Indio.h>        // Library  - Industruino I/O control
#include <UC1701.h>       // Library  - Screen basic library
static UC1701 lcd;        // Library  - Screen basic library constructor
#include <MEM.h>          // Library  - SE2R EEPROM I2C control library
static MEM MEM;           // Library  - SE2R I2C EEPROM library constructor

// Process variables ------------------------------------------------------------------------------------------------------------------------*
int VCM_MINT[2];          // EEPROM   - [00] Read  int type value
                          //            [01] Write int type value
unsigned int VCM_MUIN[2]; // EEPROM   - [00] Read  unsigned int type value
                          //            [01] Write unsigned int type value
float VCM_MFLT[2];        // EEPROM   - [00] Read  float type value
                          //            [01] Write float type value

// Screen variables -------------------------------------------------------------------------------------------------------------------------*
boolean FCO_PRUP[5];      // LCDScreen- "Up" button pressed
boolean FCO_PREN[5];      // LCDScreen- "Enter" button pressed
boolean FCO_PRDN[5];      // LCDScreen- "Down" button pressed
int VNT_MENU[3];          // LCDScreen- Total number of menu screens
                          //            [01] Number of the next destination screen
                          //            [02] Number of the last destination screen
int VNC_MENU[10];         // LCDScreen- Table of menu adresses
int VNC_PRUP[10];         // LCDScreen- Table of destination menu adresses for "Up"
int VNC_PREN[10];         // LCDScreen- Table of destination menu adresses for "Enter"
int VNC_PRDN[10];         // LCDScreen- Table of destination menu adresses for "Down"
float VTT_SCRN[10];       // LCDScreen- Table of timers

float VTM_MINT[10];       // G_MODV1E - [00] Memory of value to act on
                          //            [01] Minimum command value
                          //            [02] Maximum command value
                          //            [03] "Up" and "Down" Increment step
                          //            [04] Temporary value before "Enter" pressed
                          //            [05] CPU cycle time in ms
                          //            [06] Memory of "Millis" of last cycle
                          //            [07] "Up" and "Down" pressed timer
                          //            [08] Delay (ms) before fast increment/decrement
                          //            [09] Fast increment/decrement confirmed
float VTM_MUIN[10];       // G_MODV1E - [..] Parameter table for action on VCX_MUIN[0]
float VTM_MFLT[10];       // G_MODV1F - [00] Memory of value to act on VCM_MFLT[1]
                          //            [01] Minimum command value
                          //            [02] Maximum command value
                          //            [03] "Up" and "Down" Increment step
                          //            [04] Temporary value before "Enter" pressed
                          //            [05] CPU cycle time in ms
                          //            [06] Memory of "Millis" of last cycle
                          //            [07] "Up" and "Down" pressed timer
                          //            [08] Delay (ms) before fast increment/decrement
                          //            [09] Fast increment/decrement confirmed

int VNX_MN02[12];         // G_CHOIX8 - [00] Destination screen adress of line 0 in menu screen
                          //            [01] Destination screen adress of line 1 in menu screen
                          //            [...]
                          //            [07] Destination screen adress of line 7 in menu screen
                          //            [08] Minimum line number in the menu screen
                          //            [09] Maximum line number in the menu screen
                          //            [10] Current pointed line number in the menu screen
                          //            [11] First screen print completed = true

float VCX_MINT[1];        // G_MODV1E - [00] Float intermediary screen command value for VCM_MINT[1]
float VCX_MUIN[1];        // G_MODV1E - [00] Float intermediary screen command value for VCM_MUIN[1]

void setup() {            // Main initialization --------------------------------------------------------------------------------------------*
VTT_SCRN[1] = 30;         // G_TOUCHx - Backlight inactivity delay
VTT_SCRN[2] = 60;         // G_TOUCHx - Inactivity delay to return to main screen
VTT_SCRN[3] = 20;         // G_TOUCHx - Rebound delay for "Enter"
VTT_SCRN[4] = 15;         // G_TOUCHx - Rebound delay for "Up" and "Down"
VNT_MENU[0] = 5;          // G_NAVIGM - Size of index and destination tables
VNT_MENU[1] = 1;          // G_NAVIGM - Destinations pointer initialization
VNC_MENU[0] = 1;          // G_NAVIGM - Screen adresses table
VNC_MENU[1] = 1;
VNC_MENU[2] = 2;
VNC_MENU[3] = 3;
VNC_MENU[4] = 4;
VNC_MENU[5] = 5;
                          // G_NAVIGM - Buttons destinations adresses table
VNC_PRUP[1] =    1; VNC_PREN[1] =    2; VNC_PRDN[1] =    2;
VNC_PRUP[2] =    2; VNC_PREN[2] =    2; VNC_PRDN[2] =    2;
VNC_PRUP[3] =    3; VNC_PREN[3] =    2; VNC_PRDN[3] =    3;
VNC_PRUP[4] =    4; VNC_PREN[4] =    2; VNC_PRDN[4] =    4;
VNC_PRUP[5] =    5; VNC_PREN[5] =    2; VNC_PRDN[5] =    5;

                          // G_MODV1E - Screen value change parameters
VNX_MN02[10] = 1;
VTM_MINT[1] = -999; VTM_MINT[2] = 1999; VTM_MINT[3] =   1; VTM_MINT[8] = 100;
VTM_MUIN[1] =    0; VTM_MUIN[2] =  999; VTM_MUIN[3] =   1; VTM_MUIN[8] = 100;
VTM_MFLT[1] = -999; VTM_MFLT[2] =  999; VTM_MFLT[3] = 0.1; VTM_MFLT[8] = 100;

pinMode(23, INPUT);     // LCDScreen- 1286 et D21G specific I/O - Down arrow button
pinMode(24, INPUT);     // LCDScreen- 1286 et D21G specific I/O - Enter button
pinMode(25, INPUT);     // LCDScreen- 1286 et D21G specific I/O - Up arrow button
pinMode(26, OUTPUT);    // LCDScreen- 1286 et D21G specific I/O - Backlight output
lcd.begin();            // LCDScreen- Screen initialization
lcd.clear();            // LCDScreen- Initial clear screen

MEM.M_INIEEP();
MEM.M_INTGET(VCM_MINT, 0, 0);
MEM.M_UINGET(VCM_MUIN, 0, 2);
MEM.M_FLTGET(VCM_MFLT, 0, 4);
lcd.setCursor(0, 0); lcd.print("Current memo values --");
lcd.setCursor(0, 1); lcd.print("Int   memo : "); lcd.setCursor(78, 1); lcd.print(VCM_MINT[0]);
lcd.setCursor(0, 2); lcd.print("U.Int memo : "); lcd.setCursor(78, 2); lcd.print(VCM_MUIN[0]);
lcd.setCursor(0, 3); lcd.print("Float memo : "); lcd.setCursor(78, 3); lcd.print(VCM_MFLT[0]);
lcd.setCursor(0, 4); lcd.print("End ------------------");
VCM_MINT[1] = VCM_MINT[0]; VCX_MINT[1] = float(VCM_MINT[0]);
VCM_MUIN[1] = VCM_MUIN[0]; VCX_MUIN[1] = float(VCM_MUIN[0]);
VCM_MFLT[1] = VCM_MFLT[0];
delay(2000);
}
void loop() {        // Main execution loop -------------------------------------------------------------------------------------------------*

if (VNT_MENU[2] != VNC_MENU[0]) { lcd.clear(); }
VNT_MENU[2] = VNC_MENU[0];
G_TOUCH3(VNC_MENU, VTT_SCRN, FCO_PRUP, FCO_PREN, FCO_PRDN, VNT_MENU);

switch(VNC_MENU[0]) { 
case 1 : 
  lcd.setCursor(0, 0); lcd.print("   www.eControls.fr  ");
  lcd.setCursor(0, 1); lcd.print("    DG2R Softwares   ");
  lcd.setCursor(0, 2); lcd.print("  Industruino  D21G  ");
  lcd.setCursor(0, 6); lcd.print(" MEM library Example ");
  lcd.setCursor(0, 7); lcd.print("V.1.00     29/01/2018");
  break;
case 2 :
  VNX_MN02[0] = 0;
  VNX_MN02[1] = 1;
  VNX_MN02[2] = 3;
  VNX_MN02[3] = 4;
  VNX_MN02[4] = 5;
  VNX_MN02[5] = 0;
  VNX_MN02[6] = 0;
  VNX_MN02[7] = 0;
  VNX_MN02[8] = 1;
  VNX_MN02[9] = 4;
  G_CHOIX8(VNC_MENU, 2, FCO_PRUP, FCO_PREN, FCO_PRDN, VNX_MN02, VNT_MENU);
  lcd.setCursor(2, 0); lcd.print("-     Main Menu     -");
  lcd.setCursor(6, 1); lcd.print( "Back to home screen");
  lcd.setCursor(6, 2); lcd.print( "M_INTxxx example");
  lcd.setCursor(6, 3); lcd.print( "M_UINxxx example");
  lcd.setCursor(6, 4); lcd.print( "M_FLTxxx example");
  lcd.setCursor(0, 7); lcd.print("- Select then Enter -");
  VTM_MINT[0] = VCM_MINT[1];
  VTM_MUIN[0] = VCM_MUIN[1];
  VTM_MFLT[0] = VCM_MFLT[1];
  MEM.M_INTUPD(VCM_MINT, 1, 0);
  MEM.M_UINUPD(VCM_MUIN, 1, 2);
  MEM.M_FLTUPD(VCM_MFLT, 1, 4);
  break;
case 3 :
  lcd.setCursor(0, 0); lcd.print("-      Integer      -");
  lcd.setCursor(0, 1); lcd.print("- Change memo value -");
  G_MOSV1E(FCO_PRUP, FCO_PREN, FCO_PRDN, VCX_MINT, 0, VTM_MINT, true);
  lcd.setCursor(86, 4); lcd.print(".    ");
  lcd.setCursor(86, 5); lcd.print(".    ");
  VCM_MINT[1] = int(VCX_MINT[0]);
  break;
case 4 :
  lcd.setCursor(0, 0); lcd.print("-   Unsigned Int.   -");
  lcd.setCursor(0, 1); lcd.print("- Change memo value -");
  G_MOSV1E(FCO_PRUP, FCO_PREN, FCO_PRDN, VCX_MUIN, 0, VTM_MUIN, true);
  lcd.setCursor(86, 4); lcd.print(".    ");
  lcd.setCursor(86, 5); lcd.print(".    ");
  VCM_MUIN[1] = int(VCX_MUIN[0]);
  break;
case 5 :
  lcd.setCursor(0, 0); lcd.print("-       Float       -");
  lcd.setCursor(0, 1); lcd.print("- Change memo value -");
  G_MOSV1F(FCO_PRUP, FCO_PREN, FCO_PRDN, VCM_MFLT, 1, VTM_MFLT, true);
  lcd.setCursor(86, 4); lcd.print(".    ");
  lcd.setCursor(86, 5); lcd.print(".    ");
  break;
  }
G_NAVIGM(VNC_MENU, VNT_MENU, FCO_PRUP, FCO_PREN, FCO_PRDN , VNC_PRUP, VNC_PREN, VNC_PRDN);
}



void G_MOSV1E(boolean TUP[],boolean TEN[],boolean TDN[], float VAL[], int ARG, float VAM[], boolean LOC) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : G_MOSV1E - Fonction de consignation d'une valeur de type Float entière sans mémorisation EEPROM ni titres               11/10/2017 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        G_MOSV1E(bool TUP[],bool TEN[],bool TDN[],float VAL[],int ARG,float VAM[],bool LOC,int AEP)                                        *
 *                TUP : [00] Etat de la touche "Up" après traitement antirebond                                                              *
 *                      [01] Etat brut de la touche "Up"                                                                                     *
 *                      [02] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_TOUCHD                                   *
 *                      [03] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_NAVIGM                                   *
 *                      [04] Mémorisation de l'état de la touche "Up" du cycle n-1 des fonctions G_MENU8L et G_MODV1x                        *
 *                TEN : [00] Etat de la touche "Enter" après traitement antirebond                                                           *
 *                      [01] Etat brut de la touche "Enter"                                                                                  *
 *                      [02] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_TOUCHD                                *
 *                      [03] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_NAVIGM                                *
 *                      [04] Mémorisation de l'état de la touche "Enter" du cycle n-1 des fonctions G_MENU8L et G_MODV1x                     *
 *                TDN : [00] Etat de la touche "Down" après traitement antirebond                                                            *
 *                      [01] Etat brut de la touche "Down"                                                                                   *
 *                      [02] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_TOUCHD                                 *
 *                      [03] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_NAVIGM                                 *
 *                      [04] Mémorisation de l'état de la touche "Down" du cycle n-1 des fonctions G_MENU8L et G_MODV1x                      *
 *                VAL : [xx] Valeur à modifier (Nécessairement un tableau de taille au moins 1)                                              *
 *                ARG : Entier - Rang de la valeur à mettre à jour dans le tableau VAL[]                                                     *
 *                VAM : [00] Valeur mémorisée entrée par l'utilisateur                                                                       *
 *                      [01] Valeur minimum de la valeur entrée                                                                              *
 *                      [02] Valeur maximum de la valeur entrée                                                                              *
 *                      [03] Pas de modification : valeur ajoutée ou soustraite de [04] a chaque pression sur Up ou Down                     *
 *                      [04] Valeur temporaire de modification avant validation                                                              *
 *                      [05] Calcul de durée du temps de cycle en ms                                                                         *
 *                      [06] Mémorisation de "millis"                                                                                        *
 *                      [07] Compteur de tempo de maintien Up ou Down pour un passage en défilement rapide                                   *
 *                      [08] Durée (ms) de la temporisation avant le passage en défilement rapide                                            *
 *                      [09] Autorisation du défilement rapide                                                                               *
 *                LOC : Booléen - Changement de consigne autorisé par la fonction si True, bloqué si False                                   *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * 27/09/2016 : SE2R, DD : Testée et validée sur banc Industruino 32U6 et 1286                                                               *
 * 10/10/2016 : SE2R, DD : Suppression des chaînes de caractères externes - Testée et validée sur banc Industruino 32U6 et 1286              *
 * 18/11/2016 : SE2R, DD : Ajout des accélérateurs x5 et x10 sur maintien Up et Down - Testée et validée sur banc Industruino 32U6 et 1286   *
 * 12/01/2017 : SE2R, DD : Suppression du numéro de menu - Testée et validée sur banc Industruino 32U6 et 1286                               *
 * 11/10/2017 : SE2R, DD : Suppression de la mémorisation EEPROM - Testée et validée sur banc Industruino 32U6 et 1286                       *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
byte FVH[5]= { B00001000, B00001100, B00001110, B00001100, B00001000};
lcd.createChar(0, FVH);
byte FEN[5]= { B00010000, B00111000, B01111100, B00010000, B00011110};
lcd.createChar(1, FEN);
byte FVB[5]= { B00000100, B00001100, B00011100, B00001100, B00000100};
lcd.createChar(2, FVB);
VAM[0] = min(VAM[0], VAM[2]);
VAM[0] = max(VAM[0], VAM[1]);
VAM[4] = VAM[0];
VAM[5] =  max(0, (millis() - VAM[6]));
VAM[6] =  millis();
if (((TUP[0] > 0.5) && (TUP[4] > 0.5)) || ((TDN[0] > 0.5) && (TDN[4] > 0.5))) {VAM[7] = VAM[7] + VAM[5];} else {VAM[7] = 0;}
if (VAM[7] < VAM[8]) {VAM[9] = 0;}
if (VAM[7] > VAM[8]) {VAM[9] = 1;}
if (VAM[7] > (9 * VAM[8])) {VAM[9] = 2;}
if (VAM[7] > (29 * VAM[8])) {VAM[9] = 3;}
if ((LOC == true) && ((TUP[0] > TUP[4]) || ((TUP[0] > 0.5) && (VAM[9] > 0.5)))) {
  if (VAM[4] <= (VAM[2] - VAM[3])) { VAM[4] = (VAM[4] + VAM[3]); } else { VAM[4] = VAM[2]; }
  if ((VAM[9] > 1.5) && (VAM[4] <= (VAM[2] - ( 5 * VAM[3])))) { VAM[4] = (VAM[4] + (4 * VAM[3])); }
  if ((VAM[9] > 2.5) && (VAM[4] <= (VAM[2] - (10 * VAM[3])))) { VAM[4] = (VAM[4] + (5 * VAM[3])); }
} 
if ((LOC == true) && ((TDN[0] > TDN[4]) || ((TDN[0] > 0.5) && (VAM[9] > 0.5)))) {
  if (VAM[4] >= (VAM[1] + VAM[3])) { VAM[4] = (VAM[4] - VAM[3]); } else { VAM[4] = VAM[1]; } 
  if ((VAM[9] > 1.5) && (VAM[4] >= (VAM[1] + ( 5 * VAM[3])))) { VAM[4] = (VAM[4] - (4 * VAM[3])); }
  if ((VAM[9] > 2.5) && (VAM[4] >= (VAM[1] + (10 * VAM[3])))) { VAM[4] = (VAM[4] - (5 * VAM[3])); }
}
VAM[0] = VAM[4];
if (TEN[0] > TEN[4]) {
  if (LOC == true) { VAL[ARG] = VAM[0]; }
}
lcd.setCursor(0, 2);  lcd.clearLine();  lcd.print("Mode:");
lcd.setCursor(30, 2); if (LOC == true) {lcd.print("Modif.Libre  ");} else {lcd.print("Modif.Bloquee");} 
lcd.setCursor(0, 3);  lcd.clearLine();
lcd.setCursor(10, 3); lcd.write(byte(0));
lcd.setCursor(24, 3); lcd.print(":+");
lcd.setCursor(42, 3); lcd.print(int(VAM[3]));
lcd.setCursor(74, 3); lcd.print("Max:");
lcd.setCursor(102, 3);  lcd.print(int(VAM[2]));
lcd.setCursor(0, 4);  lcd.clearLine();  lcd.print( "Prec:");
lcd.setCursor(42, 4); lcd.print(int(VAL[ARG]));
lcd.setCursor(0, 5);  lcd.print("Nouv:                ");
lcd.setCursor(0, 5);  lcd.clearLine();  lcd.print( "Nouv:");
lcd.setCursor(42, 5); lcd.print(int(VAM[4]));
lcd.setCursor(0, 6);  lcd.clearLine();
lcd.setCursor(10, 6); lcd.write(byte(2));
lcd.setCursor(24, 6); lcd.print(":-");
lcd.setCursor(42, 6); lcd.print(int(VAM[3]));
lcd.setCursor(74, 6); lcd.print("Min:");
lcd.setCursor(102, 6);  lcd.print(int(VAM[1]));
lcd.setCursor(0, 7);  lcd.clearLine();
lcd.setCursor(10, 7); lcd.write(byte(1));
lcd.setCursor(24, 7); lcd.print(": Valide + Retour");
TUP[4] = TUP[0];
TEN[4] = TEN[0];
TDN[4] = TDN[0];
return;
}

void G_MOSV1F(boolean TUP[],boolean TEN[],boolean TDN[], float VAL[], int ARG, float VAM[], boolean LOC) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : G_MOSV1F - Fonction de consignation d'une valeur de type Float sans mémorisation EEPROM ni titres                       11/10/2017 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        G_MOSV1F(bool TUP[],bool TEN[],bool TDN[],float VAL[],int ARG,float VAM[],bool LOC,int AEP)                                        *
 *                TUP : [00] Etat de la touche "Up" après traitement antirebond                                                              *
 *                      [01] Etat brut de la touche "Up"                                                                                     *
 *                      [02] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_TOUCHD                                   *
 *                      [03] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_NAVIGM                                   *
 *                      [04] Mémorisation de l'état de la touche "Up" du cycle n-1 des fonctions G_MENU8L et G_MODV1x                        *
 *                TEN : [00] Etat de la touche "Enter" après traitement antirebond                                                           *
 *                      [01] Etat brut de la touche "Enter"                                                                                  *
 *                      [02] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_TOUCHD                                *
 *                      [03] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_NAVIGM                                *
 *                      [04] Mémorisation de l'état de la touche "Enter" du cycle n-1 des fonctions G_MENU8L et G_MODV1x                     *
 *                TDN : [00] Etat de la touche "Down" après traitement antirebond                                                            *
 *                      [01] Etat brut de la touche "Down"                                                                                   *
 *                      [02] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_TOUCHD                                 *
 *                      [03] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_NAVIGM                                 *
 *                      [04] Mémorisation de l'état de la touche "Down" du cycle n-1 des fonctions G_MENU8L et G_MODV1x                      *
 *                VAL : [xx] Valeur à modifier (Nécessairement un tableau de taille au moins 1)                                              *
 *                ARG : Entier - Rang de la valeur à mettre à jour dans le tableau VAL[]                                                     *
 *                VAM : [00] Valeur mémorisée entrée par l'utilisateur                                                                       *
 *                      [01] Valeur minimum de la valeur entrée                                                                              *
 *                      [02] Valeur maximum de la valeur entrée                                                                              *
 *                      [03] Pas de modification : valeur ajoutée ou soustraite de [04] a chaque pression sur Up ou Down                     *
 *                      [04] Valeur temporaire de modification avant validation                                                              *
 *                      [05] Calcul de durée du temps de cycle en ms                                                                         *
 *                      [06] Mémorisation de "millis"                                                                                        *
 *                      [07] Compteur de tempo de maintien Up ou Down pour un passage en défilement rapide                                   *
 *                      [08] Durée (ms) de la temporisation avant le passage en défilement rapide                                            *
 *                      [09] Autorisation du défilement rapide                                                                               *
 *                LOC : Booléen - Changement de consigne autorisé par la fonction si True, bloqué si False                                   *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * 27/09/2016 : SE2R, DD : Testée et validée sur banc Industruino 32U6 et 1286                                                               *
 * 10/10/2016 : SE2R, DD : Suppression des chaînes de caractères externes - Testée et validée sur banc Industruino 32U6 et 1286              *
 * 18/11/2016 : SE2R, DD : Ajout des accélérateurs x5 et x10 sur maintien Up et Down - Testée et validée sur banc Industruino 32U6 et 1286   *
 * 12/01/2017 : SE2R, DD : Suppression du numéro de menu - Testée et validée sur banc Industruino 32U6 et 1286                               *
 * 11/10/2017 : SE2R, DD : Suppression de la mémorisation EEPROM - Testée et validée sur banc Industruino 32U6 et 1286                       *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
byte FVH[5]= { B00001000, B00001100, B00001110, B00001100, B00001000};
lcd.createChar(0, FVH);
byte FEN[5]= { B00010000, B00111000, B01111100, B00010000, B00011110};
lcd.createChar(1, FEN);
byte FVB[5]= { B00000100, B00001100, B00011100, B00001100, B00000100};
lcd.createChar(2, FVB);
VAM[0] = min(VAM[0], VAM[2]);
VAM[0] = max(VAM[0], VAM[1]);
VAM[4] = VAM[0];
VAM[5] =  max(0, (millis() - VAM[6]));
VAM[6] =  millis();
if (((TUP[0] > 0.5) && (TUP[4] > 0.5)) || ((TDN[0] > 0.5) && (TDN[4] > 0.5))) {VAM[7] = VAM[7] + VAM[5];} else {VAM[7] = 0;}
if (VAM[7] < VAM[8]) {VAM[9] = 0;}
if (VAM[7] > VAM[8]) {VAM[9] = 1;}
if (VAM[7] > (9 * VAM[8])) {VAM[9] = 2;}
if (VAM[7] > (29 * VAM[8])) {VAM[9] = 3;}
if ((LOC == true) && ((TUP[0] > TUP[4]) || ((TUP[0] > 0.5) && (VAM[9] > 0.5)))) {
  if (VAM[4] <= (VAM[2] - VAM[3])) { VAM[4] = (VAM[4] + VAM[3]); } else { VAM[4] = VAM[2]; }
  if ((VAM[9] > 1.5) && (VAM[4] <= (VAM[2] - ( 5 * VAM[3])))) { VAM[4] = (VAM[4] + (4 * VAM[3])); }
  if ((VAM[9] > 2.5) && (VAM[4] <= (VAM[2] - (10 * VAM[3])))) { VAM[4] = (VAM[4] + (5 * VAM[3])); }
} 
if ((LOC == true) && ((TDN[0] > TDN[4]) || ((TDN[0] > 0.5) && (VAM[9] > 0.5)))) {
  if (VAM[4] >= (VAM[1] + VAM[3])) { VAM[4] = (VAM[4] - VAM[3]); } else { VAM[4] = VAM[1]; } 
  if ((VAM[9] > 1.5) && (VAM[4] >= (VAM[1] + ( 5 * VAM[3])))) { VAM[4] = (VAM[4] - (4 * VAM[3])); }
  if ((VAM[9] > 2.5) && (VAM[4] >= (VAM[1] + (10 * VAM[3])))) { VAM[4] = (VAM[4] - (5 * VAM[3])); }
}
VAM[0] = VAM[4];
if (TEN[0] > TEN[4]) {
  if (LOC == true) { VAL[ARG] = VAM[0]; }
}
lcd.setCursor(0, 2);  lcd.clearLine();  lcd.print("Mode:");
lcd.setCursor(30, 2); if (LOC == true) {lcd.print("Modif.Libre  ");} else {lcd.print("Modif.Bloquee");} 
lcd.setCursor(0, 3);  lcd.clearLine();
lcd.setCursor(10, 3); lcd.write(byte(0));
lcd.setCursor(24, 3); lcd.print(":+");
lcd.setCursor(36, 3); lcd.print(VAM[3]);
lcd.setCursor(68, 3); lcd.print("Max:");
lcd.setCursor(92, 3); lcd.print(VAM[2]);
lcd.setCursor(0, 4);  lcd.clearLine();  lcd.print( "Prec:");
lcd.setCursor(30, 4); lcd.print(VAL[ARG]);
lcd.setCursor(0, 5);  lcd.clearLine();  lcd.print( "Nouv:");
lcd.setCursor(30, 5); lcd.print(VAM[4]);
lcd.setCursor(0, 6);  lcd.clearLine();
lcd.setCursor(10, 6); lcd.write(byte(2));
lcd.setCursor(24, 6); lcd.print(":-");
lcd.setCursor(36, 6); lcd.print(VAM[3]);
lcd.setCursor(68, 6); lcd.print("Min:");
lcd.setCursor(92, 6); lcd.print(VAM[1]);
lcd.setCursor(0, 7);  lcd.clearLine();
lcd.setCursor(10, 7); lcd.write(byte(1));
lcd.setCursor(24, 7); lcd.print(": Valide + Retour");
TUP[4] = TUP[0];
TEN[4] = TEN[0];
TDN[4] = TDN[0];
return;
}

void G_NAVIGM(int VNC[], int VNT[], boolean TUP[], boolean TEN[], boolean TDN[], int VNU[], int VNE[], int VND[]) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : G_NAVIGM - Navigation générale entre les écrans                                                                         26/09/2016 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        G_NAVIGM(int VNC[], int VNT[], boolean TUP[], boolean TEN[], boolean TDN[], int VNU[], int VNE[], int VND[])                       *
 *                VNC : [0] Numéro du menu en cours d'affichage                                                                              *
 *                      [1] Numéro du menu d'accueil                                                                                         *
 *                      [x] Numéro des autres écrans de l'afficheur (dizaines : niveau / unités : n° du menu dans le niveau)                 *
 *                VNT : [0] Taille des tables de navigation                                                                                  *
 *                      [1] Numéro de la ligne des tables correspondant à l'écran en cours                                                   *
 *                TUP : [0] Etat de la touche "Up" après traitement antirebond                                                               *
 *                      [1] Etat brut de la touche "Up"                                                                                      *
 *                      [2] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_TOUCHD                                    *
 *                      [3] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_NAVIGM                                    *
 *                      [4] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_MENU8L ou G_ASCG1x                        *
 *                TEN : [0] Etat de la touche "Enter" après traitement antirebond                                                            *
 *                      [1] Etat brut de la touche "Enter"                                                                                   *
 *                      [2] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_TOUCHD                                 *
 *                      [3] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_NAVIGM                                 *
 *                      [4] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_CHOIX8 ou G_ASCG1x                     *
 *                TDN : [0] Etat de la touche "Down" après traitement antirebond                                                             *
 *                      [1] Etat brut de la touche "Down"                                                                                    *
 *                      [2] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_TOUCHD                                  *
 *                      [3] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_NAVIGM                                  *
 *                      [4] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_MENU8L ou G_ASCG1x                      *
 *                VNU : [0] Numéro du menu de destination pour la touche "Up" pressée dans le menu courant                                   *
 *                      [1] Numéro du menu de destination pour la touche "Up" pressée dans l'écran d'accueil                                 *
 *                      [x] Numéro du menu de destination pour la touche "Up" pressée dans l'écran correspondant de la table VNC             *
 *                VNE : [0] Numéro du menu de destination pour la touche "Enter" pressée dans le menu courant                                *
 *                      [1] Numéro du menu de destination pour la touche "Enter" pressée dans l'écran d'accueil                              *
 *                      [x] Numéro du menu de destination pour la touche "Enter" pressée dans l'écran correspondant de la table VNC          *
 *                VND : [0] Numéro du menu de destination pour la touche "Down" pressée dans le menu courant                                 *
 *                      [1] Numéro du menu de destination pour la touche "Down" pressée dans l'écran d'accueil                               *
 *                      [x] Numéro du menu de destination pour la touche "Down" pressée dans l'écran correspondant de la table VNC           *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * 2015 07 05 : SE2R, DD : Testée et validée sur banc                                                                                        *
 * 2015 08 08 : SE2R, DD : Réorganisation des arguments pour harmoniser avec la famille de fonctions G                                       *
 *                         Cette fonction nécessite l'utilisation d'une fonction G_TOUCHx commune de suivi des touches de l'afficheur        *
 * 2015 10 08 : SE2R, DD : Correction d'un bug d'interaction entre le retour en page par défaut de G_TOUCHx et G_NAVIGM                      *
 * 2016 02 24 : SE2R, DD : Attention : Toujours placer l'appel de la fonction G_NAVIGM en dernier dans le programme                          *
 * 26/09/2016 : SE2R, DD : Mise à jour de l'itération sur I et correction du bug VNC / VNT dans la condition d'exécution                     *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
if ((VNU[VNT[1]] != VNE[VNT[1]]) || (VND[VNT[1]] != VNE[VNT[1]]) || (VNU[VNT[1]] != VND[VNT[1]])) {
    if ((TUP[0] > TUP[3]) && (VNC[VNT[1]] != VNU[VNT[1]])) {VNC[0] = VNU[VNT[1]]; }
    if ((TEN[0] > TEN[3]) && (VNC[VNT[1]] != VNE[VNT[1]])) {VNC[0] = VNE[VNT[1]]; }
    if ((TDN[0] > TDN[3]) && (VNC[VNT[1]] != VND[VNT[1]])) {VNC[0] = VND[VNT[1]]; }
    if (VNC[0] != VNC[VNT[1]]) {
    for (int i = 0; i <= VNT[0]; i++) {
      if  (VNC[0] == VNC[i]) { VNT[1] = i; }
    }
  }
    TUP[3] = TUP[0];
    TEN[3] = TEN[0];
    TDN[3] = TDN[0];
  }
  return;
}


void G_CHOIX8(int VNC[], int VNM, boolean TUP[],boolean TEN[],boolean TDN[], int VNX[], int VNT[]) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : G_CHOIX8 - Fonction de choix de destination dans une liste de 8 directions                                              26/09/2016 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        G_CHOIX8(int VNC[], int VNM, boolean TUP[],boolean TEN[],boolean TDN[], int VNX[])                                                 *
 *                VNC : [00] Numéro du menu en cours d'affichage                                                                             *
 *                      [01] Numéro du menu d'accueil                                                                                        *
 *                      [...] Menus suivants                                                                                                 *
 *                VNM : Numéro du menu concerné par l'appel de fonction                                                                      *
 *                TUP : [00] Etat de la touche "Up" après traitement antirebond                                                              *
 *                      [01] Etat brut de la touche "Up"                                                                                     *
 *                      [02] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_TOUCHD                                   *
 *                      [03] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_NAVIGM                                   *
 *                      [04] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_CHOIX8 et G_MODV1x                       *
 *                TEN : [00] Etat de la touche "Enter" après traitement antirebond                                                           *
 *                      [01] Etat brut de la touche "Enter"                                                                                  *
 *                      [02] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_TOUCHD                                *
 *                      [03] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_NAVIGM                                *
 *                      [04] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_CHOIX8 et G_MODV1x                    *
 *                TDN : [00] Etat de la touche "Down" après traitement antirebond                                                            *
 *                      [01] Etat brut de la touche "Down"                                                                                   *
 *                      [02] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_TOUCHD                                 *
 *                      [03] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_NAVIGM                                 *
 *                      [04] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_CHOIX8 et G_MODV1x                     *
 *                VNX : [00] Index du menu de destination de la ligne 0                                                                      *
 *                      [01] Index du menu de destination de la ligne 1                                                                      *
 *                      [...]                                                                                                                *
 *                      [07] Index du menu de destination de la ligne 7                                                                      *
 *                      [08] Index minimum de la ligne à pointer                                                                             *
 *                      [09] Index maximum de la ligne à pointer                                                                             *
 *                      [10] Index la ligne pointée                                                                                          *
 *                      [11] Information d'affichage déjà en place (= true en fin de 1er affichage du menu)                                  *
 *                VNT : [0] Taille des tables de navigation                                                                                  *
 *                      [1] Numéro de la ligne des tables correspondant à l'écran en cours                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino 32U8 et Industruino 1286                                                                               *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * 09/07/2015 : SE2R, DD : Testée et validée sur banc sous la forme de G_MENU8L                                                              *
 * 07/08/2015 : SE2R, DD : Suppression de l'affichage des lignes de texte et simplification de l'utilisation de VNC                          *
 *                         Nécessite G_MESS1L pour l'affichage des lignes de menus et G_TOUCHD pour détecter les actions sur les touches     *
 * 03/03/2016 : SE2R, DD : Restrictions d'exécution pour éviter des interactions avec d'autres fonctions de navigation                       *
 * 03/03/2016 : SE2R, DD : Testée et validée sur banc Industruino 32U6                                                                       *
 * 24/03/2016 : SE2R, DD : Testée et validée sur banc Industruino 1286 avec G.TOUCH2                                                         *
 * 26/09/2016 : SE2R, DD : Mise à jour de l'itération sur I et ajout de VNT pour naviguer vers l'écran suivant lors de l'action "Enter"      *
 * 01/10/2016 : SE2R, DD : Retour circulaire sur le menu en début et en fin de liste                                                         *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
if ((VNC[0] == VNM) && (VNX[8] != VNX[9])) {
  byte FLH[5]= { B01111111, B00111110, B00011100, B00001000, B00000000};
    lcd.createChar(0, FLH);
  if ((TUP[3] == TUP[0]) && (TEN[3] == TEN[0]) && (TDN[3] == TDN[0])) {
    lcd.setCursor(0, VNX[10]);
    lcd.write(byte(0));
  }
    if (TUP[0] > TUP[3]) { if ((VNX[10] - 1) < VNX[8]) { VNX[10] = VNX[9]; } else { VNX[10] = VNX[10] - 1 ; } }
    if (TDN[0] > TDN[3]) { if ((VNX[10] + 1) > VNX[9]) { VNX[10] = VNX[8]; } else { VNX[10] = VNX[10] + 1 ; } }
    if ((TUP[0] > TUP[3]) || (TDN[0] > TDN[3]) || (VNX[11] == 0)) {
        for (int I = VNX[8]; I <= VNX[9]; I++) {
           lcd.setCursor(0, I);
           if  (I == VNX[10]) { lcd.write(byte(0)); } else { lcd.print(" "); }
        }
    VNX[11] = 1;
  }
    if (TEN[0] > TEN[3]) {
        VNC[0] = VNX[VNX[10]];
    for (int i = 0; i <= VNT[0]; i++) { if  (VNC[0] == VNC[i]) { VNT[1] = i; } }
        VNX[11] = 0;
    }
    TUP[3] = TUP[0];
    TEN[3] = TEN[0];
    TDN[3] = TDN[0];
}
return;
}

void G_TOUCH3(int VNC[], float CPT[], boolean TUP[],boolean TEN[],boolean TDN[],int VNT[]) {
/*-------------------------------------------------------------------------------------------------------------------------------------------*
 * SE2R : G_TOUCH3 - Gestion des touches de l'écran Industruino D21G                                                              07/11/2017 *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 *        G_TOUCH3(int VNC[], float CPT[], boolean TUP[],boolean TEN[],boolean TDN[],int VNT[])                                              *
 *                VNC : [00] Numéro du menu en cours d'affichage                                                                             *
 *                      [01] Numéro du menu d'accueil                                                                                        *
 *                      [...] Menus suivants                                                                                                 *
 *                CPT : [00] Compteur de temporisation                                                                                       *
 *                      [01] Tempo de maintien allumé de l'écran après l'action sur une touche                                               *
 *                      [02] Tempo d'inactivité de retour à l'écran d'accueil (s)                                                            *
 *                      [03] Tempo de confirmation de la touche Enter (ms)                                                                   *
 *                      [04] Tempo de confirmation des touches de flêches (ms)                                                               *
 *                      [05] Temps de cycle automate calculé par la fonction                                                                 *
 *                      [06] Mémorisation de la variable système Millis pour le calcul du temps de cycle                                     *
 *                      [07] Lecture de l'état de l'entrée analogique de synthèse des touches                                                *
 *                      [08] Mémorisation de l'état de l'entrée analogique de synthèse des touches du cycle n-1                              *
 *                      [09] Mémorisation millis() lors au début de la dernière action sur une touche                                        *
 *                TUP : [00] Etat de la touche "Up" après traitement antirebond                                                              *
 *                      [01] Etat brut de la touche "Up"                                                                                     *
 *                      [02] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_TOUCH2                                   *
 *                      [03] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_NAVIGM                                   *
 *                      [04] Mémorisation de l'état de la touche "Up" du cycle n-1 de la fonction G_MENU8L ou G_CHOIX8                       *
 *                TEN : [00] Etat de la touche "Enter" après traitement antirebond                                                           *
 *                      [01] Etat brut de la touche "Enter"                                                                                  *
 *                      [02] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_TOUCH2                                *
 *                      [03] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_NAVIGM                                *
 *                      [04] Mémorisation de l'état de la touche "Enter" du cycle n-1 de la fonction G_MENU8L ou G_CHOIX8                    *
 *                TDN : [00] Etat de la touche "Down" après traitement antirebond                                                            *
 *                      [01] Etat brut de la touche "Down"                                                                                   *
 *                      [02] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_TOUCH2                                 *
 *                      [03] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_NAVIGM                                 *
 *                      [04] Mémorisation de l'état de la touche "Down" du cycle n-1 de la fonction G_MENU8L ou G_CHOIX8                     *
 *                VNT : [0] Taille des tables de navigation                                                                                  *
 *                      [1] Numéro de la ligne des tables correspondant à l'écran en cours                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Copyright SE2R under the APACHE Licence                                                                                                   *
 *-------------------------------------------------------------------------------------------------------------------------------------------*
 * Plate-formes testées : Industruino D21G                                                                                                   *
 * ------------------------------------------------------------------------------------------------------------------------------------------*
 * 07/11/2017 : SE2R, DD : Testée et validée sur banc                                                                                        *
 * ------------------------------------------------------------------------------------------------------------------------------------------*/
  CPT[5] =  max(0, (millis() - CPT[6])) / 1000;
  CPT[6] =  millis();
  CPT[7] = analogRead(A5);
  if (digitalRead(25) == HIGH) { TUP[1] = false; } else  { TUP[1] = true; }
  if (digitalRead(24) == HIGH) { TEN[1] = false; } else  { TEN[1] = true; }
  if (digitalRead(23) == HIGH) { TDN[1] = false; } else  { TDN[1] = true; }
  if ((TUP[1] > TUP[2]) || (TEN[1] > TEN[2]) || (TDN[1] > TDN[2])) { CPT[9] =  millis(); }
  if (((millis() - CPT[9]) > CPT[4]) && TUP[1] && TUP[2]) { TUP[0] = true; } else  { TUP[0] = false; }
  if (((millis() - CPT[9]) > CPT[3]) && TEN[1] && TEN[2]) { TEN[0] = true; } else  { TEN[0] = false; }
  if (((millis() - CPT[9]) > CPT[4]) && TDN[1] && TDN[2]) { TDN[0] = true; } else  { TDN[0] = false; }
  if (TUP[0] || TEN[0] || TDN[0]) { digitalWrite(26, HIGH); }
  TUP[2] = TUP[1];
  TEN[2] = TEN[1];
  TDN[2] = TDN[1];
  if (TUP[1] || TEN[1] || TDN[1]) { CPT[0] = 0; } else  { CPT[0] = CPT[0] + CPT[5]; }
  if (CPT[0] > CPT[1]) { digitalWrite(26, LOW); } else  { digitalWrite(26, HIGH); }
  if ((CPT[0] > CPT[2]) && (CPT[0] < (CPT[2] + 2))) { VNC[0] = VNC[1]; VNT[1] = 1; }
  CPT[0] = min(CPT[0], CPT[2] + 42);
  CPT[8] = CPT[7];
  return;
}
