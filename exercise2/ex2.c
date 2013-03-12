/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "ex2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;	// piob; buttons
volatile avr32_pio_t *pioc = &AVR32_PIOC;	// pioc; leds
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;
volatile avr32_pm_t *pm = &AVR32_PM;

int playingSound;

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

  pioc->codr = 0xff;
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
  
  piob->PDR.p20 = 1;
  piob->PDR.p21 = 1;

  piob->ASR.p20 = 1;
  piob->ASR.p21 = 1;
  
  pm->GCCTRL[6].diven = 0;
  pm->GCCTRL[6].pllsel = 0;
  pm->GCCTRL[6].oscsel = 1;
  pm->GCCTRL[6].cen = 1;  

  abdac->CR.en = 1;
  abdac->IER.tx_ready = 1;
}

void button_isr(void) {
  int statusRegister = piob->isr;
  int pressedButtons = statusRegister & 0xff; // Filter away excess bits

  switch (pressedButtons) {
    case SW0:
      playingSound = SW0;
      break;
    case SW1:
      playingSound = SW1;
      break;
    case SW2:
      playingSound = SW2;
      break;
    case SW3:
      playingSound = SW3;
      break;
    case SW4:
      playingSound = SW4;
      break;
    case SW5:
      playingSound = SW5;
      break;
    case SW6:
      playingSound = SW6;
      break;
    case SW7:
      playingSound = SW7;
      break;
    default:
      break;
  }

  pioc->sodr = playingSound;
}

void abdac_isr(void) {
  int statusRegister = abdac->isr;
  short channelData = rand();
  
  abdac->SDR.channel0 = ;
  abdac->SDR.channel1 = ;
  
}
