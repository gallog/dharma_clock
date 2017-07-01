#ifndef dfplayer_h
#define dfplayer_h

#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>

class DFPlayer 
{
	public:
		DFPlayer(HardwareSerial &serial, byte busy);
		void init();
		void play(uint16_t n);
		void play();
		void sleep(); 
		void reset(); 
		void pause(); 
		void stop();
		void setVolume(uint16_t v);
		boolean isPlaying();

	private:
		static HardwareSerial *_serial;
		static byte _busy;
};
#endif