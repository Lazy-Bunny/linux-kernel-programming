# Linux-Kernel-Programming
This repo have collection of simple Linux kernel modules that demonstrate kernel features and interfaces.  
Useful as a reference for learning kernel module development and driver programming in linux.

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
