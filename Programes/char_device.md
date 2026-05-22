## 📜 Character device driver 📜 

The character device driver is used to controll and manage the character device like keyboard. The <linux/cdev.h> gives many apis to made easy to
write drivers for character device.
```

      	 !!!!!!!!!     _     _  ___  _    _	     ^_^     _ 
      	/  ^   ^  \   	|   |  |      \  /	    (._.)___/ 
        | -O   O- |   	|---|  |---    \/	     \    _ )
        |    _    |   	|   |  |___     \_        | ||  |
        \_  ___ __/



	> This module just takes input in character device file how many times to blink the
	  capslock, numlock, scroll lock led in pattern one-after-another by setting some
	  delay in between.

```
Command :
```
$ sudo echo "2" > /dev/my_char_device
```
![Alt Text](assets/Char_Device.gif)
