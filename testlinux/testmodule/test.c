#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/kfifo.h>

//cat /proc/devices
//mknod /dev/testmem0 c 230 0

#define MEM_SIZE 0x1000
#define MEM_MAGIC 'g'
#define MEM_CLEAR _IO(MEM_MAGIC, 0)
#define MEM_MAJOR 230
#define DEVICE_NUM 10

static int mem_major = MEM_MAJOR;
module_param(mem_major, int, S_IRUGO);

struct mem_dev{
    struct cdev cdev;
    struct mutex mtx;
    wait_queue_head_t r_wait;
    wait_queue_head_t w_wait;
    unsigned char mem[MEM_SIZE];
    struct kfifo fifo;
};
struct mem_dev *g_devp;


static char *test_name="test name";
module_param(test_name, charp, S_IRUGO);

static int mem_open(struct inode *inode, struct file *filp)
{
    struct mem_dev *dev = container_of(inode->i_cdev, struct mem_dev, cdev);
    filp->private_data = dev;
    return 0;
}

static int mem_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static long mem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct mem_dev *dev = filp->private_data;
    switch (cmd){
    case MEM_CLEAR:
        mutex_lock(&dev->mtx);
        memset(dev->mem, 0, MEM_SIZE);
        printk(KERN_INFO "clear mem\n");
        mutex_unlock(&dev->mtx);
    break;
    default:
        return -EINVAL;
    break;
    }
    return 0;
}

static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    struct mem_dev *dev = filp->private_data;

    if (p >= MEM_SIZE)
        return 0;
    
    if (count > MEM_SIZE - p)
        count = MEM_SIZE - p;

    mutex_lock(&dev->mtx);
    if (copy_to_user(buf, dev->mem + p, count))
        ret = -EFAULT;
    else{
        *ppos += count;
        ret = count;
        printk(KERN_INFO "read success\n");
    }
    mutex_unlock(&dev->mtx);
    return ret;
}

static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    struct mem_dev *dev = filp->private_data;

    if (p >= MEM_SIZE)
        return 0;
    
    if (count > MEM_SIZE - p)
        count = MEM_SIZE - p;
    
    mutex_lock(&dev->mtx);
    if (copy_from_user(dev->mem + p, buf, count)){
    //if (kfifo_from_user(&dev->fifo, buf, count) )
        printk(KERN_INFO "write failed\n");
        ret = -EFAULT;
    }
    else{
        *ppos += count;
        ret = count;
        printk(KERN_INFO "write success\n");
    }
    mutex_unlock(&dev->mtx);
    return ret;
}

static loff_t mem_llseek(struct file *filp, loff_t offset, int orig)
{
    loff_t ret = 0;
    struct mem_dev *dev = filp->private_data;

    mutex_lock(&dev->mtx);
    switch (orig){
    case 0:
        if (offset < 0){
            ret = -EINVAL;
            break;
        }
        if ((unsigned int)offset > MEM_SIZE){
            ret = -EINVAL;
            break;
        }
        filp->f_pos = (unsigned int)offset;
        ret = filp->f_pos;
    break;
    case 1:
        if ((filp->f_pos + offset) > MEM_SIZE){
            ret = -EINVAL;
            break;
        }
        if ((filp->f_pos + offset) < 0){
            ret = -EINVAL;
            break;
        }
        filp->f_pos += offset;
        ret = filp->f_pos;
    break;
    default:
        ret = -EINVAL;
    break;
    }
    mutex_unlock(&dev->mtx);
    return ret;
}

static const struct file_operations mem_fops = {
    .owner = THIS_MODULE,
    .llseek = mem_llseek,
    .read = mem_read,
    .write = mem_write,
    .unlocked_ioctl = mem_ioctl,
    .open = mem_open,
    .release = mem_release,
};

static void mem_setup_dev(struct mem_dev *dev, int index)
{
    int err, devno = MKDEV(mem_major, index);

    cdev_init(&dev->cdev, &mem_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
        printk(KERN_INFO "cdev_add failed err:%d\n", err);
    mutex_init(&dev->mtx);
    dev->current_len = 0;
    init_waitqueue_head(&dev->r_wait);
    init_waitqueue_head(&dev->w_wait);
    kfifo_init(&dev->fifo, dev->mem, MEM_SIZE);
}

static int __init test_init(void)
{
    int ret, i;
    //printk(KERN_INFO "my test module test_name:%s\n", test_name);
    dev_t devno = MKDEV(mem_major, 0);
    if (mem_major){
        ret = register_chrdev_region(devno, DEVICE_NUM, "testmem");
    }else{
        ret = alloc_chrdev_region(&devno, 0, DEVICE_NUM, "testmem");
        mem_major = MAJOR(devno);
    }
    if (ret < 0){
        printk(KERN_INFO "create dev failed\n");
        return ret;
    }else
        printk(KERN_INFO "create dev success\n");   
    
    g_devp = kzalloc(sizeof(struct mem_dev) * DEVICE_NUM, GFP_KERNEL);
    if (!g_devp){
        ret = -ENOMEM;
        goto fail_malloc;
    }
    
    for (i = 0;i < DEVICE_NUM; i++){
        mem_setup_dev(g_devp + i, i);
    }
    
    return 0;

    fail_malloc:
    unregister_chrdev_region(devno, DEVICE_NUM);
    return ret;
}
module_init(test_init);

static void __exit test_exit(void)
{
    int i;
    //printk(KERN_INFO "my test exit\n");
    if (g_devp){
        for (i = 0; i < DEVICE_NUM; i++){
            cdev_del(&(g_devp + i)->cdev);
        }
        
        kfree(g_devp);
        unregister_chrdev_region(MKDEV(mem_major, 0), DEVICE_NUM);
        printk(KERN_INFO "free dev success \n");
    }
}
module_exit(test_exit);

MODULE_AUTHOR("chenyue <chenyue0102@gmail.com>");
MODULE_LICENSE("GPL v2");
//MODULE_DESCRIPTION("my test driver");
//MODULE_ALIAS("alias");