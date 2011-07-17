CC=~/x-tools/arm-chumby-linux-gnueabi/bin/arm-chumby-linux-gnueabi-gcc

all: touchscreen

touchscreen: main.o screen.o touch.o
    $(CC) main.o screen.o touch.o -o touchscreen

main.o: main.c
    $(CC) main.c

screen.o: screen.c
    $(CC) screen.c

touch.o: touch.c
    $(CC) touch.c

clean:
rm -rf *o touchscreen