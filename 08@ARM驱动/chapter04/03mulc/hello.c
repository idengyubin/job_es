#include <linux/module.h>
#include <linux/init.h>
//#include "func.h"

MODULE_LICENSE("GPL");
extern int add(int a, int b);
static int __init hello_init(void) {
    int sum = add(1,3);
    printk("add(1,3) ----> %d\n", sum);
    return 0;
}

static void __exit hello_exit(void) {
    printk("hello_exit----\n");
}

module_init(hello_init);
module_exit(hello_exit);
