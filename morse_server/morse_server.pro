# -------------------------------------------------
# morse_server project
# -------------------------------------------------

SOURCES +=  main.c \
            morse_server.c \
            gpio_access.c \
            string_handling.c \
            server_socket.c

HEADERS +=  morse_server.h \
            gpio_access.h \
            includes.h \
            string_handling.h \
            server_socket.h

OTHER_FILES += Makefile

linux-* {
    target.path = ./
    INSTALLS += target
}
