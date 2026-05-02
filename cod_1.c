/*
 * Codigo 1
 * Programa Eco
 * Esse primeiro programa tem como objetivo implementar uma comunicacao serial simples, onde o Arduino recebe um caractere digitado e o envia de volta ao usuario
 */

void setup() {			// Rotina executada durante a inicializacao do sistema
	Serial.begin(9600);	// Inicializa a comunicacao serial com taxa de 9600 bps
}

void loop() {				// Rotina que se mantem em repeticao, executada apos a funcao setup
	if (Serial.available() > 0) {	// Verifica se há dados disponiveis na portaserial
		char receivedChar = Serial.read();	// Leitura do caractere recebido
		Serial.print("Voce digitou: ");		// Envio da primeira parte da mensagem
		Serial.println(receivedChar);		// Complementando a mensagem com o caractere digitado
	}
}

