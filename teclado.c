
#include "teclado.h"
#include <util/delay.h>

const unsigned char teclado[4][4] PROGMEM = {{'1', '2', '3', 'F'},
 {'4', '5', '6', 'E'},
 {'7', '8', '9', 'D'},
 {'A', '0', 'B', 'C'}};
	 
unsigned char ler_teclado()
{
 unsigned char n, j, tecla=0xFF, linha;
 for(n=0;n<4;n++)
 {
	 clr_bit(COLUNA,n); //apaga o bit da coluna (varredura)
	 _delay_ms(10); /*atraso para uma varredura mais lenta, também elimina
	 o ruído da tecla*/
	 linha = LINHA >> 4; //lê o valor das linhas

	 for(j=0;j<4;j++) //testa as linhas
	 {
		 if(!tst_bit(linha,j))//se foi pressionada alguma tecla,
		 { //decodifica e retorna o valor
		 tecla = pgm_read_byte(&teclado[j][n]);
		 }
	 }
	set_bit(COLUNA,n); //ativa o bit zerado anteriormente
 }
 return tecla; //retorna o valor 0xFF se nenhuma tecla foi pressionada
} 