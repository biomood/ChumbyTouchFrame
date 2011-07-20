#include "screen.h"

char framestr[] = "/dev/fb0";
char * framebuffer;
FILE * frame;

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

void set_screen() {
	rewind(frame);
	fwrite(framebuffer, 1, FRAMESIZE, frame);
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
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    
    int sx, sy, e2;
    if (x0 < x1) {
        sx = 1;
    }
    else {
        sx = -1;
    }
    
    if (y0 < y1) {
        sy = 1;
    }
    else {
        sy = -1;
    }
    
    int err = dx-dy;
    while (1) {
        draw_pixel(x0, y0, colour);
        if (x0==x1 && y0==y1) {
            return;
        }
        e2 = 2*err;
        if (e2 > -dy) {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}

void draw_circle(int x0, int y0, int radius, char * colour) {
    int f = 1- radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    
    draw_pixel(x0, y0 + radius, colour);
    draw_pixel(x0, y0 - radius, colour);
    draw_pixel(x0 + radius, y0, colour);
    draw_pixel(x0 - radius, y0, colour);
    
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        draw_pixel(x0 + x, y0 + y, colour);
        draw_pixel(x0 - x, y0 + y, colour);
        draw_pixel(x0 + x, y0 - y, colour);
        draw_pixel(x0 - x, y0 - y, colour);
        draw_pixel(x0 + y, y0 + x, colour);
        draw_pixel(x0 - y, y0 + x, colour);
        draw_pixel(x0 + y, y0 - x, colour);
        draw_pixel(x0 - y, y0 - x, colour);
    }
}

void swap(int * a, int * b) {
    int *temp = a;
    a = b;
    b = temp;
}