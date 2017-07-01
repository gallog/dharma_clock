#include "commandTime.h"

char time_ret_str[23]; //"Current time: "+9  

//TODO help
int time(char *argc[], int argv) {
    DateTime now = rtc.now();
    sprintf(time_ret_str, "Current time: %02u:%02u:%02u", now.hour(),now.minute(),now.second());
    TEXT_VIDEO_MEMORY[0] = time_ret_str;
    return 1;
}
