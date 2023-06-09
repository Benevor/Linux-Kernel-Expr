#include "DriverFileOperation.h"
#include "charDevDriver.h"
#include <linux/kernel.h>
#include <linux/uaccess.h>

extern int DeviceOpenNumbers; // 外部变量，用于记录设备打开次数
extern char DeviceData[];     // 外部变量，用于存储设备数据

int DriverOpen(struct inode *inode, struct file *file)
{
  DeviceOpenNumbers++;
  printk(KERN_INFO "Device opened %d times.\n", DeviceOpenNumbers);
  return 0;
}

int DriverRelease(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "Device closed.\n");
  return 0;
}

// copy data from kernel's buffer to the user space
ssize_t DriverRead(struct file *file, char __user *buffer, size_t count,
                   loff_t *offset)
{
  int error_count = 0;
  size_t data_size = strlen(DeviceData); // 计算实际设备数据的大小

  // 确保要复制的字节数不超过实际设备数据的大小
  if (count > data_size)
  {
    count = data_size;
  }

  // 将内核空间的数据复制到用户空间
  error_count = copy_to_user(buffer, DeviceData, count);
  if (error_count == 0)
  {
    printk(KERN_INFO "Read %zu characters from device.\n", count);
    return count;
  }
  else
  {
    printk(KERN_INFO "Failed to read from device.\n");
    return -EFAULT;
  }
}

// copy data from user space to the buffer
ssize_t DriverWrite(struct file *file, const char __user *buffer, size_t count,
                    loff_t *offset)
{
  ssize_t ret;
  // copy data from user space to the buffer
  ret = simple_write_to_buffer(DeviceData, DEVICE_DATA_SIZE, offset, buffer,
                               count);

  if (ret >= 0)
  {
    printk(KERN_INFO "Write %zu characters to device.\n", count);
  }
  else
  {
    printk(KERN_INFO "Failed to write to device.\n");
  }
  return ret;
}
