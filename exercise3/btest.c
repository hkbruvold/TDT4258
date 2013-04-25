/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "btest.h"

int main(void)
{
  int button_fd;
  
  button_fd = open("/dev/button", O_RDWR, 0);
  //printf("%i",button_fd);

  int buffer;
  int e;

  if (e = read(button_fd, &buffer, sizeof(buffer)) < 0)
  {
    printf("something went wrong, error code %i\n", e);
  }
  printf("output: %i\n", buffer);
  close(button_fd);
}
