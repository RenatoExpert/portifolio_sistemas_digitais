/*
 * Codigo 4
 * Controle de luminosidade de um LED por comunicacao serial
 * Este programa permite controlar o brilho do LED por meio de comandos enviados pela comunicacao serial
 */

#include <stdlib.h>

#define PINO_LED 10	// Pino de saida PWM onde o led esta conectado
char comandoSerial[4];

void setup() {
	Serial.begin(9600);		// Inicia comunicacao serial com baudrate de 9600
	pinMode(PINO_LED, OUTPUT);	// Configura o pino do led como saida
}

void loop() {
	// Verifica se ha pelo menos 3 bytes disponiveis na serial
	if(Serial.available() >= 3) {
		// Move os 3 bytes do buffer da serial para o array comandoSerial
		Serial.readBytes(comandoSerial, 3);
		// Adiciona null ao final do array, para conversao em string
		comandoSerial[3] = '\0';
		// Converte a string recebida para inteiro
		// e limita o valor final para dentro da faixa 0-255
		int luminosidade = constrain(atoi(comandoSerial), 0, 255);
		// Ajusta o valor (de duty cycle) para o pino do LED
		analogWrite(PINO_LED, luminosidade);
	}
}

