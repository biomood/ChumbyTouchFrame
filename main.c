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
    
    struct pixel_coord p0 = {40, 40};
    
    // retrieve 1st touch
    draw_cursor(p0.x, p0.y);
    draw_circle(p0.x, p0.y, 5, black);
    set_screen();
    struct touch_coord t0 = get_raw_touch();
    set_colour(white);
    printf("Touch1: x:%ld y:%ld \n", t0.x, t0.y);
    
    sleep(1);
    
    struct pixel_coord p1 = {160, 150};
    
    // retrieve 2nd touch
    draw_cursor(p1.x, p1.y);
    draw_circle(p1.x, p1.y, 5, black);
    set_screen();
    struct touch_coord t1 = get_raw_touch();
    set_colour(white);
    printf("Touch2: x:%ld y:%ld \n", t1.x, t1.y);
    
    sleep(1);
    
    struct pixel_coord p2 = {280, 200};
    
    // retrieve 3rd touch
    draw_cursor(p2.x, p2.y);
    draw_circle(p2.x, p2.y, 5, black);
    set_screen();
    struct touch_coord t2 = get_raw_touch();
    set_colour(white);
    printf("Touch3: x:%ld y:%ld \n", t2.x, t2.y);
    
    calibrate_touch(t0, t1, t2, p0, p1, p2);
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