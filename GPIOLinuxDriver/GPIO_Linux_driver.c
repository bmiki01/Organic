#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

#define DRIVER_NAME "GPIO_Linux_driver"
#define DRIVER_CLASS "MyModuleClass"

/* Meta Infos */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("V.Péter");
MODULE_DESCRIPTION("A Linux GPIO Driver for LED(output pin -4), and button(input pin - 17).");

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

/*This function is called, when the device file is opened -> reading data from button input*/
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs)
{
	int to_copy, not_copied, delta;
	char tmp[3] = " \n";	

	to_copy = min(count, sizeof(tmp));

	printk("Value of button: %d\n", gpio_get_value(17));
	tmp[0] = gpio_get_value(17) + '0';/*read data*/

	not_copied = copy_to_user(user_buffer, &tmp, to_copy);

	delta = to_copy - not_copied;

	return delta;
}

/*This function is called, when the device file is closed -> writing data to LED output*/
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) 
{
	int to_copy, not_copied, delta;
	char value;

	to_copy = min(count, sizeof(value));

	not_copied = copy_from_user(&value, user_buffer, to_copy);
	
	/*Setting the LED*/
	switch(value)
	{
		case '0':
			gpio_set_value(4,0);
		break;
		case '1':
			gpio_set_value(4,1);
		break;
		default:
			printk("Invalid input!\n");
		break;
	}
	

	delta = to_copy - not_copied;

	return delta;
}

static int driver_open(struct inode *device_file, struct file *instance) 
{
	printk("dev_nr - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance)
{
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.write = driver_write
};

/* This function is called, when the module is loaded into the kernel */
static int __init ModuleInit(void) 
{
	printk("Hello, Kernel!\n");

	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not be created!\n");
		goto ClassError;
	}

	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}

	cdev_init(&my_device, &fops);

	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}

	/*GPIO 4 init */
	if(gpio_request(4, "rpi-gpio-4"))
	{
		printk("Can not allocate GPIO port 4!\n");
		goto AddError;
	}
	/*Set GPIO port 4 direction:*/
	if(gpio_direction_output(4,0))
	{
		printk("Can not set GPIO port 4 to output!\n ");
		goto Gpio4Error;
	}
	/*GPIO 17  init */
    if(gpio_request(17, "rpi-gpio-17"))
    {
            printk("Can not allocate GPIO port 17!\n");
            goto Gpio4Error;
    }
    /*Set GPIO port 17 direction:*/
    if(gpio_direction_input(17))
    {
            printk("Can not set GPIO port 17 to output!\n ");
            goto Gpio17Error;
    }


	return 0;
Gpio4Error:
	gpio_free(4);
Gpio17Error:
	gpio_free(17);
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) 
{
	gpio_set_value(4,0);
	gpio_free(17);
	gpio_free(4);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);