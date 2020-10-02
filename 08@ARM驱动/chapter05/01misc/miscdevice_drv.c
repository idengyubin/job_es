#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

#define LEDS_MAJOR 255
#define DEVICE_NAME "miscdevice_drv"

MODULE_LICENSE("GPL");

static int miscdrv_open(struct inode* pinode, struct file* pfile) {
    printk("%s\n",__FUNCTION__);
    return 0;
}

static int miscdrv_ioctl(struct file* pfile, unsigned int cmd, unsigned long arg) {
    printk("%s\n",__FUNCTION__);
    return 0;
}

static ssize_t miscdrv_read(struct file* pfile, char __user *buf, size_t count, loff_t* offset) {
    printk("%s\n",__FUNCTION__);
    return 0;
}

static ssize_t miscdrv_write(struct file* pfile, const char __user *buf, size_t count, loff_t* offset) {
    printk("%s\n",__FUNCTION__);
    return 0;
}

static loff_t miscdrv_llseek(struct file* pfile, loff_t loff, int origin) {
    printk("%s\n",__FUNCTION__);
    return 0;
}

static int miscdrv_release(struct inode* pinode, struct file* pfile) {
    printk("%s\n",__FUNCTION__);
    return 0;
}

static struct file_operations drv_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = miscdrv_ioctl,
    .open           = miscdrv_open,
    .read           = miscdrv_read,
    .write          = miscdrv_write,
    .llseek         = miscdrv_llseek,
    .release        = miscdrv_release,
};

static struct miscdevice misc = {
    .minor  = LEDS_MAJOR,
    .name   = DEVICE_NAME,
    .fops   = &drv_fops,
};

static int __init miscdrv_init(void) {
    int ret;
    ret = misc_register(&misc);

    if(ret < 0) {
        printk("misc_register err\n"); 
    }

    return ret;
}

static void __exit miscdrv_exit(void) {
    misc_deregister(&misc);
    printk("miscdrv_exit \n");
}

module_init(miscdrv_init);
module_exit(miscdrv_exit);
