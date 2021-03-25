CC=gcc
CFLAGS=-I /usr/include/freetype2 -I /usr/include/freetype2/freetype
LDFLAGS=-lfreetype

all: font2c

font2c: font2c.c
	$(CC) $(CFLAGS) font2c.c $(LDFLAGS) -o font2c
