#ifndef TOUCH_H
#define TOUCH_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>

char touchstr[] = "/dev/input/event1";
FILE * touchscreen;
int td;
struct input_event ev;

// used as friendly object to return
struct touch_coord {
    long int x;
    long int y;
    long int pressure;
};


// returns true if the touch screen has been initiated
int init_touchscreen();

// waits until the user has entered a touch and fills pointer
struct touch_coord * get_touch();

#endif