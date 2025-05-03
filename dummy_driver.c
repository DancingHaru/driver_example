#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int dummy_init(void)
{
	printk(KERN_INFO "dummy-driver - Initialization\n");
	return 0;
}

static void dummy_exit(void)
{
	printk(KERN_INFO "dummy-driver - Uninitializing\n");
}


module_init(dummy_init);
module_exit(dummy_exit);
