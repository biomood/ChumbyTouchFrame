#include "screen.h"

int init_screen() {
    // open the framebuffer to read/write
	frame = fopen(framestr, "r+b");
    
	if (frame) {
        // make an array size of the framebuffer
        framebuffer = malloc(sizeof(char)*(FRAMESIZE));
		return 1;
	}
	else {
		return 0;
    }
}

void set_colour(char colour[]) {
    
    // iterate through the framebuffer setting each pixel to colour
    int i;
	for (i=0; i<(FRAMESIZE); i=i+2) {
		framebuffer[i] = colour[0];
		int j = i;
		j++;
		framebuffer[j] = colour[1];
	}
}

void draw_pixel(int x, int y, char * colour) {
    int pos = (((320*y)+x)*2);
	framebuffer[pos] = colour[0];
	framebuffer[pos+1] = colour[1];
}

char * rgb_to_byte(int red, int green, int blue) {
    short int colour16 = (short)(((blue&0xf8)<<8) + 
								 ((red&0xfc)<<3) + ((green&0xf8)>>3));
    
	char * arr = malloc(sizeof(char)*2);
	arr[0] = ((colour16 >> 8) & 0xff);
	arr[1] = ((colour16 >> 0) & 0xff);
	
	return arr;
}

void draw_line(int x0, int y0, int x1, int y1, char * colour) {
    int steep = abs(y1-y0) > abs(x1-x0);
    if (steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    
    int deltax = x1-x0;
    int deltay = abs(y1-y0);
    int error = deltax/2;
    int ystep;
    int y=y0;
    
    if (y0 < y1 ) {
        ystep = 1;
    }
    else {
        ystep = -1;
    }
    
    int x;
    for (x=x0; x<x1; x++) {
        if (steep) {
            draw_pixel(y, x, colour);
        }
        else {
            draw_pixel(x, y, colour);
        }
        
        error = error - deltay;
        if (error < 0) {
            y = y + ystep;
            error = error + deltax;
        }
    }
}

void swap(int * a, int * b) {
    int *temp = a;
    a = b;
    b = temp;
}