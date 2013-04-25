/******************************************************************************
 *
 * Renderer
 *
 ******************************************************************************/


#include "renderer.h"


int fd;
char *screen_start;
char *screen_row[240];
int COLUMNS = 320;

int PIXELS = 76800;

int main(void)
{
	init_fd();
	set_background();
	make_stripes();
	close_fd();
}

int init_fd(void)
{
	fd = open("/dev/fb0", O_RDWR | O_CREAT | O_TRUNC);
	screen_start = mmap(NULL, PIXELS*3, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (screen_start == MAP_FAILED) 
		return -1;	
//		printf("mmap fucked\n");
	else
		printf("framebuffer open\n");
	
	int i = 0;
	while (i<240)
	{
		screen_row[i] = &screen_start[i*320*3];
		i++;
	}
}
int close_fd(void)
{
	close(fd);
	printf("framebuffer closed\n");
}
int set_background(void)
{
	int i = 0;

	while (i<PIXELS*3)
	{
		// blue:
		screen_start[i+0] = 0;
		// green:
		screen_start[i+1] = 0;
		// red:
		screen_start[i+2] = 0;
		i = i+3;
	}

	return 0;
}
int make_stripes(void)
{
	int r = 90;
	while (r<110)
	{
		int i = 0;
		while (i<COLUMNS*3)
		{
			// blue:
			screen_row[r][i+0] = 0;
			// green:
			screen_row[r][i+1] = 0;
			// red:
			screen_row[r][i+2] = 255;
			i = i+3;
		}
		r++;
	}
	
	r = 180;
	while (r<200)
	{
		int i = 0;
		while (i<COLUMNS*3)
		{
			// blue:
			screen_row[r][i+0] = 255;
			// green:
			screen_row[r][i+1] = 255;
			// red:
			screen_row[r][i+2] = 255;
			i = i+3;
		}
		r++;
	}
};










