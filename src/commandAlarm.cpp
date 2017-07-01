#include "commandAlarm.h"


boolean getAlarm(char *str, int &h, int &m);

//TODO help
int alarm(char *argc[], int argv) {
	if (argv == 0) {
		TEXT_VIDEO_MEMORY[0] = "Use alarm help";
		return 1;
	}
  if (!strcmp("help",argc[0])) {
      TEXT_VIDEO_MEMORY[0] = "alarm set <hh:mm> [1-4]";
      TEXT_VIDEO_MEMORY[1] = "alarm list";
      TEXT_VIDEO_MEMORY[2] = "alarm remove [id]";
      return 3;    
  }
	if (!strcmp("set",argc[0])) {
		if (argv != 3) {
			TEXT_VIDEO_MEMORY[0] = "Use alarm set <hh:mm> [1-4]";
			return 1;
		}
    int h,m,s;
    if (!getAlarm(argc[1], h, m)) {
      TEXT_VIDEO_MEMORY[0] = "Invalid time, use hh:mm";
      return 1;      
    }
    s = atoi(argc[2]);
    if (s < 1 || s > 4) {
      TEXT_VIDEO_MEMORY[0] = "Invalid song, use [1-4]";
      return 1;      
    }
    if (alarml.setAlarm(h,m,s)) {
      TEXT_VIDEO_MEMORY[0] = "Alarm set "+ String(h) +":" + String(m) + ", song: "+ String(s);
      return 1;
    }
    TEXT_VIDEO_MEMORY[0] = "Alarm already exists";
    return 1;   
	} 
	if (!strcmp("list",argc[0])) {
		int n = alarml.getAlarmN();
    int m,h,s,i;
    TEXT_VIDEO_MEMORY[0] = "Alarms:";
		for (i = 0; i < n; i++) {
      alarml.getAlarm(i,h,m,s);
			TEXT_VIDEO_MEMORY[i+1] = " id:" + String(i+1) + ", at " +String(h)+":"+String(m)+", song:"+String(s);
		}
		return i+1;
	}
	if (!strcmp("remove",argc[0])) {
		if (argv != 2) {
		  TEXT_VIDEO_MEMORY[0] = "Use alarm remove [id]";
		  return 1;
		}
		int id = atoi(argc[1]) -1;
		if (alarml.removeAlarm(id)) {
		  TEXT_VIDEO_MEMORY[0] = "Removed alarm "+String(id+1);
		  return 1;      
		}    
		TEXT_VIDEO_MEMORY[0] = "Invalid id: "+String(argc[1]);
		return 1;
	}
	TEXT_VIDEO_MEMORY[0] = "alarm unknow args";
	return 1;
}

boolean getAlarm(char *str, int &h, int &m) { //str=hh:mm
  if (strlen(str) != 5 || str[2] != ':') {
    return false;
  }
  int ih = (str[0] - '0') * 10 + (str[1] - '0');
  int im = (str[3] - '0') * 10 + (str[4] - '0');

  if (ih > 23) {
    return false;
  }
  if (im > 60) {
    return false;
  }
  m = im;
  h = ih;
  return true;
  
}

