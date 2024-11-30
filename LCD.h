/* 
 * File:   LCD.h
 * Author: lauri
 *
 * Created on November 26, 2024, 8:18 PM
 */
#ifndef LCD_H
#define LCD_H

#include <util/delay.h>
#include "def_principais.h"

// Configura��es do LCD
#define DADOS_LCD PORTB      // 4 bits de dados do LCD no PORTD
#define nibble_dados 0       // Usa o nibble baixo
#define CONTR_LCD PORTB      // PORT com os pinos de controle do LCD
#define E PB5                // Pino de habilita��o do LCD (enable)
#define RS PB4               // Pino para instru��o ou caractere
#define tam_vetor 5          // N�mero de d�gitos para convers�o em ident_num()
#define conv_ascii 48        // Adiciona 48 para formato ASCII (ou 0 para n�meros puros)


// Macro para habilitar o LCD
#define pulso_enable() \
    do { \
        _delay_us(1); \
        set_bit(CONTR_LCD, E); \
        _delay_us(1); \
        clr_bit(CONTR_LCD, E); \
        _delay_us(45); \
    } while (0)

// Prot�tipos das fun��es
void cmd_LCD(unsigned char c, char cd);
void inic_LCD_4bits();
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);
void ident_num(unsigned int valor, unsigned char *disp);

#endif
