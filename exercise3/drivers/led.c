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

/* cdev struct */

struct cdev *led_cdev;

/*****************************************************************************/

volatile avr32_pio_t *piob = &AVR32_PIOB;

dev_t dev_no;

static int __init led_init(void)
{
  int ret;
  
  printk(KERN_NOTICE "LED driver: Loading driver");


  // allocate major and minor number
  ret = alloc_chrdev_region(&dev_no, 0, 1, "led");
  if(ret < 0)
  {
    printk(KERN_WARNING "LED driver: can\'t register character device with errorcode = %i \n", ret);
    return 1;
  }
  int mjnr = MAJOR(dev_no);
  int minr = MINOR(dev_no);

  printk(KERN_NOTICE "LED driver: allocated device with major number = %i and minor number %i \n", mjnr, minr);

  // allocate access for I/O ports
  // 1024 = AVR32_PIOC_ADDRESS - AVR32_PIOB_ADDRESS
  request_region(AVR32_PIOB_ADDRESS, 1024000, "led"); 
  
  // initialise PIO hardware
  piob->per = 0xff;
  piob->oer = 0xff;

  // register device in system
  led_cdev = cdev_alloc();
  led_cdev->ops = &led_fops;
  //cdev_init(led_cdev, &led_fops);
  if (cdev_add(led_cdev, dev_no, 1) != 0)
  {
    printk(KERN_WARNING "LED driver: Error when adding driver to system");
  }

  return 0;
}

static void __exit led_exit(void)
{
  printk(KERN_NOTICE "LED driver: unloading driver");
  release_region(AVR32_PIOB_ADDRESS, 1024);
  unregister_chrdev(MAJOR(dev_no), "led");
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
