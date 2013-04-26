/******************************************************************************
 *
 * Sound test
 *
 ******************************************************************************/

#include "soundtest.h"

int main(void) 
{
  long filesize;
  char *buffer;
  int ret = 0;
  int rd;
  int wrt;
  int reading = 1;

  int soundcard_fd = open("/dev/dsp", O_WRONLY, 0);
  FILE *snd_fd = fopen("test.raw", "r");
  
  if (soundcard_fd < 0) {
    printf("error opening soundcard\n");
    ret = 1;
  }
  if (snd_fd < 0) {
    printf("error opening soundfile\n");
    ret = 1;
  }

  fseek(snd_fd, 0, SEEK_END);
  filesize = ftell(snd_fd);
  fseek(snd_fd, 0, SEEK_SET);
  printf("file size: %i\n", filesize);
  
  buffer = malloc(filesize * sizeof(char) +1);
  
  while (reading) {
    rd = fread(buffer, sizeof(char), filesize, snd_fd);
    printf("reading from file\n");
    if (feof(snd_fd)) {
      fclose(snd_fd);
      reading = 0;
    }
  }
  fclose(snd_fd);
  
  wrt = write(soundcard_fd, buffer, filesize);
  printf("buffer: %s\n", buffer);
  
  printf("wrote to dsp: %i\n", filesize);
  close(soundcard_fd);
  return ret;
}
