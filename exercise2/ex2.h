/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 * Headerfil
 *

 *****************************************************************************/

#ifndef EX_2_H /* vanlig måte å unngå headerrekursjon på */
#define EX_2_H

#include <stdio.h>
#include <stdlib.h>

#include <avr32/ap7000.h> /* inkludere Atmel-headerfil */
#include <sys/interrupts.h>

/* legg andre "includes" her, sammen med "defines" og prototyper */
#define ABDAC_INT_LEVEL 0
#define BUTTONS_INT_LEVEL 0

/* Button makros */
#define SW0 0b1
#define SW1 0b10
#define SW2 0b100
#define SW3 0b1000
#define SW4 0b10000
#define SW5 0b100000
#define SW6 0b1000000
#define SW7 0b10000000


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
