/* 
 * File:   def_principais.h
 * Author: lauri
 *
 * Created on November 26, 2024, 8:18 PM
 */

#ifndef DEF_PRINCIPAIS_H
#define DEF_PRINCIPAIS_H

#define F_CPU 16000000UL // Define a frequ�ncia do microcontrolador - 16 MHz
#include <avr/io.h>        // Defini��es do componente especificado
#include <util/delay.h>    // Biblioteca para rotinas de atraso
#include <avr/pgmspace.h>  // Para o uso do PROGMEM, grava��o de dados na flash
#include <avr/interrupt.h> // Para o uso de interrup��es

// Defini��es de macros para o trabalho com bits
#define set_bit(y, bit) ((y) |= (1 << (bit)))
#define clr_bit(y, bit) ((y) &= ~(1 << (bit)))
#define cpl_bit(y, bit) ((y) ^= (1 << (bit)))
#define tst_bit(y, bit) ((y) & (1 << (bit)))

#endif
