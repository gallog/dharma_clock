#include "commandTemp.h"

//TODO help
int temp(char *argc[], int argv) {
  String ret;
  int chk = DHT.read11();
  if (chk == DHTLIB_OK) {
    char buffer[6];
    dtostrf(DHT.temperature, 5, 2, buffer);
    TEXT_VIDEO_MEMORY[0] = "Temperature: " +String(buffer)+"C";
    return 1;
  }
  TEXT_VIDEO_MEMORY[0] = "Error reading DHT11";
  return 1;
}
