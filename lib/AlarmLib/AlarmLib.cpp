#include "AlarmLib.h"

RTC_DS1307 *AlarmLib::_rtc;
DFPlayer *AlarmLib::_player;

AlarmLib::AlarmLib(RTC_DS1307 &rtc, DFPlayer &player) {
	_rtc = &rtc;
	_player = &player;
	getEEPROM();
}

void AlarmLib::updateEEPROM() {
	int addr = EEPROM_ADD;
	EEPROM.put(addr,_alarmsN);
	addr += sizeof(int);
	for (int i = 0; i < _alarmsN; i++) {
		EEPROM.put(addr,_alarms[i]);
		addr += sizeof(AlarmTime);
	}
}
void AlarmLib::getEEPROM() {
	int addr = EEPROM_ADD;
	EEPROM.get(addr,_alarmsN);
	addr += sizeof(int);
	for (int i = 0; i < _alarmsN; i++) {
		EEPROM.get(addr,_alarms[i]);
		addr += sizeof(AlarmTime);
	}
}

boolean AlarmLib::setAlarm(int hour, int min, int songId) {
	if (_alarmsN == MAX_ALARMS-1) {
		return false;
	}
	if (hour < 0 || hour > 23 || min < 0 || min > 60) {
		return false;
	}
	for (int i = 0; i < _alarmsN; i++) {
		if (_alarms[i].getHour() == hour && _alarms[i].getMin() == min) {
			return false;
		}
	}
	AlarmTime al = AlarmTime(hour,min,songId);
	_alarms[_alarmsN++] = al;
	updateEEPROM();
	return true;
}

boolean AlarmLib::removeAlarm(int id) {
	if (id >= _alarmsN) {
		return false;
	}
	for (int i = id+1; i < _alarmsN; i++) {		
		_alarms[i-1] = _alarms[i];
	}
	_alarmsN--;
	updateEEPROM();
	return true;
}

void AlarmLib::getAlarm(int id, int &h, int &m, int &s) {
	if (id >= _alarmsN) {
		return;
	}
	h = _alarms[id].getHour();
	m = _alarms[id].getMin();
	s = _alarms[id].getSong();
}

int AlarmLib::getAlarmN() { return _alarmsN; };

boolean AlarmLib::checkAlarms() {
	if (_alarmsN == 0) {
		return false;
	}
	DateTime now = _rtc->now();
	boolean running = false;
	for (int i = 0; i < _alarmsN; i++) {
		if (!_alarms[i].isRunning()) {
			if (now.hour() == _alarms[i].getHour() && now.minute() == _alarms[i].getMin() && now.second() == 0) {
				_player->play(_alarms[i].getSong());
				_alarms[i].setRunning(true);
				running |= true;
			}
		} else if (now.second() != 0) { //sono sicuro che non riparta subito, visto che il check scatta piu di una volta al sec
			_alarms[i].setRunning(false);
		}
	}	
	return running;	
}