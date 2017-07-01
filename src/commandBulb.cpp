#include "commandBulb.h"

//TODO help
int bulb(char *argc[], int argv) {
	if (argv != 1) {
		TEXT_VIDEO_MEMORY[0] = "Use bulb help";
		return 1;
	}
	if (!strcmp("on",argc[0])) {
		keyboard.bulbOn();
		TEXT_VIDEO_MEMORY[0] = "Bulb is now on";
		return 1;
	} else if (!strcmp("off",argc[0])) {
		keyboard.bulbOff();
		TEXT_VIDEO_MEMORY[0] = "Bulb is now off";
		return 1;
	}
	TEXT_VIDEO_MEMORY[0] = "Bulb unknow args";
	return 1;
}
