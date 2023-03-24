#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

// if it compiles, then it's fine

#define BUFFER_SIZE 756
#define MAJOR_NUMBER 240
// remove magic value for register_chrdev
#define UNIQUE_NAME "pa3_char_driver"

// Maybe need GLP License, saw that the TA had it

/* Define device_buffer and other global data structures you will need here */

char* kbuffer;
int open;
int close;

ssize_t pa3_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/

	if (*offset+length > BUFFER_SIZE)
	{
		printk(KERN_ALERT "ERROR: offset + length > BUFFER_SIZE,");
		// return nonzero value for failure
		return -1;
	}

	// if (copy_to_user(buffer,kbuffer,length) == 0)
	// {
	// 	*offset += length;

	// }

	// FROM RECITATION 5:
	// return length - CTU return value 
	// (CTU should normally be zero, returns number of bytes remaining if over)
	// check to see if value is nonzero
	int CTU = copy_to_user(buffer,kbuffer + *offset,length);
	int bytes_read = length - CTU;
	if (length != bytes_read)
	{
		return -1;
	}
	
	*offset += length;
	printk(KERN_ALERT "Read %d bytes\n", bytes_read);

	
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */

	return bytes_read;
}



ssize_t pa3_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */

	if (*offset+length > BUFFER_SIZE)
	{
		printk(KERN_ALERT "ERROR: offset + length > BUFFER_SIZE,");
		// return nonzero value for failure
		return -1;
	}

	// COPY PASTED AND MODIFIED FROM READ

	// FROM RECITATION 5:
	// return length - CTU return value 
	// (CTU should normally be zero, returns number of bytes remaining if over)
	
	int CFU = copy_from_user(kbuffer + *offset,buffer,length);
	// check to see if value is nonzero
	int bytes_written = length - CFU;
	if (length != bytes_written)
	{
		return -1;
	}
	
	*offset += length;
	printk(KERN_ALERT "Wrote %d bytes\n", bytes_written);

	
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */

	return bytes_written;

}


int pa3_char_driver_open (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	printk(KERN_ALERT "pa2_char_driver_open called\n");\
	// print how many times it has been open instead of insinuating program has been opened
	open++;
	return 0;
}

int pa3_char_driver_close (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	printk(KERN_ALERT "pa2_char_driver_close called\n");
	close++;
	return 0;
}

loff_t pa3_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
	/* The seek function takes three parameters, a file pointer, an offset, and the value whence.  
		Whence describes how to interpret the offset (note that offset can be negative).*/  

	// Stores modified position value from seek switch options, end result is updated into p_file->f_pos
	// https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch03s04.html#:~:text=A%20FILE%20is%20defined%20in,structure%20represents%20an%20open%20file.

	loff_t s_pos = 0; 
	
	/* Update open file position according to the values of offset and whence */

	switch (whence)
	{
		// If the value of whence is ​0​ (​SEEK_SET​), the position is set to the value of the offset.
		case 0: 
		// Either starts at position negative from head or exceeds buffer, wrap around buffer and continue 
			if (offset < 0)
			{
				s_pos = BUFFER_SIZE + offset; 
			}
			else if (offset >= BUFFER_SIZE)
			{
				s_pos = offset % BUFFER_SIZE; 
			}
			else
			{
				// seek 0 op
				s_pos = offset; 
			}
			break;
		// If the value of whence is ​1​ (SEEK_CUR​), the current position is incremented (or decremented, if negative) 
		// by offset bytes.
		case 1:
		// Copy pasted from case 0 and altered to account for seek 1 ops
			// if (pfile->f_pos + offset < 0 || pfile->f_pos + offset > BUFFER_SIZE)
			// {
			// 	printk(KERN_ALERT "ERROR: offset value is invalid");
			// 	pfile->f_pos = 0;
			// 	return -1;
			// }
			if (pfile->f_pos + offset < 0)
			{
				s_pos = BUFFER_SIZE + (pfile->f_pos + offset); 
			}
			else if (pfile->f_pos + offset > BUFFER_SIZE)
			{
				s_pos = (pfile->f_pos + offset) % BUFFER_SIZE; 
			} 
			else
			{
				// seek 1 op
				s_pos = pfile->f_pos + offset; 
			}
			break;
		// Finally, if the value of whence is ​2 (​SEEK_END​), the position is set to offset bytes from the end of the file.*/

		case 2:
		// Copy pasted from case 0 and altered to account for seek 1 ops
			// if (BUFFER_SIZE - offset < 0 || BUFFER_SIZE - offset > BUFFER_SIZE)
			// {
			// 	printk(KERN_ALERT "ERROR: offset value is invalid");
			// 	pfile->f_pos = 0;
			// 	return -1;
			// }
			if (BUFFER_SIZE - offset < 0)
			{
				s_pos = offset%BUFFER_SIZE; 
			}
			else if (BUFFER_SIZE - offset > BUFFER_SIZE)
			{
				s_pos = BUFFER_SIZE + offset; 
			} 
			else
			{
				s_pos = offset;
			}
			break;
	}
	// resulting s_pos value (if no edge cases were triggered) is used to be set as f_pos value and zero is returned
	pfile->f_pos = s_pos;

	return s_pos;
}

// Example from pa3 writeup
struct file_operations my_file_operations = {
	// need to change these values to reflect the functions in this c file
    .owner   = THIS_MODULE,
    .open    = pa3_char_driver_open,       // int my_open  (struct inode *, struct file *);
    .release = pa3_char_driver_close,      // int my_close (struct inode *, struct file *);
    .read    = pa3_char_driver_read,       // ssize_t my_read  (struct file *, char __user *, size_t, loff_t *);
    .write   = pa3_char_driver_write,      // ssize_t my_write (struct file *, const char __user *, size_t, loff_t *);
    .llseek  = pa3_char_driver_seek        // loff_t  my_seek  (struct file *, loff_t, int);
};

static int pa3_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	printk(KERN_ALERT "pa3_char_driver_init was called.\n");
	// void* kmalloc(size_t size, gfp_t flags) ​allocates memory 
	// for use in the kernel, use the macro GFP_KERNEL​ as the flags argument in this case
	kbuffer = (char*)kmalloc(BUFFER_SIZE,GFP_KERNEL);
	/* register the device */
	// register_chrdev() takes three parameters: major number, a unique name, 
	// and a pointer to a file operations struct (see below).
	register_chrdev(MAJOR_NUMBER,UNIQUE_NAME, &my_file_operations);
	return 0;
}

static void pa3_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	printk(KERN_ALERT "pa3_char_driver_exit was called.\n");
	// void kfree(const void* kptr)​ frees memory previously allocated using kmalloc()
	kfree(kbuffer);
	/* unregister  the device using the register_chrdev() function. */
	unregister_chrdev(MAJOR_NUMBER,UNIQUE_NAME);
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
// https://tldp.org/LDP/lkmpg/2.4/html/x257.htm
module_init(pa3_char_driver_init);
module_exit(pa3_char_driver_exit);

