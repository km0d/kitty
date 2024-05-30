CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OUT=kitty.so
DOUT=kitty_debug.so

install:
	mkdir ./build/
	$(CC) -c src/kitty.c -o ./build/kitty.o $(CFLAGS) -fPIC -D_GNU_SOURCE
	$(CC) -c src/hooks.c -o ./build/hooks.o $(CFLAGS) -fPIC -D_GNU_SOURCE
	$(CC) -c src/hide.c -o ./build/hide.o $(CFLAGS) -fPIC -D_GNU_SOURCE
	$(CC) build/*.o -shared -o $(OUT)
	rm -r ./build/

debug:
	mkdir ./build/
	$(CC) -c src/kitty.c -o ./build/kitty.o $(CFLAGS) -fPIC -D_GNU_SOURCE -D DEBUG
	$(CC) -c src/hooks.c -o ./build/hooks.o $(CFLAGS) -fPIC -D_GNU_SOURCE -D DEBUG
	$(CC) -c src/hide.c -o ./build/hide.o $(CFLAGS) -fPIC -D_GNU_SOURCE -D DEBUG
	$(CC) build/*.o -shared -D DEBUG -o $(DOUT)
	rm -r ./build/
