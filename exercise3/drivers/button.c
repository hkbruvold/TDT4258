/******************************************************************************
 *
 * Button driver
 *
 ******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "ap7000.h"

/* prototypes */

static int __init button_init(void);
static void __exit button_exit(void);
static int driver_open (struct inode *inode, struct file *filp);
static int driver_release (struct inode *inode, struct file *filp);
static ssize_t driver_read (struct file *filp, char __user *buff,
                     size_t count, loff_t *offp);
static ssize_t driver_write (struct file *filp, const char __user *buff,
                      size_t count, loff_t *offp);

/* fops-struct */

static struct file_operations driver_fops = {
  .owner = THIS_MODULE,
  .read = driver_read,
  .write = driver_write,
  .open = driver_open,
  .release = driver_release
};

/*****************************************************************************/



volatile avr32_pio_t *piob = &AVR32_PIOB;

static int __init button_init(void)
{
  int ret;
  dev_t dev_no

  // allocate device number
  ret = alloc_chrdev_region(&dev_no, 0, 1,"button");

  // ask for access to I/O ports

  // initialise PIO hardware
  piob->per = 0xff;
  piob->puer = 0xff;
  piob->ier = 0xff;

  // register device in system
}

static void __exit button_init(void)
{
}

static int driver_open (struct inode *inode, struct file *filp) {
  return 0;
}

static int driver_release (struct inode *inode, struct file *filp) {
  return 0;
}

static ssize_t driver_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {
  return 0;
}

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {
  return 0;
}


module_init(button_exit);
module_exit(button_exit);

