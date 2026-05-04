/*
 * Codigo 3
 * Controle de luminosidade de um LED com Potenciometro
 * Este programa permite controlar a intensidade luminosa de um LED com base na posicao de um potenciometro
 */

#define PINO_POTENCIOMETRO A0	// Pino / entrada analogica onde o potenciometro esta conectado
#define PINO_LED 10		// Pino / saida analogica onde o LED esta conectado

// Inicializacao
void setup() {
	pinMode(PINO_LED, OUTPUT);	// Configurando o pino do LED como saida
}

// Execucao em repeticao infinita
void loop() {
	// Leitura do potenciometro (utilizando a faixa 0-1023)
	int valorPotenciometro = analogRead(PINO_POTENCIOMETRO);
	// Conversao da faixa 0-1023 (da entrada analogica) para a faixa 0-255 (da saida analogica)
	int luminosidade = map(valorPotenciometro, 0, 1023, 0, 255);
	// Alterando o novo valor de luminosidade na saida analogica, utilizando a faixa 0-255
	analogWrite(PINO_LED, luminosidade);
}

