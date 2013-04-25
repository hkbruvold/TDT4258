/******************************************************************************
 *
 * Button and LED test
 *
 ******************************************************************************/

#include "test.h"

int main(void)
{
  int led_fd;
  int button_fd;

  led_fd = open("/dev/led", O_RDWR, 0);
  button_fd = open("/dev/button", O_RDWR, 0);
  printf("led_fd: %i\nbutton_fd: %i\n", led_fd, button_fd);

  int buffer;
  int b, l;
  while (1) {
    if (b = read(button_fd, &buffer, sizeof(buffer)) < 0) {
      printf("error reading button, error code: %i\n", b);
    }
      
    if (l = write(led_fd, &buffer, sizeof(buffer)) < 0) {
      printf("error writing to led, error code: %i\n", l);
    }
  }

  close(led_fd);
  close(button_fd);
}
