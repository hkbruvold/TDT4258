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

static struct file_operations button_fops = {
  .owner = THIS_MODULE,
  .read = button_read,
  .write = button_write,
  .open = button_open,
  .release = button_release
};

/*****************************************************************************/



volatile avr32_pio_t *piob = &AVR32_PIOB;

int mjnr = 0;
int minr = 0;

static int __init button_init(void)
{
  printk(KERN_NOTICE "Button driver: Loading driver");

  int ret;
  dev_t dev_no;


  // allocate access for I/O ports
  // 1024 = AVR32_PIOC_ADDRESS - AVR32_PIOB_ADDRESS
  
  // initialise PIO hardware
  piob->per = 0x4001e700;
  piob->puer = 0x4001e700;
  piob->ier = 0x4001e700;

  // register device in system
  request_region(AVR32_PIOB_ADDRESS, 1024, "button"); 
  if(ret < 0)
  {
    printk(KERN_WARNING "Button driver: can\'t register character device with errorcode = %i \n", ret);
    return ret;
  }

  // allocate device number
  ret = alloc_chrdev_region(&dev_no, 0, 1, "button");

  mjnr = MAJOR(dev_no);
  minr = MINOR(dev_no);

  printk(KERN_NOTICE "Button driver: allocated device with major number = %i and minor number %i \n", mjnr, minr);



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

# , loff_t *offp
static ssize_t button_read(struct file *filp, char __user *buff,
              size_t count) 
{
  char *output = 0;
  int button_pdsr = ~(piob->pdsr);

  if (button_pdsr && 0x100) { output += 0x1; }
  if (button_pdsr && 0x200) { output += 0x2; }
  if (button_pdsr && 0x400) { output += 0x4; }
  if (button_pdsr && 0x2000) { output += 0x8; }
  if (button_pdsr && 0x4000) { output += 0x10; }
  if (button_pdsr && 0x8000) { output += 0x20; }
  if (button_pdsr && 0x10000) { output += 0x40; }
  if (button_pdsr && 0x40000000) { output += 0x80; }
  

  copy_to_user(buff, output, 1);
  return 0;
}

static ssize_t button_write(struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) 
{
  return 0;
}

MODULE_LICENSE("GPL");
module_init(button_init);
module_exit(button_exit);

