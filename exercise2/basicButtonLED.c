/******************************************************************************
 *
 * Exercise 1 ported to C
 *
 *****************************************************************************/

#include "basicButtonLED.h"

int main(int argc, char *argv[]) {
  volatile avr32_pio_t *pioc = &AVR32_PIOC;
  volatile avr32_pio_t *piob = &AVR32_PIOB;

  /* initialise buttons */
  pioc->per = 0xff;
  pioc->puer = 0xff;
  
  /* initialise LEDs */
  piob->per = 0xff;
  piob->oer = 0xff;

  /* start main loop */
  while (1) {
    int a = pioc->pdsr;
    piob->codr = 0xff;
    pioc->sodr = a;
  }
}
