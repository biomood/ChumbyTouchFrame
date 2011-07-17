CC=~/x-tools/arm-chumby-linux-gnueabi/bin/arm-chumby-linux-gnueabi-gcc

all: touchscreen

touchscreen: screen.o touch.o main.o
	$(CC) screen.o touch.o main.o  -o touchscreen

screen.o: screen.c
	$(CC) screen.c

touch.o: touch.c
	$(CC) touch.c

main.o: main.c
	$(CC) main.c

clean:
	rm -rf *o touchscreen