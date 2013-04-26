/******************************************************************************
 *
 * Renderer
 *
 ******************************************************************************/


#include "renderer.h"


int fd;

int rb = 0;

char *screen_start;
char *screen_row[ROWS];


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
	while (i<ROWS)
	{
		screen_row[i] = &screen_start[i*320*3];
		i++;
	}
	set_background();
	return 0;
}
int close_fd(void)
{
	close(fd);
	printf("framebuffer closed\n");
	return 0;
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
	init_stripes();

	return 0;
}
void single_color(int i, int j, int value)
{
	screen_row[i][j] = value;
}
void pixel(int i, int j, int blue, int green, int red)
{
	// blue:
	screen_row[i][j+0] = blue;
	// green:
	screen_row[i][j+1] = green;
	// red:
	screen_row[i][j+2] = red;
}
void init_stripes(void)
{
	int stripestart = 155;
	int count;
	int i = 0;
	while (i<240)
	{
		for (count=280;count<360;count++)
		{
			pixel(i,(count%320)*3,95,95,95);
		}
		pixel(i,280*3,45,45,45);
		pixel(i,281*3,45,45,45);
		pixel(i,288*3,45,45,45);
		pixel(i,31*3,45,45,45);
		pixel(i,38*3,45,45,45);
		pixel(i,39*3,45,45,45);
		
		i++;
	}
	for (count=0;count<6;count++)
	{
		int j = 0;
		while (j<30)
		{
			int i = stripestart*3;
			while (i<163*3)
			{
				pixel(count*40+j,i,0,255,255);
				
				i=i+3;
			}
			j++;
		}
	}
	move_driver(0);
}
void move_stripes(void)
{
	if (rb==ROWS) rb=0;
	int stripestart = 155;
	
	int count;
	for (count=0;count<6;count++)
	{
		int i = stripestart*3;
		while (i<163*3)
		{
			// black stripe:
			pixel((rb+count*40)%ROWS,i,0,0,0);
			
			// yellow stripe:
			pixel((rb+30+count*40)%ROWS,i,0,255,255);
			
			i = i+3;
		}
		i=0;
		while (i<6*3)
		{
			int insstripe=((rb+count*20)+1)%ROWS;
			
			pixel(insstripe,32*3+i,45,45,45);
			pixel(insstripe,282*3+i,45,45,45);
			
			insstripe=((rb+count*40)+1)%ROWS;
			
			pixel(insstripe,32*3+i,45,45,45);
			pixel(insstripe,282*3+i,45,45,45);
			
			int rmstripe=((rb+count*20)%ROWS);
			
			pixel(rmstripe,32*3+i,95,95,95);
			pixel(rmstripe,282*3+i,95,95,95);
			
			rmstripe=((rb+count*40)%ROWS);
			
			pixel(rmstripe,32*3+i,95,95,95);
			pixel(rmstripe,282*3+i,95,95,95);
			
			i = i+3;
		}
	}
	
	rb++;
}
void paint_car_column(int column)
{
	int i;
	
	if (	column == 31
		|| column == 38
		|| column == 39
		|| column == 280
		|| column == 281
		|| column == 288)
		
		for (i=ROWS-60;i<ROWS;i++)
		{
			pixel(i,column*3,45,45,45);
		}
	else if (column<164 || column>154)
		for (i=ROWS-60;i<ROWS;i++)
		{
			pixel(i,column*3,0,255,255);
		}
	else if (column<280 || column>30)
		for (i=ROWS-60;i<ROWS;i++)
		{
			pixel(i,column*3,0,0,0);
		}
	else
		for (i=ROWS-60;i<ROWS;i++)
		{
			pixel(i,column*3,95,95,95);
		}
}










