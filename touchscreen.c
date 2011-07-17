#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>


int main() {
	if (init_screen()==0) {
        printf("Opened the framebuffer \n");
    }
    else {
        printf("Unable to open frame buffer \n");
        exit(1);
    }
    
    // set background to white
	char * colour = rgb_to_byte(255, 255, 255);
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