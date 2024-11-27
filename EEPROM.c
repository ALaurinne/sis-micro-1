
#include <avr/io.h>
#include "EEPROM.h"

void EEPROM_escrita(unsigned int uiEndereco, unsigned char ucDado)
{
while(EECR & (1<<EEPE)); //espera completar um escrita pr�via
EEAR = uiEndereco; //carrega o endere�o para a escrita
EEDR = ucDado; //carrega o dado a ser escrito
EECR |= (1<<EEMPE); //escreve um l�gico em EEMPE
EECR |= (1<<EEPE); //inicia a escrita ativando EEPE
}
unsigned char EEPROM_leitura(unsigned int uiEndereco)
{
while(EECR & (1<<EEPE)); //espera completar um escrita pr�via
EEAR = uiEndereco; //escreve o endere�o de leitura
EECR |= (1<<EERE); //inicia a leitura ativando EERE
return EEDR; //retorna o valor lido do registrador de
//dados
} 