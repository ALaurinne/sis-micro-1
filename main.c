/*
 * main.c
 *
 * Created: 11/27/2024 7:51:40 AM
 *  Author: lauri
 */ 

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include "teclado.h"
#include "def_principais.h" // Inclusï¿½o de definiï¿½ï¿½es principais
#include "LCD.h"
#include <stdbool.h>  // Ou use sua pr�pria defini��o
#include "eeprom.h" // Inclui funï¿½ï¿½es de leitura/escrita na EEPROM

// Mensagens no LCD
const char mensagem1[] = "Teclado 4x4";
const char mensagem2[] = "Senha: ";
const char msg_correto[] = "Senha correta!";
const char msg_incorreto[] = "Senha incorreta!";

#define EEPROM_SENHA_START 0x00 // Endereï¿½o inicial da senha na EEPROM
#define TAM_SENHA 4 // Tamanho da senha (nï¿½mero de dï¿½gitos)
#define LED PC5
#define RED PC4

// Funï¿½ï¿½o principal
int main() {
	unsigned char senha_digitada[TAM_SENHA];
	unsigned char senha_salva[TAM_SENHA];
	unsigned char nr;
	unsigned char indice = 0;
    bool botao_pressionado = false;

	DDRB = 0xFF;  // LCD no PORTB
	DDRD = 0x0F;   // Saida de D0 a D3 e entrada de D4 a D7
	PORTD = 0xF0;

    DDRC = 0xFF; //configura todos os pinos do PORTB como saï¿½das

	EEPROM_escrita(0x00, '1');
	EEPROM_escrita(0x01, '2');
	EEPROM_escrita(0x02, '3');
	EEPROM_escrita(0x03, '4');

	// Inicializaï¿½ï¿½o do LCD
	inic_LCD_4bits();
	escreve_LCD(mensagem1);
	cmd_LCD(0xC0, 0); // Cursor na segunda linha
	escreve_LCD(mensagem2);

	// Leitura da senha salva na EEPROM
	for (int i = 0; i < TAM_SENHA; i++) {
		senha_salva[i] = EEPROM_leitura(EEPROM_SENHA_START + i);
	}

	while (1) {
        
        clr_bit(PORTC,RED); 
        clr_bit(PORTC,LED); 
        
        _delay_ms(200); //liga LED
		nr = ler_teclado(); // Lï¿½ o teclado constantemente
		

		if (nr != 0xFF && !botao_pressionado ) { // Se uma tecla foi pressionada
            botao_pressionado = true;
			cmd_LCD(0xC7 + indice, 0); // Atualiza cursor no LCD
			cmd_LCD(nr, 1); // Exibe o dï¿½gito no LCD
			senha_digitada[indice] = nr; // Armazena o dï¿½gito
			indice++;

			if (indice == TAM_SENHA) { // Quando 4 dï¿½gitos forem digitados
				// Verifica a senha
				int senha_correta = 1;
				for (int i = 0; i < TAM_SENHA; i++) {
					if (senha_digitada[i] != senha_salva[i]) {
						senha_correta = 0;
						break;
					}
				}

				// Exibe resultado no LCD
				cmd_LCD(0xC0, 0); // Move para a segunda linha
				if (senha_correta) {
					escreve_LCD(msg_correto);
                    set_bit(PORTC,LED); 
					} else {
					escreve_LCD(msg_incorreto);
                    set_bit(PORTC,RED); 
				}

				// Limpa ï¿½ndice para nova entrada
				_delay_ms(10000); // Pausa para leitura
				cmd_LCD(0x01, 0); // Limpa LCD
				escreve_LCD(mensagem2);
				indice = 0;
			}
		}  else if (nr == 0xFF){
            botao_pressionado = false;
        }
          

	}
}
