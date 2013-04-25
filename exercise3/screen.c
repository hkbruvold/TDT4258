/******************************************************************************
 *
 * Screen test
 *
 ******************************************************************************/


#include "screen.h"


int main(void)
{
	int fd;
	char *screen;
	
	int pixels = 76800;
	int i = 0;

	fd = open("/dev/fb0", O_RDWR | O_CREAT | O_TRUNC);
	screen = mmap(NULL, pixels*3, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (screen == MAP_FAILED) 
		printf("mmap fucked\n");

	else
		while (i<pixels*3)
		{
			// blue:
			screen[i+0] = 0;
			// green:
			screen[i+1] = 0;
			// red:
			screen[i+2] = 0;
			i = i+3;
		}

	return 0;
};
