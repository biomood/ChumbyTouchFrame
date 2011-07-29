#include <stdio.h>
#include <errno.h>

#include "screen.h"
#include "touch.h"

char calibrated = 0;

void calibrate_screen();
void draw_cursor(int x, int y);
int touch_callback(long int x, long int y);

// calibrates the screen
void calibrate_screen() {
    char * white = malloc(2*sizeof(char));
    white = rgb_to_byte(255, 255, 255);
    char * black = malloc(2*sizeof(char));
    black = rgb_to_byte(0, 0, 0);
    
    // retrieve 1st touch
    draw_cursor(40, 40);
    draw_circle(40, 40, 5, black);
    set_screen();
    struct touch_coord t1 = get_touch2();
    set_colour(white);
    
    sleep(1);
    
    // retrieve 2nd touch
    draw_cursor(160, 150);
    draw_circle(160, 150, 5, black);
    set_screen();
    struct touch_coord t2 = get_touch2();
    set_colour(white);
    
    sleep(1);
    
    // retrieve 3rd touch
    draw_cursor(280, 200);
    draw_circle(280, 200, 5, black);
    set_screen();
    struct touch_coord t3 = get_touch2();
    set_colour(white);
    
    
    calibrate_touch(t1.x, t1.y, t2.x, t2.y, t3.x, t3.y);
    
    
}

// draws a cursor to the screen with origin at x, y
void draw_cursor(int x, int y) {
    char * black = rgb_to_byte(0, 0, 0);
    
    // draw the first cursor
    draw_line(x, y-10, x, y+10, black);
    draw_line(x-10, y, x+10, y, black);
}

int touch_callback(long int x, long int y) {
    printf("Coordinates are x: %ld, y: %ld \n", x, y);
    if (!calibrated) {
        
    }
    
    return 0;
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
        
        // retrieve the name of the touch screen
        char name[256] = "Unknown";        
        ioctl(td, EVIOCGNAME (sizeof (name)), name);
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
    
    //struct touch_coord t1 = get_touch2();
    //printf("Coordinates are x: %ld, y: %ld \n", t1.x, t1.y);
    //sleep(2);
    //printf("Try touching again \n");
    //struct touch_coord t2 = get_touch2();
    //printf("Coordinates are x: %ld, y: %ld \n", t2.x, t2.y);
    
    // clean up
	fclose(frame);
    if (close(td) == -1) {
        printf("Unable to close the touch screen file \n");
    }
} 