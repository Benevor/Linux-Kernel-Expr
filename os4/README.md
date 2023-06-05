```bash
make
cd test
make

sudo insmod charMsgModuel.ko
#查看：/dev/charMsgDriver

cd test
sudo ./test


sudo rmmod charMsgModuel
#查看：/dev/charMsgDriver（已经删除）
sudo dmesg | tail -10
```


