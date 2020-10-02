#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

struct btn_resource {
    int gpio;
    int irq;
    char* name;
};

static struct btn_resource btn_info[] = {
    [0] = {
        .gpio = S5PV210_GPH0(0),
        .irq = IRQ_EINT(0),
        .name = "KEY1"
    }
};

static int major;
static struct cdev btn_cdev;
static struct class* cls;
static wait_queue_head_t btn_wq;
static unsigned char key_val;
static int ispress;

static ssize_t btn_read(struct file* pfile, char __user *buf, size_t count, loff_t* offset) {
    int ret;

    if(pfile->f_flags & O_NONBLOCK) {
        if(!ispress) {
            printk("No date!\n"); 
            return -EAGAIN;
        }
    }

    wait_event_interruptible(btn_wq, ispress);
    ispress = 0;
    ret = copy_to_user(buf, &key_val, 1);
    if(ret < 0) {
        printk("copy_to_user error\n"); 
    }
    
    return count;
}

static struct file_operations dev_fops = {
    .owner = THIS_MODULE,
    .read = btn_read
};

static irqreturn_t btn_isr(int irq, void* dev_id) {
    unsigned int pinstate;
    
    struct btn_resource *pdate = (struct btn_resource*)dev_id;
    pinstate = gpio_get_value(pdate->gpio);
    if(pinstate == 1)
        key_val = 0x50;
    else if(pinstate == 0)
        key_val = 0x51;

    ispress = 1;
    wake_up_interruptible(&btn_wq);

    return IRQ_HANDLED;
}

static int __init btn_init(void) {
    dev_t dev;
    int i;
    int ret;

    alloc_chrdev_region(&dev, 0, 1, "btn");
    major = MAJOR(dev);
    cdev_init(&btn_cdev, &dev_fops);
    cdev_add(&btn_cdev, dev, 1);
    
    cls = class_create(THIS_MODULE, "btn");
    device_create(cls, NULL, dev, NULL, "mybtn");

    for(i = 0; i < ARRAY_SIZE(btn_info); i++) {
        gpio_request(btn_info[i].gpio, btn_info[i].name);
        ret = request_irq(btn_info[i].irq, btn_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                btn_info[i].name, &btn_info[i]);
        if(ret < 0) {
            printk("error\n"); 
        }
    }

    init_waitqueue_head(&btn_wq);
    return 0;
}

static void __exit btn_exit(void) {
    int i;
    dev_t dev;

    dev = MKDEV(major, 0);
    for(i = 0; i < ARRAY_SIZE(btn_info); i++) {
        gpio_free(btn_info[i].gpio); 
        free_irq(btn_info[i].irq, &btn_info[i]);
    }

    device_destroy(cls, dev);
    class_destroy(cls);

    cdev_del(&btn_cdev);

    unregister_chrdev_region(dev, 1);
}

module_init(btn_init);
module_exit(btn_exit);
