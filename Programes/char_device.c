#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/delay.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>

#define Dev_name "my_char_device"
#define caps_lock "/sys/class/leds/input2::capslock/brightness"
#define num_lock "/sys/class/leds/input2::numlock/brightness"
#define scroll_lock "/sys/class/leds/input2::scrolllock/brightness"

static int major;
static ssize_t chrdevice_read(struct file *filp, char __user *buff, size_t count, loff_t *ppos);
static int chrdevice_open(struct inode *node, struct file *flip);
static int chrdevice_release(struct inode *node, struct file *flip);
static ssize_t chrdevice_write(struct file *flip, const char __user *buff, size_t count,  loff_t *ppos);
void led_on_off(int t);
void file_write_b(char *name, char *buff);


void file_write_b(char *name , char *buff){
	
	struct file * file;
	ssize_t ret;
	size_t count = 1;
	loff_t pos = 0;

	file = filp_open(name , O_WRONLY, 0644);
	if(IS_ERR(file)){
		pr_info("[ CHAR_DEV ] failed to open file\n");
		return;
	}
	else
		pr_info("[ CHAR_DEV ] successfully opened the file %s\n",name);

	ret = kernel_write(file ,buff ,count ,&pos);
	
	if (ret<0)
		pr_info("[ CHAR_DEV ] failed to write into the file\n");
	else
		pr_info("[ CHAR_DEV ] successfully write into the %s file\n", name);

	filp_close(file, NULL);

}

void led_on_off(int t){

	char on = '1', off = '0';
	for (int i =0;i<t;i++){
		file_write_b(num_lock ,&on);
		msleep(1000);
		file_write_b(caps_lock ,&on);
		msleep(1000);
		file_write_b(scroll_lock ,&on);
		msleep(2000);
		file_write_b(num_lock ,&off);
		msleep(1000);
		file_write_b(caps_lock ,&off);
		msleep(1000);
		file_write_b(scroll_lock ,&off);
		msleep(2000);
	}

}

static ssize_t chrdevice_read(struct file *flip, char __user *buff, size_t count, loff_t *ppos){
	pr_info("[ CHAR_DEV ] Try to read the device file but can't read\n");
	return 0;
}
static ssize_t chrdevice_write(struct file *flip ,const char __user *buff ,size_t count ,loff_t *ppos){

	int t, ret;	
	ret = kstrtoint(buff, 10, &t);

	if (ret<0){
		pr_info("[ CHAR_DEV ] failed to get the integer\n");
		return ret;
	}
	led_on_off(t);
	pr_info("[ CHAR_DEV ] successfully done task\n");
	return count;

}

static int chrdevice_open(struct inode *node, struct file *flip){
	pr_info("[ CHAR_DEV ] tryed to open character device file\n");
	return 0;
}

static int chrdevice_release(struct inode *node, struct file *flip){
	pr_info("[ CHAR_DEV ] tryed to release character device file\n");
	return 0;
}

static struct file_operations file_ops = {
	.write = chrdevice_write,
	.read = chrdevice_read,
	.release = chrdevice_release,
	.open = chrdevice_open,
};
static struct class *cls;

static int __init blink_init(void){

	major = register_chrdev(0,Dev_name, &file_ops);
	if (major<0){
		pr_info("[ CHAR_DEV ] failed to register the device\n");
		return -ENOMEM;
	}
	
	cls = class_create(Dev_name);
	if(IS_ERR(cls)){
		pr_info("[ CHAR_DEV ] failed to create class in sysfs\n");
		return -ENOMEM;
	}
	pr_info("[ CHAR_DEV ] successfully create class in sysfs\n");

	device_create(cls ,NULL ,MKDEV(major,0) ,NULL ,Dev_name);

	pr_info("[ CHAR_DEV ] successfully register the device file\n");
	return 0;
}

static void __exit blink_exit(void){

	device_destroy(cls, MKDEV(major ,0));
	class_destroy(cls);
	unregister_chrdev(major, Dev_name);

	pr_info("[ CHAR_DEV ] successfully removed the device file\n");
}



module_init(blink_init);
module_exit(blink_exit);
MODULE_AUTHOR("Lazy-bunny");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blinking led on keyboard");

