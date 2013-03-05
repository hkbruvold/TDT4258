/******************************************************************************
 *
 * Exercise 1 header file
 *
 *****************************************************************************/

#ifndef EX1_H
#define EX1_H

#include <stdio.h>
#include <stdlib.h>

#include <avr32/ap7000.h>
#include "include/sys/interrupts.h"

#define BUTTONS 5
#define SW0 1
#define SW2 4

struct ledstate {
  int leds;
};

int main(int argc, char *argv[]);
void *int_handler(void);

#endif
