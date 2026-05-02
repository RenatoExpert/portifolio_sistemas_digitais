/*
 * Codigo 2
 * Programa de piscar LEDs em sequencia para Arduino Uno
 * Este programa simula um registrador de deslocamento utilizando 5 LEDs
 */

#define QUANTIDADE_LEDS 5;	// Quantos leds existem
#define TEMPO_ACESO 200;

const int pinLEDs[] = { 8, 9, 10, 11, 12 };

// Outra forma de conseguir o valor de QUANTIDADE_LEDS seria utilizando a formula
// 	int quantidadeLEDs = sizeof(pinLEDs) / sizeof(pinLEDs[0]);
// Desde modo seria utilizada uma variavel, no lugar de uma definicao em macro
// Poderia ser util, caso o numero de LEDs variasse. Desta forma a iteracao do loop seria reajustada automaticamente

void setup() {
	for(int i = 0; i < QUANTIDADE_LEDS; i++) {
		pinMode(pinLEDs[i], OUTPUT);
	}
}

void loop() {
	for(int i = 0; i < QUANTIDADE_LEDS; i++) {
		digitalWrite(pinLEDs[i], HIGH);
		delay(TEMPO_ACESO);
		digitalWrite(pinLEDs[i]. LOW);
	}
}

