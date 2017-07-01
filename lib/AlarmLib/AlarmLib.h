#ifndef alarmlib_h
#define alarmlib_h

#include <Arduino.h>
#include <DFPlayer.h>
#include <RTClib.h>
#include <EEPROM.h>

#define MAX_ALARMS 10
#define EEPROM_ADD 0xfe

class AlarmTime {
	public:
		AlarmTime() { _running = false; _hour = 255; _min = 255; _songId = 255; }
		AlarmTime(int hour, int min, int songId) { _running = false; _hour = hour; _min = min; _songId = songId; }
		int getMin() { return _min; }
		int getHour() { return _hour; }
		int getSong() { return _songId; }
		void setRunning(boolean running) { _running = running; }
		boolean isRunning() { return _running; }
		
	private:
		int _hour;
		int _min;
		int _songId;
		boolean _running;
};

class AlarmLib 
{
	public:
		AlarmLib(RTC_DS1307 &rtc, DFPlayer &player);
		boolean setAlarm(int hour, int min, int songId);
		boolean removeAlarm(int id);
		void getAlarm(int id, int &h, int&m, int&s);
		int getAlarmN();
		boolean checkAlarms();
		
	private:
		static RTC_DS1307 *_rtc;
		static DFPlayer *_player;
		AlarmTime _alarms[MAX_ALARMS]; //TODO va in eeprom
		int _alarmsN;
		void updateEEPROM();
		void getEEPROM();
};

#endif