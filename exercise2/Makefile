###############################################################################
#
# Exercise 2 Makefile
#
###############################################################################


CC = avr32-gcc # is also used for linking
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -g -Wall -pedantic -Llib -lavr32b-interrupts -lm
SOURCES = ex2.c musicPlayer.c notes.c sinTables.c melodies.c
OBJECTS = $(SOURCES:.c=.o)
OUTFILE = ex2.elf

AVR32PROGRAM = avr32program

all: $(OUTFILE)


# link
$(OUTFILE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# make object files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

upload: 
	$(AVR32PROGRAM) halt
	sleep 3
	$(AVR32PROGRAM) program -e -f0,8Mb $(OUTFILE)

clean:
	rm *.o *.elf
