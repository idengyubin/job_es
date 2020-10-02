#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

#define MAX_ARRAY 10
static int age = 100;
static char* name = "zhangsan";
static int nr = 0;
static int array[MAX_ARRAY] = {1,2,3,4,5,6,7,8,9,10};

module_param(age, int, 0644);
module_param(name, charp, 0644);
module_param_array(array, int, &nr, 0644);

static int __init hello_init(void) {
    int arrnr = 0;
    int i = 0;
    printk("name = %s\n", name);
    arrnr = nr > 0 ? nr : MAX_ARRAY;
    for(i = 0; i < arrnr; i++) {
        printk("array[%d] = %d\n", i, array[i]); 
    }

    return 0;
}

static void __exit hello_exit(void) {
    printk("hello exit----\n");
}

module_init(hello_init);
module_exit(hello_exit);
