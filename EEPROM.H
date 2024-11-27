/* 
 * File:   EEPROM.H
 * Author: lauri
 *
 * Created on November 26, 2024, 9:49 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H
#define F_CPU 1000000UL
#include <util/delay.h>

void EEPROM_escrita(unsigned int address, unsigned char data);
unsigned char EEPROM_leitura(unsigned int address);

#endif /* EEPROM_H_ */
