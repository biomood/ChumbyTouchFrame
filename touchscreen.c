#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>

#define FRAMESIZE 320*240*2


char framestr[] = "/dev/fb0";
char touchstr[] = "/dev/input/event1";

char * framebuffer;

FILE * frame;
FILE * touchscreen;

int td;

struct input_event ev;

int init_screen();
int init_touchscreen();
void set_screen();
void set_colour(char colour[]);
void draw_pixel(int x, int y, char * colour);
char * rgb_to_byte(int red, int green, int blue);


int main() {
	if (init_screen()==0) {
        printf("Opened the framebuffer \n");
    }
    else {
        printf("Unable to open frame buffer \n");
        exit(1);
    }
    
    // set background to white
	char * colour = rgb_to_byte(255, 0, 255);
	set_colour(colour);
	
	// write array to framebuffer
	set_screen();
    
    
    
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
	
	
    while (1) {
        int retval = read(td, &ev, sizeof(struct input_event));
        if (retval > 0) {
            switch(ev.type) {
                case EV_ABS:
                    printf("Type: EV_ABS: ");
                    switch (ev.code) {
                        case ABS_X:
                            printf("Code ABS_X:  %ld \n", ev.value);
                            break;
                        case ABS_Y:
                            printf("Code ABS_Y: %ld \n", ev.value);
                            break;
                        case ABS_PRESSURE:
                            printf("Code ABS_PRESSURE: %ld \n", ev.value);
                            break;
                        default:
                            break;
                    }
                    break;
                case EV_KEY:
                    printf("Type: EV_KEY: ");
                    printf("Value %ld \n", ev.value);
                    break;
                default:
                    printf("Type: unknown: ");
                    if (ev.value == EV_SYN) {
                        printf("Value %ld \n", ev.value);
                    }
                    else {
                        printf ("Unknown value %ld \n", ev.value);
                    }
                    break;
            }
        }
    }
    
	// clean up
	fclose(frame);
    if (close(td) == -1) {
        printf("Unable to close the touch screen file \n");
    }
}

// initiates the frame buffer
// returns 1 if failure
int init_screen() {
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


// initaites the touch screen
// returns 1 if failure
int init_touchscreen() {
    if ((td = open(touchstr, O_RDONLY))>-1){
        return 0;
    }
    else {
       return 1;
    }
}

// writes array to the framebuffer
void set_screen() {
	rewind(frame);
	fwrite(framebuffer, 1, FRAMESIZE, frame);
}

// sets the entire frame buffer to colour
void set_colour(char colour[]) {
	int i;
	for (i=0; i<(320*240*2); i=i+2) {
		framebuffer[i] = colour[0];
		int j = i;
		j++;
		framebuffer[j] = colour[1];
	}
}

// converts rgb to byte 
char * rgb_to_byte(int red, int green, int blue) {
	short int colour16 = (short)(((blue&0xf8)<<8) + 
								 ((red&0xfc)<<3) + ((green&0xf8)>>3));

	char * arr = malloc(sizeof(char)*2);
	arr[0] = ((colour16 >> 8) & 0xff);
	arr[1] = ((colour16 >> 0) & 0xff);
	
	return arr;
}

// sets a single pixel to colour
void draw_pixel(int x, int y, char * colour) {
	int pos = (((320*y)+x)*2);
	framebuffer[pos] = colour[0];
	framebuffer[pos+1] = colour[1];
}