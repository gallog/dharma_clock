#include "dharma_clock_lib.h"

String TEXT_VIDEO_MEMORY[20];

byte getInputData() {      
    byte data = INVALID_VALUE;    
    if (keyboard.isDataReady()) {
      data = keyboard.getData();
    }
    if (Serial.available() > 0) {
      data = Serial.read();
    }
    return data;
}

void blinkForInput() {
  unsigned long currentW = millis();
  if (currentW - lastW > BLINKING_CHAR_DELAY_MS) {
    lastW = currentW;
    if (currentCH == BLINKING_NOT_CHAR) {
      currentCH = BLINKING_CHAR;
    } else {
      currentCH = BLINKING_NOT_CHAR;
    }
    myGLCD.print(currentCH,lcdCurrentX,lcdCurrentY);  
  }
}

void processCommand(char* command) {

    //parse command args
    char *argc[10];
    char *r = command;    
    char *c = strtok_r(r, " ", &r); //comando
    uint8_t argv = 0;
    while((argc[argv++] = strtok_r(r, " ", &r))); //argomenti
    
    int retSize = exec(c, argc, argv-1);
    if (retSize == 0) {
      TEXT_VIDEO_MEMORY[0] = "Unknow, use cmdlist for help";
      retSize++;
    }
    outData(retSize);
}

void outData(int size) {
   if (size < 0) {
    return;
   }
   CLEARBLINKCHAR();
   
   myGLCD.setColor(COMMAND_COLOR);
   
   for (uint8_t i = 0; i < size; i++) {   
     lcdCurrentX = CHAR_LCD_SPACER; //la risposta parte sempre con uno spazio bianco
     lcdCurrentY += CHAR_LCD_SPACER;
     Serial.print("\r\n "); 
     Serial.print(TEXT_VIDEO_MEMORY[i]); 
     
     myGLCD.print(TEXT_VIDEO_MEMORY[i],lcdCurrentX,lcdCurrentY); 
     if (lcdCurrentY > MAX_LCD_LINES) { // e' un numero pari, quindi pu� succedere solo dopo la risposta ad un comando
        delay(1000); //porcheria per far leggere l'ultima riga, da sistemare
        lcdCurrentY = 0;
        myGLCD.clrScr();
     }
   }
   lcdCurrentX = 0;   
   lcdCurrentY += CHAR_LCD_SPACER; 
   Serial.print("\r\n");
   
   myGLCD.setColor(INPUT_COLOR);
   PRINTSTARTER();
}

void outChar(char data) {
  char dataOut[2];
  dataOut[0] = data;
  dataOut[1] = 0;   
  
  Serial.print(data); 
  
  myGLCD.setColor(INPUT_COLOR);
  myGLCD.print(dataOut,lcdCurrentX,lcdCurrentY);    
  lcdCurrentX+=CHAR_LCD_SPACER;
}

void outBackspace() {
  //solo da lcd
  char *dataOut = " ";    
  CLEARBLINKCHAR();
  lcdCurrentX-=CHAR_LCD_SPACER;
  myGLCD.setColor(INPUT_COLOR);
  myGLCD.print(dataOut,lcdCurrentX,lcdCurrentY);  
}


//quando sposto il cursore non avanti (indietro o sotto) c'e' il 50% di probabilita' di essere nella fase BLINKING_CHAR
//quindi occorre ripulire per evitare di lasciare stampato

void CLEARBLINKCHAR() {
  if (currentCH == BLINKING_CHAR) {
      currentCH = BLINKING_NOT_CHAR;
      myGLCD.print(currentCH,lcdCurrentX,lcdCurrentY);
  }
}

void PRINT_HELLO_STR() {
  myGLCD.print(String(HELLO_STR_1),lcdCurrentX,lcdCurrentY);
  lcdCurrentY += CHAR_LCD_SPACER;
  myGLCD.print(String(HELLO_STR_2),lcdCurrentX,lcdCurrentY);
  lcdCurrentY += CHAR_LCD_SPACER*2;
  Serial.println(HELLO_STR_1);
  Serial.println(HELLO_STR_2);
  Serial.println();
}

void PRINTSTARTER() {
  myGLCD.print(String(LINE_STARTER_STRING),lcdCurrentX,lcdCurrentY);
  for (byte i = 0; LINE_STARTER_STRING[i] != 0; i++) {
       lcdCurrentX += CHAR_LCD_SPACER;
  }
  Serial.print(LINE_STARTER_STRING);
}

//
// DISPATCH COMANDI
//
int exec(char* com, char *argc[], int argv) {
  if (!strcmp(com,"cmdlist")) { return cmdlist();              } 
  if (!strcmp(com,"clock"))   { return clockmode(argc, argv);  } 
  if (!strcmp(com,"temp"))    { return temp(argc, argv);       } 
  if (!strcmp(com,"hum"))     { return hum(argc, argv);        }
  if (!strcmp(com,"time"))    { return time(argc, argv);       } 
  if (!strcmp(com,"date"))    { return date(argc, argv);       } 
  if (!strcmp(com,"bulb"))    { return bulb(argc, argv);       }
  if (!strcmp(com,"music"))   { return music(argc, argv);      } 
  if (!strcmp(com,"rtcset"))  { return rtcset(argc, argv);     }
  if (!strcmp(com,"alarm"))   { return alarm(argc, argv);      }
  return 0;
}

  
int cmdlist() {
   TEXT_VIDEO_MEMORY[0] = "Available commands:";
   TEXT_VIDEO_MEMORY[1] = "  clock: clock mode";
   TEXT_VIDEO_MEMORY[2] = "  temp: room temperature";
   TEXT_VIDEO_MEMORY[3] = "  hum: room humidity";
   TEXT_VIDEO_MEMORY[4] = "  time: current time",
   TEXT_VIDEO_MEMORY[5] = "  rtcset: set date/time";
   TEXT_VIDEO_MEMORY[6] = "  date: current date";
   TEXT_VIDEO_MEMORY[7] = "  bulb: turn on/off lamp";
   TEXT_VIDEO_MEMORY[8] = "  music: play song";
   TEXT_VIDEO_MEMORY[9] = "  alarm: set alarm";
   return 10;
}

