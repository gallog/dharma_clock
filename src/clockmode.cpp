#include "clockmode.h"

#define normalSpacing 96
#define normalSpacingH 144
#define dotSpacing 74 // risparmio 96-76=20, 10 per lato, clockStartX
#define clockStartX normalSpacing-dotSpacing
#define xx clockStartX
#define BLINKING_DOTS_DELAY_MS 1000
#define READ_TEMP_HUM_DELAY 2650 //almeno 1secondo con dht11 (messo spaiato cosi non si aggiorna col lampeggio dei puntini)
#define OFFSET_ASSOLUTO_VERTICALE 40 //metterlo ad esempio a 5 per avere spazio sotto per la combinazione lost

char daysOfTheWeek[7][4] = {"Dom", "Lun", "Mar", "Mer", "Gio", "Ven", "Sab"};
char monthOfYear[12][4] = {"Gen", "Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
int last_h0;
int last_h1;
int last_m0;
int last_m1;
int last_dd;
int last_ee;
int last_yy;
double last_t, last_h;
unsigned long lastDotted;
unsigned long lastTempHum;
boolean currentDotVisible;

boolean toggleDots() {
  unsigned long currentW = millis();
  if (currentW - lastDotted > BLINKING_DOTS_DELAY_MS) {
    lastDotted = currentW;
    return true;
  }
  return false;
}

boolean leggiTempHum() {
  unsigned long currentW = millis();
  if (currentW - lastTempHum > READ_TEMP_HUM_DELAY) {
    lastTempHum = currentW;
    return true;
  }
  return false;
}

void printTime() {
	DateTime now = rtc.now();
	
	int current_h0;
	int current_h1;
	int current_m0;
	int current_m1;
	int current_dd;
	int current_ee;
	int current_yy;
  double current_t, current_h;

	int gh = now.hour();
	if (gh <= 9) {
		current_h0 = 0;
	} else {
		current_h0 = gh/10;
	}
	current_h1 = gh % 10;
	
	int gm = now.minute();
	if (gm <= 9) {
		current_m0 = 0;
	} else {
		current_m0 = gm/10;
	}
	current_m1 = gm % 10;

  current_dd = now.day(); 
  current_ee = now.month();
  current_yy = now.year();
  
	//-------------------------------data
	if (current_dd != last_dd || current_ee != last_ee || current_yy != last_yy) {
    last_dd = current_dd;
    last_ee = current_ee;
    last_yy = current_yy;
		myGLCD.setColor(COMMAND_COLOR);
		myGLCD.setFont(Grotesk16x32);  
    char t[18]; //18
    sprintf(t,"%s %02u, %s %04u",daysOfTheWeek[now.dayOfTheWeek()],last_dd,monthOfYear[last_ee-1],last_yy);
		myGLCD.print(String(t), 114, OFFSET_ASSOLUTO_VERTICALE);
	}
	
	//-------------------------------tempo
    //ora  
	if (current_h0 != last_h0) {
		myGLCD.setColor(INPUT_COLOR);
		myGLCD.setFont(SevenSegment96x144Num);  
		myGLCD.print(String(current_h0), clockStartX, OFFSET_ASSOLUTO_VERTICALE+40);
		last_h0 = current_h0;
	}
	if (current_h1 != last_h1) {
		myGLCD.setColor(INPUT_COLOR);
		myGLCD.setFont(SevenSegment96x144Num);  
		myGLCD.print(String(current_h1), clockStartX+normalSpacing, OFFSET_ASSOLUTO_VERTICALE+40);
		last_h1 = current_h1;
	}
	
	//min
	if (current_m0 != last_m0) {
		myGLCD.setColor(INPUT_COLOR);
		myGLCD.setFont(SevenSegment96x144Num);  
		myGLCD.print(String(current_m0), clockStartX+normalSpacing+dotSpacing*2, OFFSET_ASSOLUTO_VERTICALE+40);
		last_m0 = current_m0;
	}
	if (current_m1 != last_m1) {
		myGLCD.setColor(INPUT_COLOR);
		myGLCD.setFont(SevenSegment96x144Num);  
		myGLCD.print(String(current_m1), clockStartX+normalSpacing*2+dotSpacing*2, OFFSET_ASSOLUTO_VERTICALE+40);
		last_m1 = current_m1;
	}

	//puntini
	if (toggleDots()) {
		if (currentDotVisible) {
			currentDotVisible = false;
			myGLCD.setColor(SCREEN_BG_COLOR);
		} else {
			currentDotVisible = true;
			myGLCD.setColor(INPUT_COLOR);
		}
		myGLCD.setFont(SevenSegment96x144Num);  
		myGLCD.fillCircle(normalSpacing*2+dotSpacing/2 +10, OFFSET_ASSOLUTO_VERTICALE+40 + normalSpacingH/2 -20, 7); //20 offset verticale rispetto al centro
		myGLCD.fillCircle(normalSpacing*2+dotSpacing/2 +10, OFFSET_ASSOLUTO_VERTICALE+40 + normalSpacingH/2 +20, 7); //20 offset verticale rispetto al centro
	}

  //-----temperatura e umidita
    if (leggiTempHum()) {
		int chk = DHT.read11();
		if (chk == DHTLIB_OK) {
			current_t = DHT.temperature;
			current_h = DHT.humidity;      
			if (current_t != last_t) {
				last_t = current_t;
				myGLCD.setColor(COMMAND_COLOR);
				myGLCD.setFont(Grotesk16x32);  
				myGLCD.print(String(((int)last_t))+".0 C", 40, OFFSET_ASSOLUTO_VERTICALE+384);
			}
			if (current_h != last_h) {
				last_h = current_h;
				myGLCD.setColor(COMMAND_COLOR);
				myGLCD.setFont(Grotesk16x32);  
				myGLCD.print(String(((int)last_h))+".0 %", 355, OFFSET_ASSOLUTO_VERTICALE+384);
			}
		}
    }
}

int clockmode(char *argc[], int argv) {
	
	clock_mode = true;
	myGLCD.clrScr();
  
	last_h0 = -1;
	last_h1 = -1;
	last_m0 = -1;
	last_m1 = -1;
    last_dd = -1;
    last_ee = -1;
    last_yy = -1;
	lastDotted = 0;
    lastTempHum = 0;
    last_t = -1;
    last_h -1;
	currentDotVisible = false;
	
	printTime();

	return -1;
}

void pingClock() {
	printTime();
}
