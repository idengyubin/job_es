#include <linux/module.h>


static int  __init hello_init(void) {
    printk(KERN_EMERG "KERN_EMERG\n");
    printk(KERN_ALERT "KERN_ALERT\n");
    printk(KERN_CRIT "KERN_CRIT\n");
    printk(KERN_ERR "KERN_ERR\n");
    printk(KERN_WARNING "KERN_WARNING\n");
    printk(KERN_NOTICE "KERN_NOTICE\n");
    printk("<6>""KERN_INFO\n");
    printk("<7>""KERN_DEBUG\n");
    return 0;
}

static  void  __exit hello_exit(void) {
    printk("hello_exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
