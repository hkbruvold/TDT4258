/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "ltest.h"

int main(void)
{
  int led_fd;
  
  led_fd = open("/dev/led", O_RDWR);
  //printf("open status: %i\n",led_fd);
  //char buffer;
  int e;
  int buff = 0x55;

  if (e = write(led_fd, &buff, sizeof(buff)) < 0)
  {
    printf("something went wrong, error code %i", e);
  }
  printf("bytes written: %i\n", e);
  close(led_fd);
}
