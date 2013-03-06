/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "ex2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;	// piob; buttons
volatile avr32_pio_t *pioc = &AVR32_PIOC;	// pioc; leds
volatile avr32_dac_t *dac = &AVR32_ABDAC;
volatile avr32_pm_t *pm = &AVR32_PM;

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
  register_interrupt(button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
  piob->per = 0xff;
  piob->puer = 0xff;
  piob->ier = 0xff;
}

void initLeds(void) {
  pioc->per = 0xff;
  pioc->oer = 0xff;
}

void initAudio(void) {
  register_interrupt(abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  
  piob->pdr.p20 = 1;
  piob->pdr.p21 = 1;

  piob->asr.p20 = 1;
  piob->asr.p21 = 1;
  
  pm->pm_gcctrl[6] = data; /* something goes here*/
  
  dac->cr.en = 1;
  dac->ier.tx_ready = 1;
}

void button_isr(void) {
  int pressedButton = piob->isr;
  pioc->codr = 0xff; // temporary
  pioc->sodr = pressedButton; // temporary
  
  if (pressedButton == SW0) {
    /* do something */
  } else if (pressedButton == SW1) {
    /* do something */
  } else if (pressedButton == SW2) {
    /* do something */
  } else if (pressedButton == SW3) {
    /* do something */
  } else if (pressedButton == SW4) {
    /* do something */
  } else if (pressedButton == SW5) {
    /* do something */
  } else if (pressedButton == SW6) {
    /* do something */
  } else if (pressedButton == SW7) {
    /* do something */
  }
}

void abdac_isr(void) {}
