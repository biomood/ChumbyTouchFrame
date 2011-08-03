#include "touch.h"

char touchstr[] = "/dev/input/event1";
FILE * touchscreen;
int td;
const double touch_threshold = 300000;
struct input_event ev;
struct timeval endTime;
float k, a, b, c, d, e, f;

int init_touchscreen() {
    if ((td = open(touchstr, O_RDWR))>-1){
        gettimeofday(&endTime, NULL);
        return 1;
    }
    else {
        return 0;
    }
}


struct touch_coord get_raw_touch() {    
    long int last_x;
    long int last_y;
    struct input_event t_eve;
    
    // loop over the input queue
    int count = 0;
    while (1) {
        int retval = read(td, &t_eve, sizeof(struct input_event));
        if (retval > -1) {
            count++;
            
            // retrieve the x,y values from the touch
            if (t_eve.type == 3 && t_eve.code == 0) 
                last_x = t_eve.value;
            if (t_eve.type == 3 && t_eve.code == 1) 
                last_y = t_eve.value;
            
            // check if we've found the end of a touch
            if ((t_eve.type == 0) && (t_eve.code == 0)) {
                // call the callback function
                if (count==5) {
                    struct timeval nowTime;
                    gettimeofday(&nowTime, NULL);
                    double tS = nowTime.tv_sec*1000000 + (nowTime.tv_usec);
                    double tE = endTime.tv_sec*1000000  + (endTime.tv_usec);
                    
                    endTime = nowTime;
                    
                    // check if the difference is less than defined time
                    if ((tS-tE) < touch_threshold) {
                        struct touch_coord touch;
                        touch.x = last_x;
                        touch.y = last_y;
                        return touch;
                    }
                }
                count = 0;
            }
        }
    }
}


void calibrate_touch(struct touch_coord t0, struct touch_coord t1, struct touch_coord t2, struct pixel_coord p0, struct pixel_coord p1, struct pixel_coord p2) {
    k = ((t0.x-t2.x)*(t1.y-t2.y))-((t1.x-t2.x)*(t0.y-t2.y));
    a = (((p0.x-p2.x)*(t1.y-t2.y))-((p1.x-p2.x)*(t0.y-t2.y)))/k;
    b = (((t0.x-t2.x)*(p1.x-p2.x)) - ((p0.x-p2.x)*(t1.x-t2.x)))/k;
    c = ((t0.y*((t2.x*p1.x)-(t1.x*p2.x)))+(t1.y*((t0.x*p2.x)-(t2.x*p0.x)))+(t2.y*((t1.x*p0.x)-(t0.x*p1.x))))/k;
    d = (((p0.y-p2.y)*(t1.y-t2.y)) - ((p1.y-p2.y)*(t0.y-t2.y)))/k;
    e = (((t0.x-t2.x)*(p1.y-p2.y)) - ((p0.y-p2.y)*(t1.x-t2.x)))/k;
    f = ((t0.y*((t2.x*p1.y)-(t1.x*p2.y))) + (t1.y*((t0.x*p2.y)-(t2.x*p0.y))) + (t2.y*((t1.x*p0.y)-(t0.x*p1.y))))/k;
    
    printf("k: %f \n", k);
    printf("a: %f \n", a);
    printf("b: %f \n", b);
    printf("c: %f \n", c);
    printf("d: %f \n", d);
    printf("e: %f \n", e);
    printf("f: %f \n", f);
}

struct pixel_coord raw_to_pixel(struct touch_coord touch) {
	struct pixel_coord pixel;
	pixel.x = (int)((a*touch.x)+(b*touch.y)+c);
	pixel.y = (int)((d*touch.x)+(e*touch.y)+f);
	return pixel;
}

void print_event(struct input_event e) {
    printf("Type %ld \n", e.type);
    printf("Code %ld \n", e.code);
    printf("Value %ld \n", e.value);
    printf("\n");
}