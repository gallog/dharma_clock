#include "commandHum.h"

//TODO help
int hum(char *argc[], int argv) {
	int chk = DHT.read11();
	if (chk == DHTLIB_OK) {
		char buffer[6];
		dtostrf(DHT.humidity, 5, 2, buffer);
		TEXT_VIDEO_MEMORY[0] = "Humidity: "+ String(buffer) + "%";
		return 1;
	}
	TEXT_VIDEO_MEMORY[0] = "Error reading DHT11";
	return 1;
}
