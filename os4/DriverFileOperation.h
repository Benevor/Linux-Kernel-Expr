#ifndef DRIVER_FILE_OPERATION_H
#define DRIVER_FILE_OPERATION_H

#include <linux/fs.h>

int DriverOpen(struct inode *inode, struct file *file);
int DriverRelease(struct inode *inode, struct file *file);
ssize_t DriverRead(struct file *file, char __user *buffer, size_t count, loff_t *offset);
ssize_t DriverWrite(struct file *file, const char __user *buffer, size_t count, loff_t *offset);

#endif
