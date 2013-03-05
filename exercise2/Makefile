###############################################################################
#
# Exercise 2 Makefile
#
###############################################################################


CC = avr32-gcc # is also used for linking
CFLAGS = -Wall -g -c -Iinclude
LDFLAGS = -g -Wall -pedantic -Llib -lavr32b-interrupts -lm
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

upload: 
	$(AVR32PROGRAM) halt
	sleep 3
	$(AVR32PROGRAM) program -e -f0,8Mb $(OUTFILE)

clean:
	rm *.o *.elf
