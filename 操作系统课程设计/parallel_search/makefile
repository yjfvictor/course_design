CC=gcc
STD=-std=c99
DEBUG_OPTION=-ggdb
THREAD_OPTION=-D_REENTRANT -lpthread
OTHER_OPTION=-Wall
CFLAGS=$(STD) $(DEBUG_OPTION) $(THREAD_OPTION) $(OTHER_OPTION)

idfind: idfind.c
	$(CC) $< -o $@ $(CFLAGS)
clean:
	-rm idfind

.PHONY: clean
