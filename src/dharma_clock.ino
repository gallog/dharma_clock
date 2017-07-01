
#include <KeyboardII.h>
#include <UTFT.h>
#include <dht.h>
#include <Wire.h>
#include <RTClib.h>
#include <DFPlayer.h>
#include <AlarmLib.h>

#include "dharma_clock.h"
#include "dharma_clock_lib.h"

//keyboard 
KeyboardII keyboard(A7,A6,A5,A4,A3,A2,A1,18,9);

//screen
UTFT myGLCD(ILI9481,38,39,40,41);

//dht
dht DHT(19);

//rtc
RTC_DS1307 rtc;

//mp3
DFPlayer mp3(Serial2,8);

//alarm
AlarmLib alarml(rtc, mp3);

// TODO da usare serial3 per comunicare con arudino stepper
//Serial 3: 15 (RX) and 14 (TX)

//
// VARIABILI
//

//gestione posizionamento schermo e comandi
int lcdCurrentX = 0;
int lcdCurrentY = 0;
char command[100];
int command_char_index = 0;
boolean clock_mode; //global screen mode

// gestione blinking cursore schermo
unsigned long lastW = millis();
char* currentCH = BLINKING_NOT_CHAR;

void setup()
{
  cli(); //disable int
  
  delay(800);
  
  //keyboard
  keyboard.init();

  //seriale
  Serial.begin(9600);
  Serial2.begin(9600); //DFPlayer

  //DFPlayer
  mp3.init();
  mp3.setVolume(25);

  sei(); //enable

  // rtc
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
     Serial.println("RTC is NOT running!");
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //screen
  myGLCD.InitLCD();
  myGLCD.setFont(BigFont);
  myGLCD.clrScr();
  myGLCD.fillScr(SCREEN_BG_COLOR);
  myGLCD.setBackColor(SCREEN_BG_COLOR);
  myGLCD.setColor(COMMAND_COLOR);
  PRINT_HELLO_STR();
  myGLCD.setColor(INPUT_COLOR);
  PRINTSTARTER();
  clock_mode = false;
}


void loop()
{
    byte data = getInputData();
    if (INPUT_VALID(data)) {
      if (COMMAND_END(data)) {
        command[command_char_index] = 0;
        command_char_index = 0;
        processCommand(command);
      } else {
        if (clock_mode) {
          if (ESCMODE(data)) {
            resetToClassicMode();
          }
        } else {
          if (BACKSPACE(data)) {
            if (command_char_index > 0) {
              --command_char_index;
              outBackspace();
            }
          } else {
            outChar((char)data);
            command[command_char_index++] = (char)data;
          }
        }
      }
   }

   if (!clock_mode) {
      blinkForInput();  
   } else {
      pingClock();
   }
   
   alarml.checkAlarms();

}


void resetToClassicMode() {  
  clock_mode = false;
  lcdCurrentX = 0;
  lcdCurrentY = 0;
  myGLCD.setFont(BigFont);
  myGLCD.setColor(COMMAND_COLOR);
  myGLCD.clrScr();
  myGLCD.setColor(COMMAND_COLOR);
  PRINT_HELLO_STR();
  myGLCD.setColor(INPUT_COLOR);
  PRINTSTARTER();
}


