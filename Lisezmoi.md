eControls-MEM_Fr et MEM_En

Bibliothèque de fonctions pour utiliser plus simplement la mémoire EEPROM I2C des Industruino D21G

Alors, y'a quoi là-dedans ?
Quelques fonctions C développées pour nous faciliter la vie quand nous programmons nos applications Industruino D21G.
Cette nouvelle gamme de microautomates à base Arduino ne comporte plus l'EEPROM embarquée des modèles précédents, et l'adressage de l'EEPROM I2C est un peu plus complexe que celui de l'ancienne version. Il nous a donc semble plus facile de créer un jeu de fonctions pour nous simplifier le travail.
Une fois combinées, ces fonctions vous permettront de sauver, relire et garder à jour votre mémoire EEPROM I2C en résuisant le volume de code à produire et les fautes de frappe au minimum.

Eh, toto. Maintenant que tu as fini de causer, si on parlait de code ?

Trois format de valeurs, trois actions possibles, neuf fonctions ? Eh non, dix, pour le même prix !

M_INIEEP : Initialiser l'adressage EEPROM
    M_INIEEP : Adresse les quatre blocs EEPROM I2C de 256 octets chacun. Doit être appelée dans l'initialisation avant toute utilisation des fonctions suivantes.

M_INTxxx : Traiter les entiers signés
    M_INTSET : Ecrit l'entier signé dans deux octets à la suite de l'EEPROM I2C
    M_INTGET : Lit l'entier signé dans deux octets à la suite de l'EEPROM I2C
    M_INTUPD : Compare l'entier signé aux deux octets à la suite de l'EEPROM I2C et tient l'EEPROM à jour s'ils sont différents

M_UINxxx : Traiter les entiers non signés
    M_UINSET : Ecrit l'entier non signé dans deux octets à la suite de l'EEPROM I2C
    M_UINGET : Lit l'entier non signé dans deux octets à la suite de l'EEPROM I2C
    M_UINUPD : Compare l'entier non signé aux deux octets à la suite de l'EEPROM I2C et tient l'EEPROM à jour s'ils sont différents

M_FLTxxx : Traiter les nombres à virgule flottante 
    M_FLTSET : Ecrit l'entier non signé dans quatre octets à la suite de l'EEPROM I2C
    M_FLTGET : Lit l'entier non signé dans quatre octets à la suite de l'EEPROM I2C
    M_FLTUPD : Compare l'entier non signé aux quatre octets à la suite de l'EEPROM I2C et tient l'EEPROM à jour s'ils sont différents
