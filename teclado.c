
#include "teclado.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

#define set_bit(y, bit) ((y) |= (1 << (bit)))
#define clr_bit(y, bit) ((y) &= ~(1 << (bit)))
#define tst_bit(y, bit) ((y) & (1 << (bit)))

// Matriz do teclado (4x4)
const unsigned char teclado[4][4] PROGMEM = {
	{'1', '2', '3', 'F'},
	{'4', '5', '6', 'E'},
	{'7', '8', '9', 'D'},
	{'A', '0', 'B', 'C'}
};

// Função para ler o teclado
unsigned char ler_teclado() {
	unsigned char n, j, tecla = 0xFF, linha;

	for (n = 0; n < 4; n++) {
		PORTD = 0xFF;           // Inicializa todas as colunas como alto (1)
		clr_bit(PORTD, n);      // Abaixa apenas a coluna `n`
		_delay_ms(5);           // Atraso para estabilização

		linha = (PIND & 0xF0) >> 4; // Isola os 4 bits mais significativos (linhas)

		for (j = 0; j < 4; j++) {
			if (tst_bit(linha, j)) { // Se a linha está alta (tecla pressionada)
				tecla = pgm_read_byte(&teclado[j][n]); // Decodifica a tecla
				break; // Sai do loop interno
			}
		}

		set_bit(PORTD, n); // Restaura a coluna que foi zerada
		if (tecla != 0xFF) break; // Se encontrou uma tecla, sai do loop externo
	}

	return tecla; // Retorna 0xFF se nenhuma tecla foi pressionada
}