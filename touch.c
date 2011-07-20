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
    init_touchscreen();
    
    struct input_event eve;
    struct input_event event_arr[5];
    
    // read 5 structs from the touch screen
    int count = 0;
    while (1) {
        int retval = read(td, &eve, sizeof(struct input_event));
        if (retval > -1) {
            if (count < 5) {
                event_arr[count] = eve;
            }
            else {
                close(td);
                printf("broke \n");
                break;
            }
            count++;
            
        }
    }
    
    
    // set the coords for the touch
    struct touch_coord * c = (struct touch_coord *)malloc(sizeof(struct touch_coord));
    c->x = event_arr[1].value; // x
    c->y = event_arr[2].value; // y
    c->pressure = event_arr[3].value; // pressure
    
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

void print_touch(struct touch_coord t) {
    printf("x: %ld \n", t.x);
    printf("y: %ld \n", t.y);
    printf("pressure: %ld \n", t.pressure);
}