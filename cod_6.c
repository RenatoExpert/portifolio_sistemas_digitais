/*
 * Codigo 6
 * Leitura de umidade e temperatura
 * Envia dados do sensor DHT a cada 1 minuto, utilizando modulo RTC
 */

#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>

#define DHT_PIN 2	// Pino do sensor DHT11
#define DHT_TYPE DHT11	// Tipo do sensor DHT

#define MINUTE (60 * 1000)

RTC_DS1302 rtc;
DHT dht(DHT_PIN, DHT_TYPE);

long last_cycle_minute = 0;

void setup () {
	Serial.begin(9600);
	// Inicializar o rtc e verificar se o mesmo foi inicializado corretamente
	if (!rtc.begin()) {
		Serial.println("Nao foi possivel encontrar o modulo RTC!");
		// Trava a execucao do sistema ate que seja reiniciado novamente
		while(1);
	}
	// Verificando a execucao e configurando data e hora do RTC
	if (!rtc.isrunning()) {
		Serial.println("Configurando a hora!");
		// __DATE__ e __TIME__ sao macros que sao substituidos
		// pela data e hora do sistema durante a compilacao
		rtc.adjust(Datetime(F(__DATE__), F(__TIME__)));
	}
	// Iniciando o medidor DHT
	dht.begin();
}


void loop () {
	// Leitura do timestamp atual utilizando o modulo RTC
	dt_now = rtc.now();

	// Convertendo para minutos
	long current_minute = dt_now.unixtime() / MINUTE;
	// Verificando se ja se passou um minuto desde a ultima medicao
	if (current_minute > last_cycle_minute) {
		// Formatando a data e hora atuais
		dt_string = dt.ToString("dd/MM/yyyy HH:mm:ss");

		// Lendo a temperatura e formatando em String
		float temperature = dht.readTemperature();
		char temp_str[6];
		dtostrf(temperature, 5, 1, temp_str);

		// Lendo a umidade atual e formatando em String
		float humidity = dht.readHumidity();
		char hum_str[6];
		dtostrf(humidity, 5, 1, hum_str);

		// Unindo todos os textos em um so e enviando para o serial
		char text[100];
		sprint(text, "Data e Hora: %s | Temperatura: %s\xB0C | Umidade: %s%%\n", dt_string, temperature, humidity);
		Serial.print(text);

		// Armazenando a informacao de quando ocorreu a ultima medicao
		last_cycle_minute = current_minute;
	}
}

