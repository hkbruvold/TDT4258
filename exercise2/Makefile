###############################################################################
#
# Exercise 2 Makefile
#
###############################################################################


CC = avr32-gcc # is also used for linking
CFLAGS = -Wall -g -c
LDFLAGS =
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
OUTFILE = main.elf

AVR32PROGRAM = avr32program

all: $(OUTFILE)

# link
$(OUTFILE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# make object files
.c.o:
	$(CC) $(CFLAGS) $< -o $@

upload: $(OUTFILE)
	$(AVR32PROGRAM) halt
	sleep 3
	$(AVR32PROGRAM) program -e -f0,8Mb $<

clean:
	rm $(OBJECTS) $(OUTFILE)