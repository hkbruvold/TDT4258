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
void init_stripes(void)
{
	int stripestart = 155;
	int count;
	int i = 0;
	while (i<240)
	{
		for (count=280;count<360;count++)
		{
			int j=(count%320)*3;
		
			// blue:
			screen_row[i][j+0] = 95;
			// green:
			screen_row[i][j+1] = 95;
			// red:
			screen_row[i][j+2] = 95;
		}
		// blue:
		screen_row[i][280*3+0] = 45;
		// green:
		screen_row[i][280*3+1] = 45;
		// red:
		screen_row[i][280*3+2] = 45;
		
		// blue:
		screen_row[i][281*3+0] = 45;
		// green:
		screen_row[i][281*3+1] = 45;
		// red:
		screen_row[i][281*3+2] = 45;
		
		// blue:
		screen_row[i][288*3+0] = 45;
		// green:
		screen_row[i][288*3+1] = 45;
		// red:
		screen_row[i][288*3+2] = 45;
		
		// blue:
//		screen_row[i][289*3+0] = 45;
		// green:
//		screen_row[i][289*3+1] = 45;
		// red:
//		screen_row[i][289*3+2] = 45;
		
		// blue:
//		screen_row[i][30*3+0] = 45;
		// green:
//		screen_row[i][30*3+1] = 45;
		// red:
//		screen_row[i][30*3+2] = 45;
		
		// blue:
		screen_row[i][31*3+0] = 45;
		// green:
		screen_row[i][31*3+1] = 45;
		// red:
		screen_row[i][31*3+2] = 45;
		
		// blue:
		screen_row[i][38*3+0] = 45;
		// green:
		screen_row[i][38*3+1] = 45;
		// red:
		screen_row[i][38*3+2] = 45;
		
		// blue:
		screen_row[i][39*3+0] = 45;
		// green:
		screen_row[i][39*3+1] = 45;
		// red:
		screen_row[i][39*3+2] = 45;
		
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
				// blue:
				screen_row[count*40+j][i+0] = 0;
				// green:
				screen_row[count*40+j][i+1] = 255;
				// red:
				screen_row[count*40+j][i+2] = 255;
				i=i+3;
			}
			j++;
		}
	}
	
	
	
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
			int blackstripe=(rb+count*40)%ROWS;
			// blue:
			screen_row[blackstripe][i+0] = 0;
			// green:
			screen_row[blackstripe][i+1] = 0;
			// red:
			screen_row[blackstripe][i+2] = 0;
			
			// yellow stripe:
			int yellowstripe=(rb+30+count*40)%ROWS;
			// blue:
			screen_row[yellowstripe][i+0] = 0;
			// green:
			screen_row[yellowstripe][i+1] = 255;
			// red:
			screen_row[yellowstripe][i+2] = 255;
			i = i+3;
		}
		i=0;
		while (i<6*3)
		{
			int insstripe=((rb+count*20)+1)%ROWS;
			// blue:
			screen_row[insstripe][32*3+i+0] = 45;
			// green:
			screen_row[insstripe][32*3+i+1] = 45;
			// red:
			screen_row[insstripe][32*3+i+2] = 45;
		
			// blue:
			screen_row[insstripe][282*3+i+0] = 45;
			// green:
			screen_row[insstripe][282*3+i+1] = 45;
			// red:
			screen_row[insstripe][282*3+i+2] = 45;
			
			insstripe=((rb+count*40)+1)%ROWS;
			// blue:
			screen_row[insstripe][32*3+i+0] = 45;
			// green:
			screen_row[insstripe][32*3+i+1] = 45;
			// red:
			screen_row[insstripe][32*3+i+2] = 45;
		
			// blue:
			screen_row[insstripe][282*3+i+0] = 45;
			// green:
			screen_row[insstripe][282*3+i+1] = 45;
			// red:
			screen_row[insstripe][282*3+i+2] = 45;
			
			int rmstripe=((rb+count*20)%ROWS);
			// blue:
			screen_row[rmstripe][32*3+i+0] = 95;
			// green:
			screen_row[rmstripe][32*3+i+1] = 95;
			// red:
			screen_row[rmstripe][32*3+i+2] = 95;
		
			// blue:
			screen_row[rmstripe][282*3+i+0] = 95;
			// green:
			screen_row[rmstripe][282*3+i+1] = 95;
			// red:
			screen_row[rmstripe][282*3+i+2] = 95;
			
			rmstripe=((rb+count*40)%ROWS);
			// blue:
			screen_row[rmstripe][32*3+i+0] = 95;
			// green:
			screen_row[rmstripe][32*3+i+1] = 95;
			// red:
			screen_row[rmstripe][32*3+i+2] = 95;
		
			// blue:
			screen_row[rmstripe][282*3+i+0] = 95;
			// green:
			screen_row[rmstripe][282*3+i+1] = 95;
			// red:
			screen_row[rmstripe][282*3+i+2] = 95;
			
			i = i+3;
		}
	}
	
	rb++;
}










