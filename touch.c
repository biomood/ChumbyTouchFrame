#include "touch.h"

char touchstr[] = "/dev/input/event1";
FILE * touchscreen;
int td;
const double touch_threshold = 300000;
struct input_event ev;
struct timeval endTime;

int init_touchscreen() {
    if ((td = open(touchstr, O_RDWR))>-1){
        gettimeofday(&endTime, NULL);
        return 1;
    }
    else {
        return 0;
    }
}


struct touch_coord get_touch2() {    
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


void calibrate_touch(int x0, int y0, int x1, int y1, int x2, int y2) {
    k = ((x0-x2)*(y1-y2))-((x1-x2)*(y0-y2));
    
}

void print_event(struct input_event e) {
    printf("Type %ld \n", e.type);
    printf("Code %ld \n", e.code);
    printf("Value %ld \n", e.value);
    printf("\n");
}