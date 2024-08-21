#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Khaustovdn");
MODULE_DESCRIPTION("Task 2");

#define PROC_NAME "hello"
#define MSG_SIZE 256

static char* msg;
static int len = 0;
static int temp = 0;

ssize_t
read_proc(struct file* filp,
          char __user* buf,
          size_t count,
          loff_t* offp);
ssize_t
write_proc(struct file* filp,
           const char __user* buf,
           size_t count,
           loff_t* offp);

ssize_t
read_proc(struct file* filp,
          char __user* buf,
          size_t count,
          loff_t* offp)
{
  if (temp == 0) {
    return 0;
  }

  if (count > temp) {
    count = temp;
  }

  if (copy_to_user(buf, msg + (len - temp), count)) {
    return -EFAULT;
  }

  temp -= count;
  return count;
}

ssize_t
write_proc(struct file* filp,
           const char __user* buf,
           size_t count,
           loff_t* offp)
{
  if (count > MSG_SIZE - 1) {
    count = MSG_SIZE - 1;
  }

  if (copy_from_user(msg, buf, count)) {
    return -EFAULT;
  }

  msg[count] = '\0';
  len = count;
  temp = len;
  return count;
}

static const struct proc_ops proc_fops = {
  .proc_read = read_proc,
  .proc_write = write_proc,
};

static void
create_new_proc_entry(void)
{
  msg = kmalloc(MSG_SIZE * sizeof(char), GFP_KERNEL);
  if (!msg) {
    printk(KERN_ERR "Failed to allocate memory for msg\n");
    return;
  }

  temp = 0;
  proc_create(PROC_NAME, 0666, NULL, &proc_fops);
}

static int __init
proc_init(void)
{
  create_new_proc_entry();
  return 0;
}

static void __exit
proc_cleanup(void)
{
  remove_proc_entry(PROC_NAME, NULL);
  kfree(msg);
}

module_init(proc_init);
module_exit(proc_cleanup);
