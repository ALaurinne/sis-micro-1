#include "teclado.h"
#include "LCD.h"
#include "EEPROM.h"
#include <avr/io.h>
#include <util/delay.h>

// Endere�os de mem�ria para senhas na EEPROM
#define EEPROM_SENHA1 0x00
#define EEPROM_SENHA2 0x04

// Prot�tipo de fun��es auxiliares
void solicitar_senha(char *senha_digitada);
unsigned char verificar_senha(const char *senha_digitada, const char *senha_salva);

int main(void) {
    
    DDRA |= (1 << PA1); // Configura PA1 como sa�da

    
    char senha_digitada[5] = {0}; // Buffer para senha digitada
    char senha_salva[5] = {0};    // Buffer para senha salva da EEPROM
    unsigned char tentativas = 0;

    // Inicializa��es
    DDRD = 0x0F; // Configura PORTD: 4 MSB como entrada (linhas), 4 LSB como sa�da (colunas)
    DDRB = 0x03; // Configura PORTB: pinos de controle do LCD como sa�da
    inic_LCD_4bits(); // Inicializa o LCD

    escreve_LCD("Digite a senha:"); // Mensagem inicial no LCD

    while (1) {
        
        // Solicita e l� a senha digitada pelo teclado
        solicitar_senha(senha_digitada);

        // Carrega senha salva na EEPROM
        for (unsigned char i = 0; i < 4; i++) {
            senha_salva[i] = EEPROM_leitura(EEPROM_SENHA1 + i);
        }
        senha_salva[4] = '\0'; // Finaliza string

        // Verifica se a senha digitada est� correta
        if (verificar_senha(senha_digitada, senha_salva)) {
            escreve_LCD("Senha correta!");
            break; // Sai do loop
        } else {
            escreve_LCD("Senha incorreta!");
            tentativas++;
            _delay_ms(2000); // Espera para leitura da pr�xima tentativa
            escreve_LCD("Digite novamente:");
        }

        // Se exceder 3 tentativas, bloquear o sistema
        if (tentativas >= 3) {
            escreve_LCD("Acesso negado!");
            while (1) {
                // LED de alerta no pino A1
                set_bit(PORTAs, PA1); // Liga o LED
                _delay_ms(500);
                clr_bit(PORTA, PA1); // Desliga o LED
                _delay_ms(500);
            }
        }
    }

    return 0;
}

void solicitar_senha(char *senha_digitada) {
    unsigned char tecla;
    unsigned char posicao = 0;

    escreve_LCD("Senha: "); // Mostra no LCD
    while (posicao < 4) {
        tecla = ler_teclado(); // L� uma tecla
        if (tecla != 0xFF) {   // Verifica se alguma tecla foi pressionada
            senha_digitada[posicao++] = tecla; // Armazena o d�gito
            cmd_LCD('*', 1); // Exibe '*' no LCD para esconder o d�gito
        }
    }
    senha_digitada[4] = '\0'; // Finaliza a string
}

unsigned char verificar_senha(const char *senha_digitada, const char *senha_salva) {
    for (unsigned char i = 0; i < 4; i++) {
        if (senha_digitada[i] != senha_salva[i]) {
            return 0; // Senha incorreta
        }
    }
    return 1; // Senha correta
}
