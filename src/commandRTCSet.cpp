#include "commandRTCSet.h"


boolean isTimeValid(const char*t) { //format hh:mm:ss
  for (uint8_t i = 0; t[i] != 0; i++) {
    if (i > 7) {
      return false;
    }
    if (i == 2 || i == 5) {
      if (t[i] != ':') {
        return false;
      }
    } else {
      if ('0' > t[i] || t[i] > '9') {
        return false;
      }
    }
  }
  return true;
}

boolean isDateValid(const char*d) { //format dd/mm/yyyy
    for (uint8_t i = 0; d[i] != 0; i++) {
    if (i > 9) {
      return false;
    }
    if (i == 2 || i == 5) {
      if (d[i] != '/') {
        return false;
      }
    } else {
      if ('0' > d[i] || d[i] > '9') {
        return false;
      }
    }
  }
  return true;
}

static uint8_t conv2d(const char* p) {
    uint8_t v = *p - '0';
    return 10 * v + *++p - '0';
}

static uint16_t conv4d(const char* p) {
    uint16_t v = 1000 * (*p - '0');
    v += 100 * (*++p - '0');
    v += 10 * (*++p - '0');
    v += (*++p - '0');
    return v;
}

uint16_t dateGetYear(const char*date) {
  return conv4d(date+6);  
}
uint8_t dateGetMonth(const char*date) {
  return conv2d(date+3);  
}
uint8_t dateGetDay(const char*date) {
  return conv2d(date);
}

//TODO help
int rtcset(char *argc[], int argv) {
  if (argv != 2) {
    TEXT_VIDEO_MEMORY[0] = "Use rtcset help";
    return 1;
  }  
  if (!strcmp("help",argc[0])) {
      TEXT_VIDEO_MEMORY[0] = "rtcset time hh:mm";
      TEXT_VIDEO_MEMORY[1] = "rtcset date dd/mm/yyyy";
      return 2;    
  }
  char *cmd = argc[0];
  char *arg = argc[1];
   if (!strcmp("time",cmd)) {
      if (!isTimeValid(arg)) {
        TEXT_VIDEO_MEMORY[0] = "Time not valid: " + String(arg);
        return 1;
      }
      DateTime toSet = DateTime(rtc.now(),arg);
      rtc.adjust(toSet);
      TEXT_VIDEO_MEMORY[0] = "Time set to: " + String(arg);
      return 1;
   }
   if (!strcmp("date",cmd)) {
      if (!isDateValid(arg)) {
        TEXT_VIDEO_MEMORY[0] = "Date not valid: " + String(arg);
        return 1;
      }
      DateTime now = rtc.now();      
      DateTime toSet = DateTime(dateGetYear(arg), dateGetMonth(arg),dateGetDay(arg), now.hour(),now.minute(),now.second());
      rtc.adjust(toSet);
      TEXT_VIDEO_MEMORY[0] = "Date set to: " +String(arg);
      return 1;
   }
   TEXT_VIDEO_MEMORY[0] = "Unkonw arg: " + String(cmd);
   return 1;
}
