## 📜 Proc file system 📜
This is a integral part of linux kernel which essentialy have diverse application which can me found on internel. In this example i just showed one of use of proc file system.

_Read from proc file "eg_proc_file"_
```
$ cat /proc/eg_proc_file
 Hello proc read successfully
```
_Write to proc file "eg_proc_file"_
```
$ sudo echo "hey" > /proc/eg_proc_file
$ sudo dmesg | grep Proc
 [21789.446857] Proc : proc file created /proc/mouse_proc_file
 [21841.553285] Proc : Hey proc write successfully
```
