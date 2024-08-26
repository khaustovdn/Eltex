#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "my_chardev"
#define BUF_LEN 80

static int major;
static atomic_t already_open = ATOMIC_INIT(0);
static char msg[BUF_LEN];
static struct class* cls;

static int
device_open(struct inode*, struct file*);
static int
device_release(struct inode*, struct file*);
static ssize_t
device_read(struct file*, char __user*, size_t, loff_t*);
static ssize_t
device_write(struct file*,
             const char __user*,
             size_t,
             loff_t*);

static struct file_operations chardev_fops = {
  .owner = THIS_MODULE,
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release,
};

static int __init
chardev_init(void)
{
  major = register_chrdev(0, DEVICE_NAME, &chardev_fops);
  if (major < 0) {
    pr_err("Failed to register char device with error %d\n",
           major);
    return major;
  }
  pr_info("Assigned major number %d.\n", major);

  cls = class_create(DEVICE_NAME);
  if (IS_ERR(cls)) {
    unregister_chrdev(major, DEVICE_NAME);
    pr_err("Failed to create class\n");
    return PTR_ERR(cls);
  }

  if (!device_create(
        cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME)) {
    class_destroy(cls);
    unregister_chrdev(major, DEVICE_NAME);
    pr_err("Failed to create device\n");
    return -1;
  }

  pr_info("Device created at /dev/%s\n", DEVICE_NAME);
  return 0;
}

static void __exit
chardev_exit(void)
{
  device_destroy(cls, MKDEV(major, 0));
  class_destroy(cls);
  unregister_chrdev(major, DEVICE_NAME);
  pr_info("Device unregistered\n");
}

static int
device_open(struct inode* inode, struct file* file)
{
  if (atomic_cmpxchg(&already_open, 0, 1) != 0) {
    return -EBUSY;
  }

  try_module_get(THIS_MODULE);
  return 0;
}

static int
device_release(struct inode* inode, struct file* file)
{
  atomic_set(&already_open, 0);
  module_put(THIS_MODULE);
  return 0;
}

static ssize_t
device_read(struct file* filp,
            char __user* buffer,
            size_t length,
            loff_t* offset)
{
  int bytes_read = 0;

  if (*offset >= strlen(msg)) {
    *offset = 0;
    return 0;
  }

  while (length && msg[*offset]) {
    if (put_user(msg[*offset], buffer++)) {
      return -EFAULT;
    }
    (*offset)++;
    length--;
    bytes_read++;
  }

  return bytes_read;
}

static ssize_t
device_write(struct file* filp,
             const char __user* buff,
             size_t len,
             loff_t* off)
{
  if (len > BUF_LEN - 1) {
    len = BUF_LEN - 1;
  }

  if (copy_from_user(msg, buff, len)) {
    return -EFAULT;
  }

  msg[len] = '\0';
  pr_info("Received message: %s\n", msg);

  return len;
}

module_init(chardev_init);
module_exit(chardev_exit);
