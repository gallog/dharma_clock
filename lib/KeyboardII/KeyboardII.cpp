#include "KeyboardII.h"

byte KeyboardII::data;
byte KeyboardII::dataReady;
byte KeyboardII::__d0;
byte KeyboardII::__d1;
byte KeyboardII::__d2;
byte KeyboardII::__d3;
byte KeyboardII::__d4;
byte KeyboardII::__d5;
byte KeyboardII::__d6;
byte KeyboardII::__strobe;
byte KeyboardII::__bulb;
		
KeyboardII::KeyboardII(uint8_t D0,uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t STROBE, uint8_t BULB) {
	__d0 = D0;
	__d1 = D1;
	__d2 = D2;
	__d3 = D3;
	__d4 = D4;
	__d5 = D5;
	__d6 = D6;
	__strobe = STROBE;
	__bulb = BULB;
	dataReady = false;
	data = 0;
}

void KeyboardII::init() {
	pinMode(__strobe, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(__strobe), readKeyboardDataInterrupt, RISING );
	pinMode(__d0, INPUT);
	pinMode(__d1, INPUT);
	pinMode(__d2, INPUT);
	pinMode(__d3, INPUT);
	pinMode(__d4, INPUT);
	pinMode(__d5, INPUT);
	pinMode(__d6, INPUT);
	pinMode(__bulb, OUTPUT);
	digitalWrite(__bulb, BULB_OFF);
}

byte KeyboardII::waitForData() {
	while (!dataReady);
	return getData();
}

byte KeyboardII::getData() {
	dataReady = false;
	return data;
}

bool KeyboardII::isDataReady() {
	return dataReady;
}

void KeyboardII::bulbOn() {
	digitalWrite(__bulb, BULB_ON);	
}

void KeyboardII::bulbOff() {
	digitalWrite(__bulb, BULB_OFF);	
}
//keyboard interrupt function
void KeyboardII::readKeyboardDataInterrupt() {
  data = digitalRead (__d0)  
       | digitalRead (__d1) << 1  
       | digitalRead (__d2) << 2
       | digitalRead (__d3) << 3
       | digitalRead (__d4) << 4
       | digitalRead (__d5) << 5
       | digitalRead (__d6) << 6;
  dataReady = true;
}