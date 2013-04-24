/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "test.h"

int main(void)
{
  int button_fd;
  
  button_fd = open("/dev/button", O_RDONLY, 0);
  printf("%i",button_fd);

  char buffer;
  int e;

  if (e = read(button_fd, buffer, 1) < 0)
  {
    printf("something went wrong, error code %i", e);
  }
  printf("output: %i\n", buffer);
  close(button_fd);
}
