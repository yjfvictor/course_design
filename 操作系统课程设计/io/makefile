CC=gcc
DEBUG_OPTION=-ggdb
STD=-std=c99
CFLAGS=$(STD) $(DEBUG_OPTION) -Wall

all: createfile file1 file2 file3

createfile: createfile.c
	$(CC) $< -o $@ $(CFLAGS)

file1: file1.c
	$(CC) $< -o $@ $(CFLAGS)

file2: file2.c
	$(CC) $< -o $@ $(CFLAGS)

file3: file3.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm createfile file1 file2 file3

.PHONY: all clean
