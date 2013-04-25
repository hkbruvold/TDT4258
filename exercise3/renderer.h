/******************************************************************************
 *
 * Renderer header file
 *
 ******************************************************************************/

#include <stdio.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void);
int init_fd(void);
int close_fd(void);
int set_background(void);
int make_stripes(void);
