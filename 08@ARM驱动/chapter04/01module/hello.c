#include <linux/module.h>
extern int add(int a, int b);

static int __init hello_init(void) {
    int sum = add(1,2);
    printk("1 add 2 is %d\n", sum);
    return 0;
}

static void __exit hello_exit(void) {
    printk("hello_exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This is a simple module.");
