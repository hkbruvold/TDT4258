/*****************************************************************************
 * 
 * Exercise 2
 *
 *****************************************************************************/

#ifndef EX_2_H
#define EX_2_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <avr32/ap7000.h> /* inkludere Atmel-headerfil */
#include <sys/interrupts.h>

#include "musicPlayer.h"

/* legg andre "includes" her, sammen med "defines" og prototyper */
#define ABDAC_INT_LEVEL 0
#define BUTTONS_INT_LEVEL 0

/* Button makros */
#define SW0 1   //0b1
#define SW1 2   //0b10
#define SW2 4   //0b100
#define SW3 8   //0b1000
#define SW4 16  //0b10000
#define SW5 32  //0b100000
#define SW6 64  //0b1000000
#define SW7 128 //0b10000000

/* prototyper */
int main (int argc, char *argv[]);
static void initIntc(void);
static void initButtons(void);
static void initLeds(void);
static void initAudio(void);
static void initHardware (void);

static void button_isr(void);
static void abdac_isr(void);

#endif
