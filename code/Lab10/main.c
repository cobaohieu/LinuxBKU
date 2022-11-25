#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define MAX_DEV 2
#define PROCFS_MAX_SIZE 1024
#define PROCFS_NAME "buffer1k"

static int mychardev_open(struct inode *inode, struct file *file);
static int mychardev_release(struct inode *inode, struct file *file);
static long mychardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static const char data[] = "Hello world from kernel mode!n";
static const ssize_t datalen = sizeof(data);
static ssize_t mychardev_read(struct file *file, char __user *buf, size_t count,
                              loff_t *offset);
static ssize_t mychardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);
static const struct file_operations mychardev_fops = {
    .owner = THIS_MODULE,
    .open = mychardev_open,
    .release = mychardev_release,
    .unlocked_ioctl = mychardev_ioctl,
    .read = mychardev_read,
    .write = mychardev_write};

struct mychar_device_data
{
    struct cdev cdev;
};

static char procfs_buffer[PROCFS_MAX_SIZE];
static int dev_major = 0;
static struct class *mychardev_class = NULL;
static struct mychar_device_data mychardev_data[MAX_DEV];

static int mychardev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}

static int __init mychardev_init(void)
{
    int err, i;
    dev_t dev;
    err = alloc_chrdev_region(&dev, 0, MAX_DEV, "mychardev");
    dev_major = MAJOR(dev);
    mychardev_class = class_create(THIS_MODULE, "mychardev");
    mychardev_class->dev_uevent = mychardev_uevent;
    for (i = 0; i < MAX_DEV; i++)
    {
        cdev_init(&mychardev_data[i].cdev, &mychardev_fops);
        mychardev_data[i].cdev.owner = THIS_MODULE;
        cdev_add(&mychardev_data[i].cdev, MKDEV(dev_major, i), 1);
        device_create(mychardev_class,
                      NULL,
                      MKDEV(dev_major,
                            i),
                      NULL,
                      "mychardev-%d", i);
    }
    return 0;
}

static void __exit mychardev_exit(void)
{
    int i;
    for (i = 0; i < MAX_DEV; i++)
    {
        device_destroy(mychardev_class, MKDEV(dev_major, i));
    }
    class_unregister(mychardev_class);
    class_destroy(mychardev_class);
    unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

static int mychardev_open(struct inode *inode, struct file *file)
{
    printk("COBAOHIEU: Device open\n");
    return 0;
}

static int mychardev_release(struct inode *inode, struct file *file)
{
    printk("COBAOHIEU: Device successfully closed\\n");
    return 0;
}

static long mychardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("COBAOHIEU: Device ioctl\n");
    return 0;
}

static ssize_t mychardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    // uint8_t *data = "Hello from the kernel world!\n";
    // size_t size_requested;
    // size_t datalen = strlen(data); // size_of_message
    // char checks[0];
    printk("Reading device: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));
    /* If position is behind the end of a file we have nothing to read */
    if (*offset >= datalen)
        return 0;

    /* If a user tries to read more than we have, read only as many bytes as we have */
    if (*offset + count > datalen)
    {
        count = datalen - *offset;
    }

    if (copy_to_user(buf, data + *offset, count) != 0)
    {
        return -EFAULT;
    }

    /* Move reading position */
    *offset += count;

    return count;
    // if (copy_to_user(checks, data, count))
    // {
    //     return -EINVAL;
    // }
    // if (count >= size_requested)
    // {
    //     size_requested = datalen;
    // }
    // else
    // {
    //     size_requested = count;
    // }
    // if (copy_to_user(buf, data, count))
    // {
    //     return -EFAULT;
    // }
    // return size_requested;
    // // return simple_read_from_buffer(buf, length, offset, &kbuffer, BUFF_LEN);
}

static ssize_t mychardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    size_t maxdatalen = 30, ncopied;
    uint8_t databuf[maxdatalen];
    printk("Writing device: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));
    if (count < maxdatalen)
    {
        maxdatalen = count;
    }
    // *offset += maxdatalen;

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
    // if (databuf[maxdatalen] != '\0')
    // {
    //     return -EFAULT;
    // }
    printk("Data from the user: %s\n", databuf);
    if (copy_from_user(count, buf, maxdatalen))
    {
        return -EFAULT;
    }
    return count;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Co Bao Hieu");
MODULE_DESCRIPTION("Lab 10 exercise");
MODULE_VERSION("0.1");

module_init(mychardev_init);
module_exit(mychardev_exit);