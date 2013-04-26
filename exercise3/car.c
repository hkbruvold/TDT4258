/******************************************************************************
 *
 * Scroller
 *
 ******************************************************************************/

#include "car.h"


static int driver[8280] = 
{	K,K,K,K,K,C,C,C, W,W,W,W,W,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,W,W,W,W,W, C,C,C,K,K,K,K,K,
	K,K,K,C,C,C,C,C, W,W,W,W,W,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,W,W,W,W,W, C,C,C,C,C,K,K,K,
	K,K,C,C,C,C,C,C, C,W,W,W,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,W,W,W,C, C,C,C,C,C,C,K,K,
	K,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,K,
	K,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,K,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,B,B,B,W,W,R,R, R,R,R,R,R,R,R,R,R,R,R,R,R,R, R,R,R,W,W,B,B,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,W,W,B,B,W,W,R, R,R,R,R,R,R,R,R,R,R,R,R,R,R, R,W,W,B,B,W,W,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,W,W,B,B,B,B,W, W,R,R,R,R,R,R,R,R,R,R,R,R,W, W,B,B,B,B,W,W,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,B,B,B,W,W,B,B, W,W,R,R,R,R,R,R,R,R,R,R,W,W, B,B,W,W,B,B,B,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, W,W,B,B,W,W,B,B, B,W,W,R,R,R,R,R,R,R,R,W,W,B, B,B,W,W,B,B,W,W, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,W,W,B,B,B,B,W, W,B,B,W,W,R,R,R,R,W,W,B,B,W, W,B,B,B,B,W,W,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,W,W,B,B,W, W,B,B,B,W,W,R,R,W,W,B,B,B,W, W,B,B,W,W,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,R,R,W,W,B, B,W,W,B,B,B,W,W,B,B,B,W,W,B, B,W,W,R,R,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,R,R,R,W,W, B,W,W,B,B,B,B,B,B,B,B,W,W,B, W,W,R,R,R,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,R,R,R,R,W, B,B,B,B,B,B,W,W,B,B,B,B,B,B, W,R,R,R,R,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,R,R,R,R,W, B,B,B,B,B,B,W,W,B,B,B,B,B,B, W,R,R,R,R,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,R,R,R,W,W, B,W,W,B,B,B,B,B,B,B,B,W,W,B, W,W,R,R,R,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,R,R,W,W,B, B,W,W,B,B,B,W,W,B,B,B,W,W,B, B,W,W,R,R,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,R,R,W,W,B,B,W, W,B,B,B,W,W,R,R,W,W,B,B,B,W, W,B,B,W,W,R,R,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, R,W,W,B,B,B,B,W, W,B,B,W,W,R,R,R,R,W,W,B,B,W, W,B,B,B,B,W,W,R, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, W,W,B,B,W,W,B,B, B,W,W,R,R,R,R,R,R,R,R,W,W,B, B,B,W,W,B,B,W,W, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,B,B,B,W,W,B,B, W,W,R,R,R,R,R,R,R,R,R,R,W,W, B,B,W,W,B,B,B,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,W,W,B,B,B,B,W, W,R,R,R,R,R,R,R,R,R,R,R,R,W, W,B,B,B,B,W,W,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,W,W,B,B,W,W,R, R,R,R,R,R,R,R,R,R,R,R,R,R,R, R,W,W,B,B,W,W,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, B,B,B,B,W,W,R,R, R,R,R,R,R,R,R,R,R,R,R,R,R,R, R,R,R,W,W,B,B,B, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,S,S,S,S,S,S,S,S,S,S,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, C,C,C,C,C,C,C,C,
	C,C,C,C,C,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,C,C,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S,S,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,S,S,S, S,S,I,I,I,I,I,I,I,I,I,I,S,S, S,S,S,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, S,S,S,S,S,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,S,S,S,S,S, S,S,S,S,S,C,C,C,
	C,C,C,S,S,S,S,S, I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I, S,S,S,S,S,C,C,C,
	C,C,C,C,C,C,I,I, I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, I,I,K,K,K,K,K,K, I,I,I,I,I,I,I,I,I,I,I,I,I,I, K,K,K,K,K,K,I,I, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, I,K,K,K,K,K,K,K, K,I,I,I,I,I,I,I,I,I,I,I,I,K, K,K,K,K,K,K,K,I, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, K,K,K,K,K,K,K,K, K,K,I,I,I,I,I,I,I,I,I,I,K,K, K,K,K,K,K,K,K,K, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, K,K,K,K,K,K,K,K, K,K,I,I,I,I,I,I,I,I,I,I,K,K, K,K,K,K,K,K,K,K, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,I,I, K,K,K,K,K,K,K,K, K,K,I,I,I,I,I,I,I,I,I,I,K,K, K,K,K,K,K,K,K,K, I,I,C,C,C,C,C,C,
	C,C,C,C,C,C,C,I, I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I,I,I,I,I,I,I, I,I,I,I,I,I,I,I, I,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,
	C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C, C,C,C,C,C,C,C,C
};



void paint_driver(int driver_pos)
{
//	pixel(200,300,255,255,255);
	driver_pos = driver_pos*3;
	int i;
	for (i = 0; i<60; i++)
	{
		int j;
		for (j = 0; j<138; j++)	//46*3 = 138
			single_color(i+180,driver_pos+j,driver[(i*138)+j]);
	}
}
