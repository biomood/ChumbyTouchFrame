#include "touch.h"

int init_touchscreen() {
    if ((td = open(touchstr, O_RDONLY))>-1){
        return 0;
    }
    else {
        return 1;
    }
}