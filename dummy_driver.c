#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/workqueue.h>

static int major;
static struct workqueue_struct *wq;
static struct delayed_work dw;

MODULE_LICENSE("GPL");

static struct file_operations fops= {};

static void dummy_work_handler(struct work_struct *work)
{
	printk(KERN_INFO "dummy_print");
	queue_delayed_work(wq, &dw, HZ);
}

static int dummy_init(void)
{
	printk(KERN_INFO "dummy-driver - Initialization\n");
	//register device
	major = register_chrdev(0, "dummy_driver", &fops);
	if(major < 0)
	{
		printk(KERN_ERR "dummy_driver - registering character device failed.\n");
		return major;
	}
	printk(KERN_INFO "dummy_driver - Registered with major number %d\n", major);

	//initialize work to queue
	wq = alloc_workqueue("wq", WQ_UNBOUND, 0);
	INIT_DELAYED_WORK(&dw, dummy_work_handler);
	queue_delayed_work(wq, &dw, HZ);
	return 0;
}

static void dummy_exit(void)
{
	printk(KERN_INFO "dummy_driver - Uninitializing\n");
	//destroy workqueue
	if(wq)
	{
		destroy_workqueue(wq);
	}
	unregister_chrdev(major, "dummy_driver");
}


module_init(dummy_init);
module_exit(dummy_exit);
