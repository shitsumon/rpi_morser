################################
# Makefile for the morse_server #
# project. Deployable on       #
# Raspberry Pi only!           #
################################

CC      = arm-unknown-linux-gnueabi-gcc
LD      = arm-unknown-linux-gnueabi-ld
LDD     = arm-unknown-linux-gnueabi-ldd
FILES   = gpio_access.c morse_server.c main.c string_handling.c server_socket.c
HEADER  = gpio_access.h morse_server.h includes.h string_handling.h server_socket.h
OBJECTS = gpio_access.o morse_server.o string_handling.o main.o server_socket.o
CFLAGS  = -g -Wall -c -std=c99 -g
LDFLAGS = -o
BINARY  = morse_server
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
