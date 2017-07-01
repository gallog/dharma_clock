#include "commandDate.h"

char date_ret_str[23]; //"Current date: "+9

//TODO help
int date(char *argc[], int argv) {
    //char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    DateTime now = rtc.now();
    sprintf(date_ret_str,"Current date: %02u/%02u/%04u",now.day(),now.month(),now.year());
    TEXT_VIDEO_MEMORY[0] = date_ret_str;
    return 1;
}
