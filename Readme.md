# eControls-MEM_En and MEM_Fr

Functions library to help your use of Industruino D21G I2C EEPROM

Some C functions originally developped to simplify our programming of controls applications in Industruino D21G.
This new hardware product line does not feature regular EEPROM any more. I has been replaced with I2C EEPROM, which is slightly more complex to use. So we found it was easier to create this set of functions to make our life a bit easier.
These functions will allow you to write, read, and update your I2C EEPROM while keeping the control code you will have to write, and misspellings, to a minimum.

Now you're done with your babbling, what about some code ?

Three value formats, three possible actions, nine functions ? With us, you'll get 10 for the same price

M_INIEEP : Initialize EEPROM adresses
    M_INIEEP : Adresses the four I2C EEPROM 256-bytes blocks. Has to be called in the init line before you use other functions.

M_INTxxx : for signed integers
    M_INTSET : Writes the signed integer to two contiguous bytes in I2C EEPROM
    M_INTGET : Reads the signed integer in two contiguous bytes in I2C EEPROM
    M_INTUPD : Compares the two contiguous bytes in I2C EEPROM to the current signed integer value and updates the EEPROM if necessary.

M_INTxxx : for unsigned integers
    M_UINSET : Writes the unsigned integer to two contiguous bytes in I2C EEPROM
    M_UINGET : Reads the unsigned integer in two contiguous bytes in I2C EEPROM
    M_UINUPD : Compares the two contiguous bytes in I2C EEPROM to the current unsigned integer value and updates the EEPROM if necessary.

M_FLTxxx : For floats
    M_UINSET : Writes the float to four contiguous bytes in I2C EEPROM
    M_UINGET : Reads the float in four contiguous bytes in I2C EEPROM
    M_UINUPD : Compares the four contiguous bytes in I2C EEPROM to the current float value and updates the EEPROM if necessary.
