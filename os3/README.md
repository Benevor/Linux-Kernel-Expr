```bash
make
cd call_os4_module/
make
cd ..


sudo insmod os4_module.ko 
cd call_os4_module/
sudo insmod call_os4_module_add_time.ko
sudo dmesg | tail -10

sudo rmmod call_os4_module_add_time.ko 
sudo rmmod os4_module.ko 
sudo dmesg | tail -10
```

