#include "DFPlayer.h"

HardwareSerial *DFPlayer::_serial;
byte DFPlayer::_busy;
		
DFPlayer::DFPlayer(HardwareSerial &serial, byte busy) {
	_serial = &serial;
	_busy = busy;
}

void DFPlayer::init() {
	mp3_set_serial (*_serial);
	pinMode(_busy,INPUT);
}

void DFPlayer::setVolume(uint16_t v) {
	mp3_set_volume(v);          // value 0~30
}
void DFPlayer::play(uint16_t n) {
	mp3_play(n);
}
void DFPlayer::play() {
	mp3_play();
}
void DFPlayer::sleep () {
	mp3_sleep();
} 
void DFPlayer::reset() {
	mp3_reset();
}
void DFPlayer::pause () {
	mp3_pause();
} 
void DFPlayer::stop() {
	mp3_stop();	
}
boolean DFPlayer::isPlaying() {
	return digitalRead(_busy) == LOW;
}