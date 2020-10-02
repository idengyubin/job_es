#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

static int major;

struct led_resource {
    int gpio;
    char* name;
};

struct led_cmd {
    int index;
    int cmd;
};

static struct led_resource led_info[] = {
    [0] = {
        .gpio = S5PV210_GPC1(3),
        .name = "LED1"
    },
    [1] = {
        .gpio = S5PV210_GPC1(4),
        .name = "LED2"
    }
};

static struct cdev led_cdev;
static int led_status;

static ssize_t led_read(struct file* pfile, char __user *buf, size_t count, loff_t* offset) {
    copy_to_user(buf, &led_status, sizeof(led_status));

    printk("%s\n", __FUNCTION__);

    return count;
}

static ssize_t led_write(struct file* pfile, const char __user *buf, size_t count, loff_t* offset) {
    struct led_cmd cmd;

    copy_from_user(&cmd, buf, sizeof(cmd));

    printk("%s ---> cmd = %d\n", __FUNCTION__, cmd.cmd);

    if(cmd.cmd == 1) {
        if(cmd.index == 1)
            gpio_set_value(led_info[0].gpio, 1);
        else if(cmd.index == 2)
            gpio_set_value(led_info[1].gpio, 1);
    } else if(cmd.cmd == 0) {
        if(cmd.index == 1)
            gpio_set_value(led_info[0].gpio, 0);
        else if(cmd.index == 2)
            gpio_set_value(led_info[1].gpio, 0);
    }

    // led_status = cmd;
    return count;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .read = led_read,
    .write = led_write
};

static int __init led_init(void) {
    dev_t dev;
    int i;
    alloc_chrdev_region(&dev, 0, 1, "leds");
    major = MAJOR(dev);

    cdev_init(&led_cdev, &led_fops);
    cdev_add(&led_cdev, dev, 1);

    for(i = 0; i < ARRAY_SIZE(led_info); i++) {
        gpio_request(led_info[i].gpio, led_info[i].name) ;
        gpio_direction_output(led_info[i].gpio, 0);
    }
    return 0;
}

static void __exit led_exit(void) {
    int i;

    for(i = 0; i < ARRAY_SIZE(led_info); i++) {
        gpio_set_value(led_info[i].gpio, 0) ;
        gpio_free(led_info[i].gpio);
    }

    cdev_del(&led_cdev);
    unregister_chrdev_region(MKDEV(major, 0), 1);
}

module_init(led_init);
module_exit(led_exit);
