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
extern float k, a, b, c, d, e, f;

const double touch_threshold;

// used as friendly struct for passing around
struct touch_coord {
    long int x;
    long int y;
};

// used as friendly struct for passing around
struct pixel_coord {
	int x;
	int y;
};

// returns true if the touch screen has been initiated
int init_touchscreen();

// waits until a use has entered a touch and returns a struct with x,y
struct touch_coord get_raw_touch();

// call to ignore touches until a user lifts their finger
void ignore_touches();

// print the info about the event
void print_event(struct input_event e);

// print details about the touch
void print_touch(struct touch_coord t);

// works out the variables used for relating touch screen coords to pixel coords
void calibrate_touch(struct touch_coord t0, struct touch_coord t1, struct touch_coord t2, struct pixel_coord p0, struct pixel_coord p1, struct pixel_coord p2);

#endif