#include "charDevDriver.h"
#include "DriverFileOperation.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux character driver example");



// linux操作系统中一切都是文件,设备也是文件。*linux/fs.h定义file_operations结构体
// 这里定义文件操作的相关联的回调函数
// 字符设备的基本功能包括打开,关闭,读取,写入

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = DriverOpen,
    .release = DriverRelease,
    .read = DriverRead,
    .write = DriverWrite,
};

static int MajorNumber;
static struct class *CharMsgDriverClass = NULL;
static struct device *CharMsgDriverDevice = NULL;

int DeviceOpenNumbers= 0;
char DeviceData[DEVICE_DATA_SIZE];

static int __init CharMsgDriverInit(void) {
    MajorNumber = register_chrdev(0, DEVICE_NAME, &fops);//Linux内核中用于注册字符设备驱动程序的函数.参数1：传递0，则表示由内核自动分配主设备号。参数3：驱动程序的回调函数，用于处理设备的操作。
    if (MajorNumber < 0) {
        printk(KERN_ALERT "Failed to register a major number.\n");
        return MajorNumber;
    }
    printk(KERN_INFO "Registered correctly with major number %d.\n", MajorNumber);

    // class_create可以用它来创建一个类，这个类存放于sysfs下面，一旦创建好了这个类，再调用device_create(…)函数来在/dev目录下创建相应的设备节点。
    // 这样，加载模块的时候，用户空间中的udev会自动响应device_create(…)函数，去/sysfs下寻找对应的类从而创建设备节点。

    CharMsgDriverClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(CharMsgDriverClass)) {
        unregister_chrdev(MajorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create device class.\n");
        return PTR_ERR(CharMsgDriverClass);
    }

    CharMsgDriverDevice = device_create(CharMsgDriverClass, NULL, MKDEV(MajorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(CharMsgDriverDevice)) {
        class_destroy(CharMsgDriverClass);
        unregister_chrdev(MajorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device.\n");
        return PTR_ERR(CharMsgDriverDevice);
    }

    printk(KERN_INFO "CharMsgDriver: device class created correctly.\n");
    return 0;
}

static void __exit CharMsgDriverExit(void) {
    device_destroy(CharMsgDriverClass, MKDEV(MajorNumber, 0));
    class_unregister(CharMsgDriverClass);
    class_destroy(CharMsgDriverClass);
    unregister_chrdev(MajorNumber, DEVICE_NAME);
    printk(KERN_INFO "CharMsgDriver: Goodbye from the LKM!\n");
}

module_init(CharMsgDriverInit);
module_exit(CharMsgDriverExit);
