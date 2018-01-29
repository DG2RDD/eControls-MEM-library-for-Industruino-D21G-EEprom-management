eControls-MEM_Fr et MEM_En

Biblioth�que de fonctions pour utiliser plus simplement la m�moire EEPROM I2C des Industruino D21G

Alors, y'a quoi l�-dedans ?
Quelques fonctions C d�velopp�es pour nous faciliter la vie quand nous programmons nos applications Industruino D21G.
Cette nouvelle gamme de microautomates � base Arduino ne comporte plus l'EEPROM embarqu�e des mod�les pr�c�dents, et l'adressage de l'EEPROM I2C est un peu plus complexe que celui de l'ancienne version. Il nous a donc semble plus facile de cr�er un jeu de fonctions pour nous simplifier le travail.
Une fois combin�es, ces fonctions vous permettront de sauver, relire et garder � jour votre m�moire EEPROM I2C en r�suisant le volume de code � produire et les fautes de frappe au minimum.

Eh, toto. Maintenant que tu as fini de causer, si on parlait de code ?

Trois format de valeurs, trois actions possibles, neuf fonctions ? Eh non, dix, pour le m�me prix !

M_INIEEP : Initialiser l'adressage EEPROM
    M_INIEEP : Adresse les quatre blocs EEPROM I2C de 256 octets chacun. Doit �tre appel�e dans l'initialisation avant toute utilisation des fonctions suivantes.

M_INTxxx : Traiter les entiers sign�s
    M_INTSET : Ecrit l'entier sign� dans deux octets � la suite de l'EEPROM I2C
    M_INTGET : Lit l'entier sign� dans deux octets � la suite de l'EEPROM I2C
    M_INTUPD : Compare l'entier sign� aux deux octets � la suite de l'EEPROM I2C et tient l'EEPROM � jour s'ils sont diff�rents

M_UINxxx : Traiter les entiers non sign�s
    M_UINSET : Ecrit l'entier non sign� dans deux octets � la suite de l'EEPROM I2C
    M_UINGET : Lit l'entier non sign� dans deux octets � la suite de l'EEPROM I2C
    M_UINUPD : Compare l'entier non sign� aux deux octets � la suite de l'EEPROM I2C et tient l'EEPROM � jour s'ils sont diff�rents

M_FLTxxx : Traiter les nombres � virgule flottante 
    M_FLTSET : Ecrit l'entier non sign� dans quatre octets � la suite de l'EEPROM I2C
    M_FLTGET : Lit l'entier non sign� dans quatre octets � la suite de l'EEPROM I2C
    M_FLTUPD : Compare l'entier non sign� aux quatre octets � la suite de l'EEPROM I2C et tient l'EEPROM � jour s'ils sont diff�rents
