#ifndef TOUCH_H
#define TOUCH_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <time.h>

extern char touchstr[];
extern FILE * touchscreen;
extern int td;
extern struct input_event ev;
extern clock_t now, last, diff;

// touch screen variables
int k, a, b, c, d, e, f;

const double touch_threshold;

// used as friendly object to return
struct touch_coord {
    long int x;
    long int y;
};


// returns true if the touch screen has been initiated
int init_touchscreen();

// waits until a use has entered a touch and returns a struct with x,y
struct touch_coord get_touch2();

// call to ignore touches until a user lifts their finger
void ignore_touches();

// print the info about the event
void print_event(struct input_event e);

// print details about the touch
void print_touch(struct touch_coord t);

// works out the variables used for relating touch screen coords to pixel coords
void calibrate_touch(int x0, int y0, int x1, int y1, int x2, int y2);

#endif