/******************************************************************************
 *
 * LED driver
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

static int __init led_init(void);
static void __exit led_exit(void);
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

volatile avr32_pio_t *pioc = &AVR32_PIOC;

static int __init led_init(void)
{
  // allocate device number

  // ask for access to I/O ports

  // initialise PIO hardware
  pioc->per = 0xff;
  pioc->oer = 0xff;

  // register device in system
}

static void __exit led_init(void)
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


module_init(led_init);
module_exit(led_exit);
