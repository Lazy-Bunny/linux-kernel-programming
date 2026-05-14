#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/string.h>

struct kobject sysfs_kobj;
char encrypt_buffer[100];
char decrypt_buffer[100];
void crypto(char *buf, size_t size);

void crypto(char *buf, size_t size){
	char temp;
	for ( size_t i = 0; i < size-1; i += 2 ){
		temp = buf[i];
		buf[i] = buf[i+1];
		buf[i+1] = temp;
	}
}



static ssize_t sysfs_show(struct kobject *kobj, struct attribute *attr, char *buf){
	
	int ret;
	if ( strcmp(attr->name, "encrypt") ){
		ret  = sysfs_emit(buf, "%s\n", encrypt_buffer);
		pr_info("[ SYSFS ] trying to display content of encrypt file.\n");
	}
	else {
		ret = sysfs_emit(buf, "%s\n", decrypt_buffer);
		pr_info("[ SYSFS ] trying to display content of decrypt file.\n");

	}

	if ( ret < 0 ){
		pr_info("[ SYSFS ] Can't able to write to the buf\n");
		return - ENOMEM;
	}

	pr_info("[ SYSFS ] successfully displayed.\n");
	return ret;
}

static ssize_t sysfs_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count){
	
	if ( strcmp(attr->name, "encrypt") ){
		strncpy(encrypt_buffer, buf, count);
		crypto(encrypt_buffer, count);
		pr_info("[ SYSFS ] Successfully write to encrypt file.\n");
	}
	else{
		strncpy(decrypt_buffer, buf, count);
		crypto(decrypt_buffer, count);
		pr_info("[ SYSFS ] Successfully write to decrypt file.\n");
	}
	return count;
}

static void sysfs_release(struct kobject *kobj){
	pr_info("[ SYSFS ] The sysfs file has been realeased\n");
}

struct sysfs_ops my_sysfs_ops = {
	.show = sysfs_show,
	.store = sysfs_store,
};

static struct attribute sysfs_file_encrypt_in = {
	.name = "encrypt",
	.mode = 0664,
};

static struct attribute sysfs_file_decrypt_out = {
	.name = "decrypt",
	.mode = 0664,
};

static struct attribute *my_file_attrs[] = {
 &sysfs_file_encrypt_in,
 &sysfs_file_decrypt_out,
 NULL,
};

ATTRIBUTE_GROUPS(my_file);

static const struct kobj_type my_sysfs_type = {
	.sysfs_ops = &my_sysfs_ops,
	.release = sysfs_release,
	.default_groups = my_file_groups,
};

static int __init sysfs_start (void){
	
	int ret;
	ret = kobject_init_and_add(&sysfs_kobj, &my_sysfs_type, kernel_kobj, "%s", "sysfs_example");
	if (ret){
		pr_info("[ SYSFS ] Failed to create kobject and sysfile\n");
		return -ENOMEM;
	}
	pr_info("[ SYSFS ] Successfully created kobject and sysfile\n");
	return 0;

}


static void __exit sysfs_exit (void){
	
	kobject_put(&sysfs_kobj);
}

module_init(sysfs_start);
module_exit(sysfs_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lazy-bunny");
MODULE_DESCRIPTION("Displaying sysfs");
