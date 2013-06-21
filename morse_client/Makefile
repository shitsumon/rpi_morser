################################
# Makefile for the led_blinker #
# project for the raspberry pi #
################################

CC      = gcc
LD      = ld
LDD     = ldd
FILES   = main.c client_socket.c
HEADER  = client_socket.h
OBJECTS = main.o client_socket.o
CFLAGS  = -Wall -c -std=c99 -g
LDFLAGS = -o
BINARY  = morse_client
.PHONY  = clean distclean rebuild

all: build

build: $(OBJECTS)
	$(CC) $+ $(LDFLAGS) $(BINARY)

%o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS)

distclean:
	rm -rf $(OBJECTS) $(BINARY)

rebuild: distclean all
