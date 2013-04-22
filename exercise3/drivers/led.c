/******************************************************************************
 *
 * LED driver
 *
 ******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>

volatile avr32_pio_t *pioc = &AVR32_PIOC;

static int __init init_led(void)
{
  pioc->per = 0xff;
  pioc->our = 0xff;
}

static void __exit exit_led(void)
{
}

module_init(init_led);
module_exit(exit_led);
