###############################################################################
#
# Exercise 3 Makefile
#
###############################################################################

CC = avr32-linux-gcc
CFLAGS = -g
SOURCES = test.c
OUTFILE = test

all:
	$(CC) $^ $(CFLAGS) -o $(OUTFILE)

.PHONY: clean
clean:
	rm $(OUTFILE)