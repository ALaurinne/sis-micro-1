/* 
 * File:   teclado.h
 * Author: lauri
 *
 * Created on November 26, 2024, 8:17 PM
 */

#ifndef TECLADO_H
#define	TECLADO_H

#include "def_principais.h"

#define LINHA PIND //registrador para a leitura das linhas
#define COLUNA PORTD //registrador para a escrita nas colunas

//prot�tipo da fun��o
unsigned char ler_teclado();
#endif