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

/* cdev struct */

struct cdev *button_cdev;

/*****************************************************************************/



dev_t dev_no;
volatile avr32_pio_t *piob = &AVR32_PIOB;

static int __init button_init(void)
{
  int ret;
  
  printk(KERN_NOTICE "Button driver: Loading driver");


  // allocate major and minor number
  ret = alloc_chrdev_region(&dev_no, 0, 1, "button");
  if(ret < 0)
  {
    printk(KERN_WARNING "Button driver: can\'t register character device with errorcode = %i \n", ret);
    return ret;
  }
  int mjnr = MAJOR(dev_no);
  int minr = MINOR(dev_no);

  printk(KERN_NOTICE "Button driver: allocated device with major number = %i and minor number %i \n", mjnr, minr);

  // allocate access for I/O ports
  // 1024 = AVR32_PIOC_ADDRESS - AVR32_PIOB_ADDRESS
  request_region(AVR32_PIOB_ADDRESS, 1024, "button"); 
  
  // initialise PIO hardware
  piob->per = 0x4001e700;
  piob->puer = 0x4001e700;
  //piob->ier = 0x4001e700;

  // register device in system
  button_cdev = cdev_alloc();
  button_cdev->ops = &button_fops;
  button_cdev->owner = THIS_MODULE;
  //cdev_init(button_cdev, &button_fops);
  if (cdev_add(button_cdev, dev_no, 1) != 0)
  {
    printk(KERN_WARNING "Button driver: Error when adding driver to system");
  }


  return 0;
}

static void __exit button_exit(void)
{
  printk(KERN_NOTICE "Button driver: unloading driver");
  //release_region(AVR32_PIOB_ADDRESS, 1024);
  //unregister_chrdev(MAJOR(dev_no), "button");
  cdev_del(button_cdev);
}

static int button_open(struct inode *inode, struct file *filp) 
{
  return 0;
}

static int button_release(struct inode *inode, struct file *filp) 
{
  return 0;
}

static ssize_t button_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp)
{
  int output = 0x00;
  int button_pdsr = (~(piob->pdsr) & 0x4001e700);

  printk(KERN_NOTICE "button_pdsr: %i", button_pdsr);
  
  if (button_pdsr & 0x100) { output += 0x1; printk(KERN_NOTICE "button0"); }
  if (button_pdsr & 0x200) { output += 0x2; printk(KERN_NOTICE "button1"); }
  if (button_pdsr & 0x400) { output += 0x4; printk(KERN_NOTICE "button2"); }
  if (button_pdsr & 0x2000) { output += 0x8; printk(KERN_NOTICE "button3"); }
  if (button_pdsr & 0x4000) { output += 0x10; printk(KERN_NOTICE "button4"); }
  if (button_pdsr & 0x8000) { output += 0x20; printk(KERN_NOTICE "button5"); }
  if (button_pdsr & 0x10000) { output += 0x40; printk(KERN_NOTICE "button6"); }
  if (button_pdsr & 0x40000000) { output += 0x80; printk(KERN_NOTICE "button7"); }

  printk(KERN_NOTICE "%i", output);
  copy_to_user(buff, &output, sizeof(buff));
  return count;
}

static ssize_t button_write(struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) 
{
  return 0;
}

MODULE_LICENSE("GPL");
module_init(button_init);
module_exit(button_exit);

