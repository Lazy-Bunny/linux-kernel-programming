# linux-kernel-programming
The purpose of this is to help new learner to show some example kernel programmes to start out in kernel programming and also for my personal exploration.

![Alt text](assets/penguin.PNG)

📝 All program can be build using given Makefile

### Here are steps to build Modules
```
make          # Change obj-m variable in make file before building the module.
sudo insmod <module>.ko # Inserting Module
sudo lsmod | grep <module> # Check if module is inserted or not.
sudo rmmod <module> # Removing Module
dmesg | tail/grep <pattern>  # View kernel logs
```
