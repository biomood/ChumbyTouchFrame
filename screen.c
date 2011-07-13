#include "screen.h"

void init_screen() {
    // open the framebuffer to read/write
	frame = fopen(framestr, "r+b");
    
	if (frame) {
        // make an array size of the framebuffer
        framebuffer = malloc(sizeof(char)*(FRAMESIZE));
		return 0;
	}
	else {
		return 1;
    }
}

void set_colour(char colour[]) {
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