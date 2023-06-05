#ifndef CHAR_DEV_DRIVER_H
#define CHAR_DEV_DRIVER_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>

#define DEVICE_NAME "charMsgDriver"
#define CLASS_NAME "charMsg"
#define DEVICE_DATA_SIZE 1024

extern int DeviceOpenNumbers;
extern char DeviceData[DEVICE_DATA_SIZE];

#endif
