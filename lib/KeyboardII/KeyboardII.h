#ifndef keyboardii_h
#define keyboardii_h

#include <Arduino.h>

#define BULB_ON LOW
#define BULB_OFF HIGH

class KeyboardII 
{
	public:
		KeyboardII(byte D0,byte D1, byte D2, byte D3, byte D4, byte D5, byte D6, byte strobe, byte bulb);
		void init();
		bool isDataReady();
		byte getData();
		void bulbOn();
		void bulbOff();
		byte waitForData(); //aspetta solo un byte, 
		//TODO fare funzioni fighe per lettura stringhe
	
	private:
		static void readKeyboardDataInterrupt();
		static byte data, dataReady;
		static byte __d0,__d1,__d2,__d3,__d4,__d5,__d6,__strobe,__bulb;
};
#endif