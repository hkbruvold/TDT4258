/*****************************************************************************
 * 
 * Exercise 2 - main file
 *
 *****************************************************************************/

#include "ex2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;	// piob; buttons
volatile avr32_pio_t *pioc = &AVR32_PIOC;	// pioc; leds
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;
volatile avr32_pm_t *pm = &AVR32_PM;


int main (int argc, char *argv[]) {
  initHardware();

  while(1);
  return 0;
}

void clearLEDs(void) {
  poic->codr = 0xff;
}

void initHardware (void) {
  initIntc();
  initLeds();
  initButtons();
  initAudio();

  clearLEDs();
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
  int pressedButton = statusRegister & 0xff; // Filter away excess bits

  switch (pressedButton) {
    case SW0:
      playMelody(0);
      pioc->sodr = 1;
      break;
    case SW1:
      playMelody(1);
      pioc->sodr = 2;
      break;
    case SW2:
      playMelody(2);
      pioc->sodr = 4;
      break;
    case SW3:
      playMelody(3);
      pioc->sodr = 8;
      break;
    case SW4:
      playMelody(4);
      pioc->sodr = 16;
      break;
    case SW5:
      playMelody(5);
      pioc->sodr = 32;
      break;
    case SW6:
      playMelody(6);
      pioc->sodr = 64;
      break;
    case SW7:
      playMelody7();
      pioc->sodr = 128;
      break;
    default:
      break;
  }
}

void abdac_isr(void) {
  int statusRegister = abdac->isr;
  short channelData = getNextSample();
  
  abdac->SDR.channel0 = channelData;
  abdac->SDR.channel1 = channelData;
  
}
