/******************************************************************************
 *
 * Exercise 1 header file
 *
 *****************************************************************************/

#include <avr32/ap7000.h>
#include <sys/interrupts.h>

#define BUTTONS 0b00000101
#define SW0 0b1
#define SW2 0b100

struct ledstate {
  int leds;
}
