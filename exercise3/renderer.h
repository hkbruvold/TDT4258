/******************************************************************************
 *
 * Renderer header file
 *
 ******************************************************************************/

#ifndef RENDERER
#define RENDERER

#include <stdio.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ROWS 240
#define COLUMN 320
#define PIXELS 76800

int init_fd(void);
int close_fd(void);
int set_background(void);
void single_color(int i, int j, int value);
void pixel(int i, int j, int blue, int green, int red);
void init_stripes(void);
void move_stripes(void);
void paint_car_column(int column);

#endif
