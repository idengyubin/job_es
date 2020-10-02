#include <linux/module.h>

static int __init func_init(void) {
    printk("func_init\n"); 
    return 0;
}

static void __exit func_exit(void) {
    printk("func_exit\n");
}

static int add(int a, int b) {
    return a + b;
}

module_init(func_init);
module_exit(func_exit);

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(add);
