#ifndef TOUCH_H
#define TOUCH_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>

extern char touchstr[];
extern FILE * touchscreen;
extern int td;
extern struct input_event ev;

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

// call to ignore touches until a user lifts their finger
void ignore_touches();

// print the info about the event
void print_event(struct input_event e);

// print details about the touch
void print_touch(struct touch_coord t);

#endif