#include <linux/init.h>
#include <linux/module.h>

static char *input_string = "input string";
module_param(input_string, charp, S_IRUGO);

static int input_num = 0;
module_param(input_num, int, S_IRUGO);

static int __init hello_init(void)
{
	printk(KERN_INFO "hello init\n");
	printk(KERN_INFO "hello input string:%s\n", input_string);
	printk(KERN_INFO "hello input num:%d\n", input_num);
	return 0;
}

module_init(hello_init);

int add_integar(int a, int b)
{
	return a + b;
}
EXPORT_SYMBOL_GPL(add_integar);

int sub_integar(int a, int b)
{
	return a - b;
}
EXPORT_SYMBOL_GPL(sub_integar);

static void __exit hello_exit(void)
{
	printk(KERN_INFO "hello exit\n");
}
module_exit(hello_exit);

MODULE_AUTHOR("chenyue <chenyue0102@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("hello descrption");
MODULE_VERSION("V1.0");
MODULE_ALIAS("module alias");
