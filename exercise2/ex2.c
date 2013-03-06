/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "ex2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;	// piob; buttons
volatile avr32_pio_t *pioc = &AVR32_PIOC;	// pioc; leds


int main (int argc, char *argv[]) {
  initHardware();

  while(1);
  return 0;
}

/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware (void) {
  initIntc();
  initLeds();
  initButtons();
  initAudio();
}

void initIntc(void) {
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);
  init_interrupts();
}

void initButtons(void) {
  register_interrupt( button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
  /* (...) */
  piob->per = 0xff;
  piob->puer = 0xff;
  piob->ier = 0xff;
}

void initLeds(void) {
  /* (...) */
  pioc->per = 0xff;
  pioc->oer = 0xff;
  pioc->codr = 0xff;
}

void initAudio(void) {
  register_interrupt( abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  /* (...) */
}

void button_isr(void) {
  int a = piob->isr;
  pioc->codr = 0xff;
  pioc->sodr = a;
}

void abdac_isr(void) {}
