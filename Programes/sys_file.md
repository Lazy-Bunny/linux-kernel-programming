## 📜 Sys file system 📜 

The Sysfs is also an usefull feature which helps to expose kernel object which enables to config easy in kernel module or driver
or whatsoever. In this sysfs is used to take input and do simple and basic crypto on it and display.

```
 	                    
       ...	             ... 
      . . ... ......... ... ..
           ..         ..
      	  ..  _    _  \..
         ..  (0)  (0)  |..
         ..            |..
          ..    \/     |..    
            ...      ./..
         ..        .....
        ..      /\\\\\\\\
       ..       |\\\\\\\\
        ..       \\\\\\\\
         ..       \\\\\\\
	         ........\\\\
             |     |  \\\\
            /|\   /|\  \\\
                        \\

       > This kernel module is making two sysfs file "encrypt" and "decrypt" under directory named
         "sysfs_example" under "/sys/kernel". by writing in "encrypt" file then, input
         will be encrypt with parmutation cipher and result will store will increase
         display brightness and as for decrypt file to decrypt input.

```
Encryption :

```
$ sudo echo "sysfss" > /sys/kernel/sysfs_example/encrypt
$ sudo cat /sys/kernel/sysfs_example/encrypt
  ysfsss
```
Decryption : 
```
$ sudo echo "ysfsss" > /sys/kernel/sysfs_example/decrypt
$ sudo cat /sys/kernel/sysfs_example/decrypt
  sysfss
```
