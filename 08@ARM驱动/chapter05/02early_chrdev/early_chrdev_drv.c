#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "early_chrdev_drv"
int major = 0;

static int early_chrdev_open(struct inode* pinode, struct file* pfile) {
    printk("%s\n", __FUNCTION__);
    return 0;
}

static int early_chrdev_release(struct inode* pinode, struct file* pfile) {
    printk("%s\n", __FUNCTION__);
    return 0;
}

static ssize_t early_chrdev_read(struct file* pfile, char __user *buf, size_t count, loff_t* offset) {
    printk("%s\n", __FUNCTION__);
    return count;
}

static ssize_t early_chrdev_write(struct file* pfile, const char __user *buf, size_t count, loff_t* offset) {
    printk("%s\n", __FUNCTION__);
    return count;
}

static loff_t early_chrdev_llseek(struct file* pfile, loff_t offset, int origin) {
    printk("%s\n", __FUNCTION__);
    return 0;
}

static int early_chrdev_ioctl(struct file* pfile, unsigned int cmd, unsigned long arg) {
    printk("%s\n", __FUNCTION__);
    return 0;
}

struct file_operations dev_fops = {
    .owner      = THIS_MODULE,
    .open       = early_chrdev_open,
    .release    = early_chrdev_release,
    .write      = early_chrdev_write,
    .read       = early_chrdev_read,
    .llseek     = early_chrdev_llseek,
    .unlocked_ioctl = early_chrdev_ioctl,
};

static int __init early_chrdev_init(void) {
    int ret;

    // 主设备号是0时，由内核动态分配一个
    major = register_chrdev(major, DEVICE_NAME, &dev_fops);
    if(major < 0) {
        printk("register_chrdev err\n"); 
        ret = major;
        return ret;
    }

    printk("%s\n", __FUNCTION__);
    return 0;
}

static void __exit early_chrdev_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk("%s\n", __FUNCTION__);
}

module_init(early_chrdev_init);
module_exit(early_chrdev_exit);
