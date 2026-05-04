/*
 * Codigo 5
 * Monitor de umidade
 * Esse algoritmo faz com que o arduino realize a leitura da umidade do solo e acenda o LED correspondente ao nivel detectado
 */

// Utilizando macros para enderecar os pinos
#define LED_VERMELHO 13
#define LED_AMARELO 12
#define LED_LARANJA 11
#define LED_AZUL 10
#define LED_VERDE 9
#define PIN_VCC A0
#define PIN_SENSOR A1

// Macros para limites de faixa de valores
#define LIMITE_VERMELHO 200
#define LIMITE_AMARELO 400
#define LIMITE_LARANJA 600
#define LIMITE_AZUL 800

// Definindo intervalo do loop em 1 segundo
#define INTERVALO 1000

// Inicializando variavel umidade
// Poderia tambem ser inicializado dentro de loop()
int umidade = 0;

void setup() {
	// Configurando os pinos como saida digital para os LEDs
	pinMode(LED_VERMELHO, OUTPUT);
	pinMode(LED_AMARELO, OUTPUT);
	pinMode(LED_LARANJA, OUTPUT);
	pinMode(LED_AZUL, OUTPUT);
	pinMode(LED_VERDE, OUTPUT);
	// Configurando o pino A0 (VCC) como saida
	pinMode(PIN_VCC, OUTPUT);
	// Ativando saida digital para PIN_VCC
	digitalWrite(PIN_VCC, HIGH);
	// Configurando o pino A1 (sensor) como entrada analogica
	pinMode(PIN_SENSOR, INPUT);
	// Inicializando a comunicacao serial com baudrate de 9600bps
	Serial.begin(9600);
}

void loop() {
	// Leitura do valor de umidade
	umidade = analogRead(PIN_SENSOR);
	// Enviar valor para o serial, para mostragem em terminal
	Serial.println(umidade);

	// Desligando todos os LEDs
	digitalWrite(LED_VERMELHO, LOW);
	digitalWrite(LED_AMARELO, LOW);
	digitalWrite(LED_LARANJA, LOW);
	digitalWrite(LED_AZUL, LOW);
	digitalWrite(LED_VERDE, LOW);

	// Ativando apenas o LED relativo ao valor atual de umidade
	if (umidade < LIMITE_VERMELHO) {
		digitalWrite(LED_VERMELHO, HIGH);
	} else if (umidade < LIMITE_AMARELO) {
		digitalWrite(LED_AMARELO, HIGH);
	} else if (umidade < LIMITE_LARANJA) {
		digitalWrite(LED_LARANJA, HIGH);
	} else if (umidade < LIMITE_AZUL) {
		digitalWrite(LED_AZUL, HIGH);
	} else {
		digitalWrite(LED_VERDE, HIGH);
	}

	// Intervalo para manter o valor antes da proxima leitura
	delay(INTERVALO);
}

