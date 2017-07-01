#ifndef dharma_clock_h
#define dharma_clock_h

//macro
#define INVALID_VALUE 255
#define INPUT_VALID(a) a != INVALID_VALUE 
#define COMMAND_END(a) a == 13
#define BACKSPACE(a) a == 5
#define CHAR_LCD_SPACER 16
#define ESCMODE(a) a == 27
#define MAX_LCD_LINES CHAR_LCD_SPACER*18
#define SCREEN_BG_COLOR VGA_BLACK
#define INPUT_COLOR 0,255,0
#define COMMAND_COLOR 0,180,0
//uso un carattere che viene stampato come quadrato pieno
#define BLINKING_CHAR "\\"
#define BLINKING_NOT_CHAR " "
#define BLINKING_CHAR_DELAY_MS 500
#define HELLO_STR_1 "GOS [Version 0.4.1]"
#define HELLO_STR_2 "  Copyright (c) 2016 GG"
#define LINE_STARTER_STRING ":>"

#endif

/*
 * CHANGELOG:
 * v 0.1 (03/11/2016) - Versione iniziale
 * v 0.2 (06/11/2016) - Aggiunto support DFPlayer
 * v 0.3 (13/11/2016) - Rifattorizzato comandi su file diversi, introdotto TEXT_VIDEO_MEMORY, introdotto AlarmLib
 * v 0.4 (20/11/2016) - Clockmode
 * v 0.4.1 (03/11/2016) - Aggiunto font per data/ora temp/hum in clockmode e aggiunte info sul display
 */

