/******************************************************************************
 *
 * Button driver
 *
 ******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>

volatile avr32_pio_t *piob = &AVR32_PIOB;

static int __init init_button(void)
{
  piob->per = 0xff;
  piob->puer = 0xff;
  piob->ier = 0xff;
}

static void __exit exit_button(void)
{
}

module_init(init_button);
module_exit(exit_button);

