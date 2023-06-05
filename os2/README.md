```bash
#下载内核源码

#修改内核文件
cd /usr/src/linux-4.10.0
arch/sh/include/uapi/asm/unistd_64.h    #系统调用号 395/400      (#define __NR_xiaoxiao_func          400)
arch/x86/entry/syscalls/syscall_64.tbl  #系统调用向量表          (400     64      xiaoxiao_oper               sys_xiaoxiao_func)
include/linux/syscalls.h                #系统调用声明            (asmlinkage long sys_xiaoxiao_func(int count);)
kernel/sys.c                            #系统调用实现            (SYSCALL_DEFINE1(xiaoxiao_func,int,count))
                                                                 #(long xiaoxiao_oper(int* result,int num1,int num2,char* op))

#编译内核源码
cd /usr/src/linux-4.10.0
sudo apt-get install libncurses*  
sudo apt-get install libssl-dev
sudo make mrproper  #清除编译记录和临时文件
sudo make menuconfig  #配置内核
sudo make bzImage -j8 #编译内核烧写镜像
sudo make -j8 modules #编译模块
sudo make -j8 modules_install
sudo make install   #安装新内核
/boot #文件夹下面可以看到新编译的内核文件


#重启，更改系统默认内核版本
uname -a

gcc test.c -o test
./test
```

写在`kernel/sys.c`中的代码
```C
//my func
long xiaoxiao_oper(int* result,int num1,int num2,char* op)
{
    if(op)
    {
        if(*op == '+')
        {
            *result = num1 + num2;
        }
        else if(*op == '-')
        {
            *result = num1 - num2;
        }
        else if(*op == '*')
        {
            *result = num1*num2;
        }
        else if(*op == '\\')
        {
            if(num2!=0)
                *result = num1/num2;
            else
                printk("dived number can't be zero!\n");
        }else
            printk("unrecongized operator %c\n", *op);
    }else
    {
        printk("operation is empty.\n");
    }
    return 0;
}

SYSCALL_DEFINE1(xiaoxiao_func,int,count) {
    printk("count is:%d\n",count);
    struct timeval tstart,tend;
    do_gettimeofday(&tstart);
    int result;
    int i;
    for (i = 0; i < count; i++) {
        char op_add = '+';
        xiaoxiao_oper(&result, 10, 10, &op_add);
    }
    printk("xiaoxiao_func op_add is ok. op_add count is:%d\n", count);
    for (i = 0; i < count; i++) {
        char op_sub = '-';
        xiaoxiao_oper(&result, 20, 10, &op_sub);
    }
    printk("xiaoxiao_func op_sub is ok. op_sub count is:%d\n", count);
    for (i = 0; i < count; i++) {
        char op_mul = '*';
        xiaoxiao_oper(&result, 10, 10, &op_mul);
    }
    printk("xiaoxiao_func op_mul is ok. op_mul count is:%d\n", count);
    for (i = 0; i < count; i++) {
        char op_div = '\\';
        xiaoxiao_oper(&result, 20, 10, &op_div);
    }
    printk("xiaoxiao_func op_div is ok. op_div count is:%d\n", count);

    do_gettimeofday(&tend);
    printk("xiaoxiao_opertotal time:%ld millisec\n", 1000*(tend.tv_sec-tstart.tv_sec)+(tend.tv_usec-tstart.tv_usec)/1000);
    return 0;
}
```

