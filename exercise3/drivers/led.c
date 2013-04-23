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
static int led_open (struct inode *inode, struct file *filp);
static int led_release (struct inode *inode, struct file *filp);
static ssize_t led_read (struct file *filp, char __user *buff,
                     size_t count, loff_t *offp);
static ssize_t led_write (struct file *filp, const char __user *buff,
                      size_t count, loff_t *offp);

/* fops-struct */

static struct file_operations led_fops = {
  .owner = THIS_MODULE,
  .read = led_read,
  .write = led_write,
  .open = led_open,
  .release = led_release
};

/*****************************************************************************/

volatile avr32_pio_t *piob = &AVR32_PIOB;

int mjnr = 0;
int minr = 0;

static int __init led_init(void)
{
  printk(KERN_NOTICE "LED driver: Loading driver");

  int ret;
  dev_t dev_no;

  // allocate device number
  alloc_chrdev_region(&dev_no, 0, 1, "led");

  mjnr = MAJOR(dev_no);
  minr = MINOR(dev_no);

  printk(KERN_NOTICE "LED driver: allocated device with major number = %i and minor number %i", mjnr, minr);

  // ask for access to I/O ports
  request_region(AVR32_PIOB_ADDRESS, 1024, "led");

  // initialise PIO hardware
  piob->per = 0xff;
  piob->oer = 0xff;

  // register device in system
  ret = register_chrdev(mjnr, "led", &led_fops);
  if(ret < 0)
  {
    printk(KERN_WARNING "LED driver: can\'t register character device with errorcode = %i", ret);
    return ret;
  }
  return 0;
}

static void __exit led_exit(void)
{
  printk(KERN_NOTICE "LED driver: unloading driver");
  release_region(AVR32_PIOB_ADDRESS, 1024);
  unregister_chrdev(mjnr, "led");
}

static int led_open (struct inode *inode, struct file *filp) {
  return 0;
}

static int led_release (struct inode *inode, struct file *filp) {
  return 0;
}

static ssize_t led_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {
  char *output = 0;
  int button_pdsr = piob->pdsr;

  output = (char*) (button_pdsr && 0xff);

  copy_to_user(buff, output, 1);
  return 0;
}

static ssize_t led_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {
  char *input = 0;
  copy_from_user(input, buff, 1);

  piob->codr = 0xff;
  piob->sodr = (int) input;
  
  return 0;
}

MODULE_LICENSE("GPL");
module_init(led_init);
module_exit(led_exit);
