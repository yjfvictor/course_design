CC=gcc
STD=-std=gnu99
DEBUG_OPTION=-ggdb
THREAD_OPTION=-D_REENTRANT -lpthread
OTHER_OPTION=-Wall
CFLAGS=$(STD) $(DEBUG_OPTION) $(THREAD_OPTION) $(OTHER_OPTION)

all: thread_synchronization process_synchronization

thread_synchronization: thread_synchronization.c
	$(CC) $< -o $@ $(CFLAGS)
process_synchronization: process_synchronization.c
	$(CC) $< -o $@ $(CFLAGS)
clean:
	-rm thread_synchronization process_synchronization
.PHONY: all clean
