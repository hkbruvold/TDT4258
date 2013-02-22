###############################################################################
#
# Exercise 2 Makefile
#
###############################################################################


CC = avr32-gcc # is also used for linking
CFLAGS = -W all -g -c
LDFLAGS =
SOURCES = ex1.c
OBJECTS = $(SOURCES:.c=.o)
OUTFILE = ex1.elf

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