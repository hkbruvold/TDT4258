/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "test.h"

int main(void)
{
  int led_fd;
  
  led_fd = open("/dev/led", O_RDWR, 0);
  printf("%i",led_fd);

  //char buffer;
  int e;

  if (e = write(led_fd, 0x55, 1) < 0)
  {
    printf("something went wrong, error code %i", e);
  }
  //printf("output: %i\n", );
  close(led_fd);
}
