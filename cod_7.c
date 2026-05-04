/*
 * Codigo 7
 * Estacao meteorologica
 * Simula uma estacao meteorologica que registra e consulta dados utilizando a EEPROM
 */

#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <EEPROM.h>

#define DHT_PIN 2	// Pino de dados do sensor DHT11
#define DHT_TYPE DHT11	// Tipo do sensor DHT

// Instanciando os objetos controladores para os modulos RTC e DHT
RTC_DS1302 rtc;
DHT dht(DHT_PIN, DHT_TYPE);

#define EEPROM_LIMIT 1023	// Ultimo endereco da EEPROM
#define ROW_SIZE 7		// Tamanho de cada medicao
#define MINUTE (60 * 1000)	// Conversor de minutos para milissegundos

int epointer = 0;		// Registrador acumulador para endereco da memoria EEPROM
long last_cycle_minute = 0;	// Minuto (unix) quando ocorreu a ultima medicao

void setup () {
	Serial.begin(9600);
	if (!rtc.begin()) {
		Serial.println("Nao foi possivel encontrar o modulo RTC!");
		while(1);
	}
	if (!rtc.isrunning()) {
		Serial.println("Configurando a hora!");
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}
	dht.begin();
}

void loop () {
	// Verificando se foi utilizado o comando L
	while (Serial.available()) {
		if (Serial.read() == 'L') {
			l_pressed_event();
		}
	}

	// Leitura do timestamp atual utilizando o modulo RTC
	DateTime dt_now = rtc.now();

	// Convertendo para minutos
	long current_minute = dt_now.unixtime() / MINUTE;
	// Verificando se ja se passou um minuto desde a ultima medicao
	if (current_minute > last_cycle_minute) {
		// Formatando a data e hora atuais
		char dt_string[] = dt_now.ToString("dd/MM/yyyy HH:mm:ss");

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
		sprintf(text, "Data e Hora: %s | Temperatura: %s\xB0C | Umidade: %s%%\n", dt_string, temp_str, hum_str);
		Serial.print(text);

		// Armazenando a informacao de quando ocorreu a ultima medicao
		last_cycle_minute = current_minute;

		// Verificando se ha espaco suficiente para armazenar novos dados
		if (epointer < EEPROM_LIMIT - ROW_SIZE) {
			// Preparando dados para EEPROM
			// Convertendo todos para int8_t
			//   para manter um padrao, considerando que a temperatura
			//   pode ser negativa em alguns casos
			int8_t day_byte = (int8_t)dt_now.day();
			int8_t month_byte = (int8_t)dt_now.month();
			int8_t year_byte = (int8_t)(dt_now.year() % 100);
			int8_t hour_byte = (int8_t)(dt_now.hour());
			int8_t minute_byte = (int8_t)(dt_now.minute());
			int8_t temp_byte = (int8_t)temperature;
			int8_t hum_byte = (int8_t)humidity;
			// Armazenando dados na EEPROM
			EEPROM.write(epointer++, day_byte);
			EEPROM.write(epointer++, month_byte);
			EEPROM.write(epointer++, year_byte);
			EEPROM.write(epointer++, hour_byte);
			EEPROM.write(epointer++, minute_byte);
			EEPROM.write(epointer++, temp_byte);
			EEPROM.write(epointer++, hum_byte);
		} else {
			Serial.println("ERRO: Limite do uso de armazenamento da EEPROM excedido!");
		}
	}
}

void clear_data () {
	for (int i = 0; i <= epointer; i++) {
		EEPROM.write(i, 0);
	}
	epointer = 0;
	Serial.println("Os dados da EEPROM foram apagados!");
}

void l_pressed_event () {
	Serial.println("Recuperando dados armazenados...");
	for (int i = 0; i < epointer / ROW_SIZE; i++) {
		int8_t buffer[ROW_SIZE];
		for (int j = 0; j < ROW_SIZE; j++) {
			int address = (i * ROW_SIZE) + j;
			buffer[j] = EEPROM.read(address);
		}
		char text[200];
		// Macro apenas para diminuir o tamanho da linha
		#define B(x) (buffer[x])
		sprintf(
			text,
			"Data: %d/%d/20%d | Hora: %d:%d:00 | Temperatura: %d\xB0C | Umidade: %d%%\n",
			B(0), B(1), B(2), B(3), B(4), B(5), B(6)
		);
		Serial.println(text);
	}
	clear_data();
}

