```bash
make

sudo insmod hello.ko  #插入内核
sudo insmod hello.ko num=2 name=ljb #插入内核

sudo dmesg | tail -50 #查看内核打印信息
sudo rmmod hello #移出内核
```

