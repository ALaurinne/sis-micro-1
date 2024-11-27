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
#include "def_principais.h" // Inclusão de definições principais
#include "LCD.h"
#include "eeprom.h" // Inclui funções de leitura/escrita na EEPROM

// Mensagens no LCD
const char mensagem1[] = "Teclado 4x4\0";
const char mensagem2[] = "Senha: \0";
const char msg_correto[] = "Senha correta! \0";
const char msg_incorreto[] = "Senha incorreta!\0";

#define EEPROM_SENHA_START 0x00 // Endereço inicial da senha na EEPROM
#define TAM_SENHA 4 // Tamanho da senha (número de dígitos)

// Função principal
int main() {
	unsigned char senha_digitada[TAM_SENHA];
	unsigned char senha_salva[TAM_SENHA];
	unsigned char nr;
	unsigned char indice = 0;

	DDRB = 0xFF;  // LCD no PORTB
	DDRD = 0x0F;   
	PORTD = 0xF0;

	EEPROM_escrita(0x00, '1');
	EEPROM_escrita(0x01, '2');
	EEPROM_escrita(0x02, '3');
	EEPROM_escrita(0x03, '4');

	// Inicialização do LCD
	inic_LCD_4bits();
	escreve_LCD_Flash(mensagem1);
	cmd_LCD(0xC0, 0); // Cursor na segunda linha
	escreve_LCD_Flash(mensagem2);

	// Leitura da senha salva na EEPROM
	for (int i = 0; i < TAM_SENHA; i++) {
		senha_salva[i] = EEPROM_leitura(EEPROM_SENHA_START + i);
	}

	while (1) {
		nr = ler_teclado(); // Lê o teclado constantemente


		if (nr != 0xFF) { // Se uma tecla foi pressionada
			cmd_LCD(0xC7 + indice, 0); // Atualiza cursor no LCD
			cmd_LCD(nr, 1); // Exibe o dígito no LCD
			senha_digitada[indice] = nr; // Armazena o dígito
			indice++;

			if (indice == TAM_SENHA) { // Quando 4 dígitos forem digitados
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
					escreve_LCD_Flash(msg_correto);
					} else {
					escreve_LCD_Flash(msg_incorreto);
				}

				// Limpa índice para nova entrada
				_delay_ms(2000); // Pausa para leitura
				cmd_LCD(0x01, 0); // Limpa LCD
				escreve_LCD_Flash(mensagem2);
				indice = 0;
			}
		}
	}
}
