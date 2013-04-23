/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "test.h"

int main(void)
{
  int led;
  
  led = open("/dev/led", O_RDONLY);
  
  char buffer = 0x55;
  
  if (write(led, buffer, 1) != 0)
  {
    printf("something went wrong\n");
  }
  close(led);
}
