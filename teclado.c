
#include "teclado.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

#define set_bit(y, bit) ((y) |= (1 << (bit)))
#define clr_bit(y, bit) ((y) &= ~(1 << (bit)))
#define tst_bit(y, bit) ((y) & (1 << (bit)))

// Matriz do teclado (4x4)
const unsigned char teclado[4][3] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
	{'*', '0', '#'}
};

// Funï¿½ï¿½o para ler o teclado
unsigned char ler_teclado() {
	unsigned char n, j, tecla = 0xFF, col;

	for (n = 0; n < 4; n++) {
		PORTD = 0xFF;           // Inicializa todas as linhas como alto (1)
		clr_bit(PORTD, n);      // Abaixa apenas a linha `n`
		_delay_ms(5);           // Atraso para estabilizaï¿½ï¿½o

		col = (PIND & 0x70) >> 4; // Isola os 4 bits mais significativos (linhas)

		for (j = 0; j < 3; j++) {
			if (!tst_bit(col, j)) { // Se a linha estï¿½ alta (tecla pressionada)
				tecla = (teclado[n][j]); // Decodifica a tecla
				break; // Sai do loop interno
			}
		}

		set_bit(PORTD, n); // Restaura a coluna que foi zerada
		if (tecla != 0xFF) break; // Se encontrou uma tecla, sai do loop externo
	}

	return tecla; // Retorna 0xFF se nenhuma tecla foi pressionada
}