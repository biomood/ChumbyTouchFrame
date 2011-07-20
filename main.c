#include <stdio.h>

#include "screen.h"
#include "touch.h"

void calibrate_screen();
void draw_cursor(int x, int y);

// calibrates the screen
void calibrate_screen() {
    char * colour = rgb_to_byte(255, 255, 255);
    
    // attempt to retrieve 1st touch
    draw_cursor(40, 40);
    draw_circle(40, 40, 10, colour);
    set_screen();
    struct touch_coord * t1 = get_touch();
    print_touch(*t1);
    set_colour(colour);
    
    // attempt to retrieve 2nd touch
    draw_cursor(160, 150);
    draw_circle(160, 150, 10, colour);
    set_screen();
    struct touch_coord * t2 = get_touch();
    print_touch(*t2);
    set_colour(colour);
    
    // attempt to retrieve 3rd touch
    draw_cursor(280, 200);
    draw_circle(280, 200, 10, colour);
    set_screen();
    struct touch_coord * t3 = get_touch();
    print_touch(*t3);
    set_colour(colour);
    
    // return if we don't have 3 complete touches
    if (!(t1 && t2 && t3)) {
        printf("Unable to retrieve coordinates \n");
        exit(0);
    }
    
    
}

// draws a cursor to the screen with origin at x, y
void draw_cursor(int x, int y) {
    char * black = rgb_to_byte(0, 0, 0);
    
    // draw the first cursor
    draw_line(x, y-10, x, y+10, black);
    draw_line(x-10, y, x+10, y, black);
}

int main(void) {
    // attempt to initiate the frame buffer
	if (init_screen()) {
        printf("Opened the framebuffer \n");
    }
    else {
        printf("Unable to open frame buffer \n");
        exit(1);
    }
    
    // attempt to initiate the touch screen
    if (init_touchscreen()) {
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
	char * colour = rgb_to_byte(255, 255, 255);
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