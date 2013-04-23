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
static int button_open (struct inode *inode, struct file *filp);
static int button_release (struct inode *inode, struct file *filp);
static ssize_t button_read (struct file *filp, char __user *buff,
                     size_t count, loff_t *offp);
static ssize_t button_write (struct file *filp, const char __user *buff,
                      size_t count, loff_t *offp);

/* fops-struct */

static struct file_operations driver_fops = {
  .owner = THIS_MODULE,
  .read = button_read,
  .write = button_write,
  .open = button_open,
  .release = button_release
};

/*****************************************************************************/



volatile avr32_pio_t *piob = &AVR32_PIOB;

int mjnr = 0;

static int __init button_init(void)
{
  printk(KERN_NOTICE "Button driver: Loading driver");

  int ret;
  dev_t dev_no;

  // allocate device number
  mjnr = alloc_chrdev_region(&dev_no, 0, 1,"button");

  printk(KERN_NOTICE "Button driver: allocated device with major number = %i and minor numbers 0...255", mjnr);

  // allocate access for I/O ports
  // 1024 = AVR32_PIOC_ADDRESS - AVR32_PIOB_ADDRESS
  request_region(AVR32_PIOB_ADDRESS, 1024, "button"); 

  // initialise PIO hardware
  piob->per = 0xff;
  piob->puer = 0xff;
  piob->ier = 0xff;

  // register device in system
  ret = register_chrdev(mjnr, "button", &driver_fops);
  if(ret < 0)
  {
    printk(KERN_WARNING "Button driver: can\'t register character device with errorcode = %i", ret);
    return ret;
  }
  return 0;
}

static void __exit button_exit(void)
{
  printk(KERN_NOTICE "Button driver: unloading driver");
  release_region(AVR32_PIOB_ADDRESS, 1024);
  unregister_chrdev(mjnr, "button");
}

static int button_open(struct inode *inode, struct file *filp) 
{
  return 0;
}

static int button_release(struct inode *inode, struct file *filp) 
{
  return 0;
}

static ssize_t button_read(struct file *filp, char __user *buff,
              size_t count, loff_t *offp) 
{
  char *output;
  int button_pdsr = piob->pdsr;

  output = (char*) button_pdsr;

  copy_to_user(buff, output, 1);
  return 0;
}

static ssize_t button_write(struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) 
{
  return 0;
}


module_init(button_init);
module_exit(button_exit);

