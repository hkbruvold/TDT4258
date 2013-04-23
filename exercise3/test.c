/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "test.h"

int main(void)
{
  int button;
  
  button = open("/dev/button", O_RDONLY);
  
  char buffer = 0;
  
  if (read(button, buffer, 1) != 0)
  {
    printf("something went wrong\n");
  }
  printf("output: %i", buffer);
  close(button);
}
