#ifndef dharma_clock_lib_h
#define dharma_clock_lib_h

#include <Arduino.h>
#include "dharma_clock.h"
#include <KeyboardII.h>
#include <UTFT.h>
#include <dht.h>
#include <Wire.h>
#include <RTClib.h>
#include <DFPlayer.h>
#include <AlarmLib.h>

//comandi
#include "commandTemp.h"
#include "commandHum.h"
#include "commandBulb.h"
#include "commandTime.h"
#include "commandDate.h"
#include "commandMusic.h"
#include "commandRTCSet.h"
#include "commandAlarm.h"
#include "clockmode.h"


void CLEARBLINKCHAR();
void PRINT_HELLO_STR();
void PRINTSTARTER();
void resetToClassicMode();

byte getInputData();
void outChar(char);
void outData(int size);
void outBackspace();
void blinkForInput();
void processCommand(char*);


int cmdlist();
int exec(char *command, char *argc[], int argv);
//Periferiche
extern KeyboardII keyboard;
extern dht DHT;
extern RTC_DS1307 rtc;
extern UTFT myGLCD;
extern DFPlayer mp3;
extern AlarmLib alarml;

//Variabili
extern int lcdCurrentX;
extern int lcdCurrentY;
extern char command[100];
extern int command_char_index;
extern unsigned long lastW;
extern char* currentCH;
extern String TEXT_VIDEO_MEMORY[20];

//Schermo
extern uint8_t BigFont[];
extern uint8_t SevenSegment96x144Num[];
extern uint8_t Grotesk16x32[];
extern boolean clock_mode;

#endif
