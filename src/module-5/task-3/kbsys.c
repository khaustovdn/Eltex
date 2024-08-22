#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kd.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/tty.h>
#include <linux/vt.h>
#include <linux/vt_kern.h>
#include <linux/console_struct.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Khaustovdn");
MODULE_DESCRIPTION("Keyboard with sys.");

static struct timer_list my_timer;
static struct tty_driver* my_driver;
static struct kobject* mymodule;

static unsigned long kbledstatus = 0;
static int myvariable = 0;

#define ALL_LEDS_ON 0x07
#define RESTORE_LEDS 0xFF

static ssize_t
myvariable_show(struct kobject* kobj,
                struct kobj_attribute* attr,
                char* buf)
{
  return sprintf(buf, "%d\n", myvariable);
}

static ssize_t
myvariable_store(struct kobject* kobj,
                 struct kobj_attribute* attr,
                 char* buf,
                 size_t count)
{
  sscanf(buf, "%du", &myvariable);
  return count;
}

static struct kobj_attribute myvariable_attribute =
  __ATTR(myvariable,
         0660,
         myvariable_show,
         (void*)myvariable_store);

static void
my_timer_func(struct timer_list* unused)
{
  struct tty_struct* t = vc_cons[fg_console].d->port.tty;

  if (kbledstatus == ALL_LEDS_ON)
    kbledstatus = RESTORE_LEDS;
  else
    kbledstatus = 1 << myvariable;

  (my_driver->ops->ioctl)(t, KDSETLED, kbledstatus);

  my_timer.expires = jiffies;
  add_timer(&my_timer);
}

static int __init
kbsys_init(void)
{
  int i;
  int error = 0;

  pr_info("kbsys: loading\n");
  pr_info("kbsys: fgconsole is %x\n", fg_console);

  mymodule =
    kobject_create_and_add("mymodule", kernel_kobj);
  if (!mymodule)
    return -ENOMEM;

  error =
    sysfs_create_file(mymodule, &myvariable_attribute.attr);
  if (error) {
    pr_info("failed to create the myvariable file "
            "in /sys/kernel/mymodule\n");
  }

  for (i = 0; i < MAX_NR_CONSOLES; i++) {
    if (!vc_cons[i].d)
      break;
    pr_info("poet_atkm: console[%i/%i] #%i, tty %p\n",
            i,
            MAX_NR_CONSOLES,
            vc_cons[i].d->vc_num,
            (void*)vc_cons[i].d->port.tty);
  }
  pr_info("kbsys: finished scanning consoles\n");

  my_driver = vc_cons[fg_console].d->port.tty->driver;
  pr_info("kbsys: tty driver name %s\n",
          my_driver->driver_name);

  timer_setup(&my_timer, my_timer_func, 0);
  my_timer.expires = jiffies;
  add_timer(&my_timer);

  return error;
}

static void __exit
kbsys_cleanup(void)
{
  pr_info("kbsys: unloading...\n");
  del_timer(&my_timer);
  (my_driver->ops->ioctl)(vc_cons[fg_console].d->port.tty,
                          KDSETLED,
                          RESTORE_LEDS);
  kobject_put(mymodule);
}

module_init(kbsys_init);
module_exit(kbsys_cleanup);
