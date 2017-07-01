#include "commandMusic.h"

//TODO help
int music(char *argc[], int argv) {
  if (argv == 0) {
    TEXT_VIDEO_MEMORY[0] = "Use music help";
    return 1;
  }
  if (!strcmp("help",argc[0])) {
      TEXT_VIDEO_MEMORY[0] = "music play [1-4]";
      TEXT_VIDEO_MEMORY[1] = "music pause";
      TEXT_VIDEO_MEMORY[2] = "music resume";
      TEXT_VIDEO_MEMORY[3] = "music stop";
      TEXT_VIDEO_MEMORY[4] = "music status";
      TEXT_VIDEO_MEMORY[5] = "music volume [1-30]";
      return 6;    
  }
  char *cmd = argc[0];
  if (!strcmp("play",cmd)) {
    if (argv != 2) {
      TEXT_VIDEO_MEMORY[0] = "Use: music play #";
      return 1;      
    }
    int musicId = atoi(argc[1]);
    if (musicId == 0) {
      TEXT_VIDEO_MEMORY[0] = "Invalid music: #"+ String(musicId);
      return 1;      
    }
    if (mp3.isPlaying()) {
      mp3.stop();
      delay(1);
    }
    mp3.play (musicId);
    TEXT_VIDEO_MEMORY[0] = "Playing song #"+ String(musicId);
    return 1;
  } 
  
  if (!strcmp("status",cmd)) {
    if (mp3.isPlaying()) {
      TEXT_VIDEO_MEMORY[0] =  "Play";
      return 1;
    }
    TEXT_VIDEO_MEMORY[0] = "Idle";
    return 1;
  }
  if (!strcmp("pause",cmd)) {
    mp3.pause();
    TEXT_VIDEO_MEMORY[0] = "Now Pause";
    return 1;
  }
  if (!strcmp("stop",cmd)) {
    mp3.stop();
    TEXT_VIDEO_MEMORY[0] = "Music stopped";
    return 1;
  }
  if (!strcmp("resume",cmd)) {
    if (mp3.isPlaying()) {
      TEXT_VIDEO_MEMORY[0] = "Already running";
      return 1;
    }
    mp3.play();
    TEXT_VIDEO_MEMORY[0] = "Now Playing";
    return 1;
  }
  if (!strcmp("volume",cmd)) {
    if (argv != 2) {
      TEXT_VIDEO_MEMORY[0] = "Use: music volume [0-30]";
      return 1;      
    }
    int vol = atoi(argc[1]);
    if (vol < 0 || vol > 30) {
      TEXT_VIDEO_MEMORY[0] = "Volume out of range [0-30]";
      return 1;           
    }
    mp3.setVolume(vol);
    TEXT_VIDEO_MEMORY[0] = "Volume set to "+ String(vol);
    return 1;
  }
  TEXT_VIDEO_MEMORY[0] = "Unkonw argument: "+String(cmd);
  return 1;
}
