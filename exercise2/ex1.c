/******************************************************************************
 *
 * Exercise 1 ported to C
 *
 *****************************************************************************/

#include "ex1.h"

__int_handler *int_handler(void) {
  volatile avr32_pio_t *pioc = &AVR32_PIOC;
  volatile avr32_pio_t *piob = &AVR32_PIOB;
  
  struct ledstate ls;
  
  if (pioc->pdsr == SW0) {
    /* rightshift */
    piob->codr = 0xff;
    if (ls.leds == 1) {
      ls.leds = 0x80;
    } else {
      ls.leds >> 1;
    }
    piob->sodr = ls.leds;
  }

  if (pioc->pdsr == SW2) {
    /* leftshift */
    piob->codr == 0xff;
    if (ls.leds == 0x80) {
      ls.leds = 1;
    } else {
      ls.leds << 1;
    }
    piob->sodr = ls.leds;
  }
}

int main(void) {
  volatile avr32_pio_t *pioc = &AVR32_PIOC;
  volatile avr32_pio_t *piob = &AVR32_PIOB;

  struct ledstate ls;

  /* initialise buttons */
  pioc->per = BUTTONS;
  pioc->puer = BUTTONS;
  pioc->ier = BUTTONS;
  
  /* initialise LEDs */
  piob->per = 0xff;
  piob->oer = 0xff;

  /* initialise interrupt handling */
  set_interrupts_base((void*) AVR32_INTC_ADDRESS);
  register_interrupt((__int_handler) (int_handler),
                     AVR32_PIOC_IRQ/32, AVR32_PIOC_IRQ%32,
                     INT0);
  init_interrupts();

  /* turn on first LED */
  piob->codr = 0xff;
  ls->leds = 1;
  piob->sodr = ls.leds;

  /* start main loop */
  while (1) {
    SLEEP(AVR32_PM_SMODE_FROZEN);
  }
}
