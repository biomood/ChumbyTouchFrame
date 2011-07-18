#include "touch.h"

char touchstr[] = "/dev/input/event1";
FILE * touchscreen;
int td;
struct input_event ev;

int init_touchscreen() {
    if ((td = open(touchstr, O_RDONLY))>-1){
        return 1;
    }
    else {
        return 0;
    }
}

struct touch_coord * get_touch() {
    int found = 0;
    
    struct input_event * eventlist = calloc(5, sizeof(struct input_event));
    int count = 0;
    
    // attempt to retrieve a full set of touch coordinates
    while (1) {        
        int retval = read(td, &ev, sizeof(struct input_event));
        
        if (retval > 0) {
            if (count <5) {
                eventlist[count] = ev;
            
                if (ev.type == 0) {
                    break;
                }
            
                count++;
            }
        }
    }
    
    // check that we have a full touch event
    // return with NULL if we haven't
    int i;
    for(i=0; i<5; i++) {
        if ((eventlist[i].value==0)&&(eventlist[i].type==0)&&(eventlist[i].code==0)) {
            return NULL;
        }
    }
    
    // set the coords for the touch
    struct touch_coord * c;
    c->x = eventlist[0].value; // x
    c->y = eventlist[1].value; // y
    c->pressure = eventlist[2].value; // pressure
    
    return c;
}

void ignore_touches() {
    struct input_event e;
    int val;
    int done = 0;
    
    while (!done) {
        val = read(td, &e, sizeof(struct input_event));
        if (val <=0) {
            done = 1;
        }
    }
}

void print_event(struct input_event e) {
    printf("Type %ld \n", e.type);
    printf("Code %ld \n", e.code);
    printf("Value %ld \n", e.value);
    printf("\n");
}