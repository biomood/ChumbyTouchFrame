#include <stdio.h>

#include "screen.h"
#include "touch.h"

// calibrates the screen
void calibrate_screen() {
    
}

int main() {
    // attempt to initiate the frame buffer
	if (init_screen()==0) {
        printf("Opened the framebuffer \n");
    }
    else {
        printf("Unable to open frame buffer \n");
        exit(1);
    }
    
    // attempt to initiate the touch screen
    if (init_touchscreen() > -1) {
        printf("Opened the touchscreen \n");
        char name[256] = "Unknown";
        ioctl (td, EVIOCGNAME (sizeof (name)), name);
        printf("Device connected: %s \n", name);
    }
    else {
        printf("Unable to open the touch screen \n");
        exit(1);
    }
    
    // set background to white
	char * colour = rgb_to_byte(255, 0, 255);
	set_colour(colour);
	
	// write array to framebuffer
	set_screen();
    
    
    // calibrate the screen
    calibrate_screen();
    
    // clean up
	fclose(frame);
    if (close(td) == -1) {
        printf("Unable to close the touch screen file \n");
    }
} 