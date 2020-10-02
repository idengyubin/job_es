#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "chrdev_drv"
int major = 0;

static int chrdev_open(struct inode* pinode, struct file* pfile) {
    printk("%s\n", __FUNCTION__);
    gpio_set_value(S5PV210_GPC1(3), 1);
    return 0;
}

static int chrdev_release(struct inode* pinode, struct file* pfile) {
    printk("%s\n", __FUNCTION__);
    gpio_set_value(S5PV210_GPC1(3), 0);
    return 0;
}

static ssize_t chrdev_read(struct file* pfile, char __user *buf, size_t count, loff_t* offset) {
    printk("%s\n", __FUNCTION__);
    return count;
}

static ssize_t chrdev_write(struct file* pfile, const char __user *buf, size_t count, loff_t* offset) {
    printk("%s\n", __FUNCTION__);
    return count;
}

static loff_t chrdev_llseek(struct file* pfile, loff_t offset, int origin) {
    printk("%s\n", __FUNCTION__);
    return 0;
}

static int chrdev_ioctl(struct file* pfile, unsigned int cmd, unsigned long arg) {
    printk("%s\n", __FUNCTION__);
    return 0;
}

struct file_operations dev_ops = {
    .open = chrdev_open,
    .release = chrdev_release,
    .read = chrdev_read,
    .write = chrdev_write,
    .llseek = chrdev_llseek,
    .unlocked_ioctl = chrdev_ioctl,
};

struct cdev my_cdev;

static int __init chrdev_init(void) {
    int ret;
    dev_t dev;
    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    major = MAJOR(dev);

    cdev_init(&my_cdev, &dev_ops);
    ret = cdev_add(&my_cdev, dev, 1);

    if(ret < 0) {
        printk("register_chrdev_region err\n"); 
        return ret;
    }
    gpio_request(S5PV210_GPC1(3), "LED1");

    gpio_direction_output(S5PV210_GPC1(3), 0);

    return 0;
}

static void __exit chrdev_exit(void) {
    printk("%s\n", __FUNCTION__);
    gpio_direction_output(S5PV210_GPC1(3), 0);
    gpio_free(S5PV210_GPC1(3));
    cdev_del(&my_cdev);

    unregister_chrdev_region(MKDEV(major, 0),1);
}
module_init(chrdev_init);
module_exit(chrdev_exit);
