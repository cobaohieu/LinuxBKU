#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define MAX_DEV 2

static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t device_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t device_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);
static const struct file_operations device_fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
    .read = device_read,
    .write = device_write};

struct mychar_device_data
{
    struct cdev cdev;
};

static int dev_major = 0;
static struct class *device_class = NULL;
static struct mychar_device_data device_data[MAX_DEV];

static int device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}

static int __init device_init(void)
{
    int err, i;
    dev_t dev;
    err = alloc_chrdev_region(&dev, 0, MAX_DEV, "COBAOHIEU");
    dev_major = MAJOR(dev);
    device_class = class_create(THIS_MODULE, "COBAOHIEU");
    device_class->dev_uevent = device_uevent;
    for (i = 0; i < MAX_DEV; i++)
    {
        cdev_init(&device_data[i].cdev, &device_fops);
        device_data[i].cdev.owner = THIS_MODULE;
        cdev_add(&device_data[i].cdev, MKDEV(dev_major, i), 1);
        device_create(device_class, NULL, MKDEV(dev_major, i), NULL, "COBAOHIEU-%d", i);
    }
    return 0;
}

static int device_open(struct inode *inode, struct file *file)
{
    printk("COBAOHIEU: Device open\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk("COBAOHIEU: Device close\n");
    return 0;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("COBAOHIEU: Device ioctl\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    uint8_t *data = "Hello from the kernel world!\n";
    size_t datalen = strlen(data);
    printk("Reading device: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));
    if (count > datalen)
    {
        count = datalen;
    }
    if (copy_to_user(buf, data, count))
    {
        return -EFAULT;
    }
    return count;
}

static ssize_t device_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    size_t maxdatalen = 30, ncopied;
    uint8_t databuf[maxdatalen];
    printk("Writing device: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));
    if (count != 1)
    {
        if (count < maxdatalen)
        {
            maxdatalen = count;
        }
        ncopied = copy_from_user(databuf, buf, maxdatalen);
        if (ncopied == 0)
        {
            printk("Copied %zd bytes from the user\n", maxdatalen);
        }
        else
        {
            printk("Could't copy %zd bytes from the user\n", ncopied);
        }
        databuf[maxdatalen] = 0;
        printk("Data from the user: %s\n", databuf);
        // return count;
    }
    else
    {
        databuf[maxdatalen] = 0;
        printk("Data from the user: -EFAULT\n");
        // return -EFAULT;
    }
    return count;
}

static void __exit device_exit(void)
{
    int i;
    for (i = 0; i < MAX_DEV; i++)
    {
        device_destroy(device_class, MKDEV(dev_major, i));
    }
    class_unregister(device_class);
    class_destroy(device_class);
    unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Co Bao Hieu");
MODULE_DESCRIPTION("Lab 10 exercise BOSCH LINUX Dev Course");
MODULE_VERSION("0.1");

module_init(device_init);
module_exit(device_exit);
