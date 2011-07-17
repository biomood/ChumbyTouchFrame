CC=~/x-tools/arm-chumby-linux-gnueabi/bin/arm-chumby-linux-gnueabi-gcc

all: touchscreen

touchscreen: main.o screen.o touch.o 
	$(CC) main.o screen.o touch.o -o touchscreen

main.o: main.c screen.h touch.h
	$(CC) -c main.c

screen.o: screen.c
	$(CC) -c screen.c

touch.o: touch.c
	$(CC) -c touch.c

clean:
	rm -rf *o touchscreen