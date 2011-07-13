#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>

char touchstr[] = "/dev/input/event1";
FILE * touchscreen;
int td;
struct input_event ev;

// initiates the touch screen
int init_touchscreen();

