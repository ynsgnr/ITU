#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/seq_file.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <asm/switch_to.h>
#include <asm/uaccess.h>
#include <linux/cred.h>
#include <linux/sched.h>

#include "messagebox_ioctl.h"

#define MESSAGEBOX_MAJOR 0
#define MESSAGEBOX_NR_DEVS 1
#define DEVICE_NAME "messagebox"

struct message {
  char *data;//message itself with sender information
  int length;//length of message to prevent overflow
  struct message *next;//next message
};

struct m_user {
  char *name;//user name of user
  struct message *messages; //pointer to message list
  int message_r; //how many messages have been read
  int message_l; //how many characters should be displayed
  int message_s; //how many messages this user has
  int name_size; //size of username to prevent overflow
};

struct messagebox_dev {
    struct m_user **data; //pointer to user array
    unsigned long size; //size (required for devices)
    struct semaphore sem; //semaphore of driver (required for devices)
    struct cdev cdev; //cdev structure (required for devices)
    int max_messages; //maximum messages that user can read (can be set with iotcl commands)
    bool inc_read; //should we include read message to output (can be set with iotcl commands)
    int user_count; //how many users system has
    int max_user; //maximum number of users
    char *tmp; //message to display
    int tmpLength; //length of message
    int current_user_no; //user no of the active user
    char current_user_name[33]; // username of the active user
    int current_user_name_l; //length of username
};

struct messagebox_dev device;

int messagebox_major = MESSAGEBOX_MAJOR;
int messagebox_minor = 0;
int messagebox_nr_devs = MESSAGEBOX_NR_DEVS;
int messagebox_quantum = sizeof(struct m_user)*10;
int messagebox_qset = sizeof(struct message);
int r_index;
struct class *c;
struct device *d;


module_param(messagebox_major, int, S_IRUGO);
module_param(messagebox_minor, int, S_IRUGO);
module_param(messagebox_nr_devs, int, S_IRUGO);
module_param(messagebox_quantum, int, S_IRUGO);
module_param(messagebox_qset, int, S_IRUGO);

MODULE_AUTHOR("Yunus Güngör, Cem Duhan");
MODULE_LICENSE("Dual BSD/GPL");

int messagebox_open(struct inode *inode, struct file *filp)
{
    struct messagebox_dev *dev;
    struct message *m;
    int i,length,j,user_no=0;
    char *tmp;
    r_index=0;
    printk(KERN_INFO "Opened");
    dev = container_of(inode->i_cdev, struct messagebox_dev, cdev);
    dev->size=device.max_user*sizeof(struct m_user);
    dev->max_messages = device.max_messages;
    dev->inc_read = device.inc_read;
    dev->user_count = device.user_count;
    dev->max_user = device.max_user;
    dev->data=device.data;
    dev->current_user_name_l=0;

    //get username
    tmp=kmalloc(33 * sizeof(struct m_user *), GFP_KERNEL);
    char *userName=tmp;
    char userIDs[33];
    int k=0;
    while(k<33)
    {
      userName[k]=' ';
      userIDs[k]=' ';
      k++;
    }
    struct file *file;
    mm_segment_t fsegment;
    char c=' ';
    long userID=-1;
    int uid;
    uid=current_uid().val;
    printk(KERN_INFO "Uid:%d",uid);

    file = filp_open("/etc/passwd", O_RDONLY, 0);
    if(file == NULL)
        printk(KERN_ALERT "Can not open user file\n");
    else{
        printk(KERN_INFO "Getting user name\n");
        fsegment = get_fs();
        set_fs(get_ds());
        while(c!=0)
        {
          i=0;
          while(c!=':')
          {
            vfs_read(file, &c, 1, &file->f_pos);
            userName[i]=c;
            i++;
          }
          j=i;
          userName[i-1] = '\0';

          //pass wd
          c=' ';
          while(c!=':')
          {
            vfs_read(file, &c, 1, &file->f_pos);
          }

          c=' ';
          i=0;
          while(c!=':')
          {
            //file->f_op->read(file, &c, 1, );
            vfs_read(file, &c, 1, &file->f_pos);
            userIDs[i]=c;
            i++;
          }
          userIDs[i-1] = '\0';
          kstrtol(userIDs, 10, &userID);
           if(userID==uid)
           break;

          //groupid
          c=' ';
          while(c!=':')
          {
            vfs_read(file, &c, 1, &file->f_pos);
          }

          //idinfo
          c=' ';
          while(c!=':')
          {
            vfs_read(file, &c, 1, &file->f_pos);
          }

          //homedr
          c=' ';
          while(c!=':')
          {
            vfs_read(file, &c, 1, &file->f_pos);
          }

          //commandshell
          c=' ';
          while(c!='\n')
          {
            vfs_read(file, &c, 1, &file->f_pos);
          }
          c=' ';
      }
    set_fs(fsegment);
    printk(KERN_INFO "username:%s\n",userName);
    }
    filp_close(file,NULL);

    for(i=0;i<=j;i++){
      dev->current_user_name[i]=userName[i];
    }
    dev->current_user_name_l=j+1;

    //find user whom opened
    printk(KERN_INFO "User count:%d",dev->user_count);
    i=0;
    while(i<=dev->user_count){
      j=0;
      if(dev->data!=NULL && dev->data[i]!=NULL && dev->data[i]->name!=NULL){
        while(j<dev->data[i]->name_size-1 && dev->data[i]->name[j]!='\0' && tmp[j]!='\0' && dev->data[i]->name[j]==tmp[j]){
            //compare string
            j++;
        }
        if(j==dev->data[i]->name_size-1){
          printk(KERN_INFO "matched!");
          user_no=i;
          i=dev->user_count;
        }
      }
      i++;
    }
    kfree(tmp);

    if(dev->data!=NULL && dev->data[user_no]!=NULL && j!=dev->data[user_no]->name_size-1){
      printk(KERN_INFO "no match!");
      user_no=-1;
    }else{

      m=NULL;
      if(dev->data!=NULL && dev->data[user_no]!=NULL)
        m=dev->data[user_no]->messages;

      if(m!=NULL){
        if(dev->tmp!=NULL) kfree(dev->tmp);
        dev->tmp=kmalloc((dev->data[user_no]->message_s) * sizeof(char), GFP_KERNEL);
        length=0;
        if(dev->inc_read){
          i=0;
        }else{
          for(i=0;i<dev->data[user_no]->message_r;i++)
            m=m->next;
        }
        //TODO add max limit
        while (i<dev->data[user_no]->message_l){
          printk(KERN_INFO "Sending data: %s with lenghth %d\n",m->data,m->length);
          memcpy(dev->tmp+length*sizeof(char),m->data,m->length);
          length+=m->length;
          m=m->next;
          i++;
        }
        dev->tmpLength=length;
      }
    }
    dev->current_user_no=user_no;
    filp->private_data = dev;
    return 0;
}


int messagebox_release(struct inode *inode, struct file *filp)
{
    return 0;
}


ssize_t messagebox_read(struct file *filp, char __user *buf, size_t count,
                   loff_t *f_pos)
{
    size_t length;
    struct message *m;
    struct messagebox_dev *dev = filp->private_data;
    int user_no = dev->current_user_no;

    printk(KERN_INFO "Read!\n");

        if (dev->data == NULL || user_no<0)
            goto out;

    printk(KERN_INFO "User no:%d\nUser count:%d\n",user_no,dev->user_count);

    if(! dev->data[user_no])
      goto out;

    ssize_t retval = 0;

    if (down_interruptible(&dev->sem)){
        printk(KERN_INFO "interrupt!");
        return -ERESTARTSYS;
    }

    m=dev->data[user_no]->messages;
    if(m==NULL)
      goto out;

    length=dev->tmpLength;
    length=length-r_index;
    if(length>count)
      length=count;

    printk(KERN_INFO "tmp: %s\nlenght:%d\n",dev->tmp,length);
    if (copy_to_user(buf, dev->tmp+r_index, length)) {
        printk(KERN_INFO "copy_to_user fail");
        retval = -EFAULT;
        goto out;
    }

    r_index+=length;
    retval = length;
    dev->data[user_no]->message_r=dev->data[user_no]->message_l;
  out:
    up(&dev->sem);
    return retval;
}


ssize_t messagebox_write(struct file *filp, const char __user *buf, size_t count,
                    loff_t *f_pos)
{
    printk(KERN_INFO "Written\n");

    struct messagebox_dev *dev = filp->private_data;
    struct message *m;
    int quantum = sizeof(struct m_user);
    int i,j;
    char *tmp;
    ssize_t retval=0;

    printk(KERN_INFO "Allocating string:%d\n",count);
    tmp=kmalloc(count*sizeof(char),GFP_KERNEL);
    if (!tmp)
        goto out;

    printk(KERN_INFO "Coping from user:");
    if (copy_from_user(tmp, buf, count)) {
        retval = -EFAULT;
        goto out;
    }
    printk(KERN_INFO "%s\n",tmp);

    if(tmp[0]!='@'){
      printk(KERN_INFO "No @");
        retval = -EFAULT;
        goto out;
    }

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;

    if (*f_pos >= quantum * dev->max_user) {
        retval = 0;
        goto out;
    }

    if (dev->data==NULL) {
        printk(KERN_INFO "Allocating quantum array: ");
        dev->data = kmalloc(dev->max_user * sizeof(struct m_user *), GFP_KERNEL);
        printk(KERN_INFO "%p\n",dev->data);
        if (!dev->data)
            goto out;
        for(i=0;i<dev->max_user;i++){
          dev->data[i]=NULL;
        }
    }

    //find user to send
    int user_no=0;
    i=0;
    while(i<=dev->user_count){
      j=0;
      printk(KERN_INFO "i: %d",i);
      if(dev->data[i]!=NULL && dev->data[i]->name!=NULL){
        while(j<dev->data[i]->name_size && dev->data[i]->name[j]!='\0' && tmp[j+1]!=' ' && dev->data[i]->name[j]==tmp[j+1]){
            //compare string
            j++;
        }
        if(j==dev->data[i]->name_size-1){
          printk(KERN_INFO "matched!");
          user_no=i;
          i=dev->user_count;
        }
      }
      i++;
    }

    if(dev->data[user_no]!=NULL && j!=dev->data[user_no]->name_size-1){
      printk(KERN_INFO "no match!");
      user_no=dev->user_count+1;
    }

    printk(KERN_INFO "User no:%d",user_no);

    if (dev->data[user_no]==NULL) {
        printk(KERN_INFO "Allocating quantum: ");
        dev->data[user_no] = kmalloc(quantum, GFP_KERNEL);
        printk(KERN_INFO "%p\n",dev->data[user_no]);
        if (!dev->data[user_no])
            goto out;
        dev->data[user_no]->messages=NULL;
        dev->data[user_no]->message_l=0;
        dev->data[user_no]->message_r=0;
        dev->data[user_no]->message_s=0;
        printk("Assiging name:");
        i=0;
        while(tmp[i]!=' ')
          i++;
        dev->data[user_no]->name=kmalloc(i*sizeof(char), GFP_KERNEL);
        memcpy(dev->data[user_no]->name,tmp+1,i);
        dev->data[user_no]->name_size=i;
        printk("%s\n",dev->data[user_no]->name);
        printk("Name count:%d\n",i);
        device.user_count++;
    }

    m=dev->data[user_no]->messages;
    for(i=1;i<dev->data[user_no]->message_l;i++){
      m=m->next;
    }
    if(m!=NULL && m->next==NULL){
      printk(KERN_INFO "Allocating new message:\n");
      m->next = kmalloc(sizeof(struct message), GFP_KERNEL);
      if (!(m->next))
          goto out;
      m->next->next=NULL;
      m=m->next;
    }
    if(m==NULL){
      dev->data[user_no]->messages=kmalloc(sizeof(struct message), GFP_KERNEL);
      if (!dev->data[user_no]->messages)
        goto out;
      dev->data[user_no]->messages->length=0;
      dev->data[user_no]->messages->next=NULL;
      m=dev->data[user_no]->messages;
    }
    printk(KERN_INFO "Coping from tmp\n");
    m->length = (count-dev->data[user_no]->name_size-1+dev->current_user_name_l+2);
    printk(KERN_INFO "data size:%d\n",m->length);
    m->data = kmalloc(m->length*sizeof(char), GFP_KERNEL);
    if (!m->data)
      goto out;
    printk(KERN_INFO "coping data:%s\n",tmp+dev->data[user_no]->name_size+1);
    memcpy(m->data,dev->current_user_name,dev->current_user_name_l-1);
    memcpy(m->data+dev->current_user_name_l-1,": ",2);
    memcpy(m->data+dev->current_user_name_l+1,tmp+dev->data[user_no]->name_size+1,count-dev->data[user_no]->name_size-1);

    kfree(tmp);

    dev->data[user_no]->message_s+=m->length;
    printk(KERN_INFO "Got data:\n%s\n",m->data);

    dev->data[user_no]->message_l++;

    retval = count;

    /* update the size */
    if (dev->size < *f_pos)
        dev->size = *f_pos;

  out:
    up(&dev->sem);

  return retval;
}

long messagebox_ioctl(struct file *filp, int cmd, unsigned long arg, char * name)
{

  printk(KERN_INFO "ioctl called: %d, %d, %s",cmd,arg,name);

	struct messagebox_dev *dev = filp->private_data;
    struct message *ms;
	int err = 0;
	int retval = 0;
	int uid=1;
	int l;
	int m;
	int same;
	int user_id;
	uid=current_uid().val;
	int max_usr;

	switch(cmd) {
    //implement EXCLUDE_READ,INCLUDE_READ,change max size and delete user's messages

    case MESSAGEBOX_EXCLUDE_READ:
		if(uid!=0)
		printk(KERN_INFO "Unaouthtorised User\n"); return -EFAULT;

		printk(KERN_INFO "EXCLUDE_READ Activated\n");
        device.inc_read=false;
        break;

      case MESSAGEBOX_INCLUDE_READ:
		if(uid!=0)
		printk(KERN_INFO "Unaouthtorised User\n"); return -EFAULT;

		printk(KERN_INFO "INCLUDE_READ Activated\n");
        device.inc_read=true;
        break;

    case MESSAGEBOX_MAX_SIZE:
		if(uid!=0)
		printk(KERN_INFO "Unaouthtorised User\n"); return -EFAULT;

		printk(KERN_INFO "Max Message Size Setted At\n", &arg);
        dev->max_messages=arg;
        break;

    case MESSAGEBOX_DELETE_MESAGE:
		if(uid!=0)
		printk(KERN_INFO "Unaouthtorised User\n"); return -EFAULT;

		//user id==arg
		same=1;
		max_usr=dev->max_user;
		for(l=0;l<max_usr;l++)
		{	same=1;
			if(sizeof(dev->data[l]->name)==sizeof(arg))
			{
				for(m=0;m<dev->data[l]->name_size;m++)
				{
						if(dev->data[l]->name[m]!=name[m])
						{
							same=0;
						}
				}

				if(same==1)
				{
					user_id=l;
					goto delete;
				}
			}
			else
			{
				same=0;
			}
		}
		goto fail;
		delete:
		printk(KERN_INFO "User Found\n");
		if(dev->data[user_id]->messages==NULL)
		{
			goto fail;
		}

		ms=dev->data[user_id]->messages;
		dev->data[user_id]->messages=dev->data[user_id]->messages->next;
		while(ms!=NULL)
		{
			kfree(ms);
			ms=dev->data[user_id]->messages;
			dev->data[user_id]->messages=dev->data[user_id]->messages->next;
		}
           //delete_user=arg;
           //arg is passed argument for userid
        printk(KERN_INFO "Messages Deleted\n");
        break;


	  default:  /* redundant, as cmd was checked against MAXNR */
    printk("Not supposed to happen");
		return -ENOTTY;
	}

	fail:
	return -ENOTTY;

	return retval;
}


loff_t messagebox_llseek(struct file *filp, loff_t off, int whence)
{
    struct messagebox_dev *dev = filp->private_data;
    loff_t newpos;

    switch(whence) {
        case 0: /* SEEK_SET */
            newpos = off;
            break;

        case 1: /* SEEK_CUR */
            newpos = filp->f_pos + off;
            break;

        case 2: /* SEEK_END */
            newpos = dev->max_user*sizeof(struct m_user) + off;
            break;

        default: /* can't happen */
            return -EINVAL;
    }
    if (newpos < 0)
        return -EINVAL;
    filp->f_pos = newpos;
    return newpos;
}

struct file_operations messagebox_fops = {
    .owner =    THIS_MODULE,
    .llseek =   messagebox_llseek,
    .read =     messagebox_read,
    .write =    messagebox_write,
    .unlocked_ioctl =  messagebox_ioctl,
    .open =     messagebox_open,
    .release =  messagebox_release,
};


void messagebox_cleanup_module(void)
{
    printk(KERN_INFO "Clear messagebox\n");
    int i;
    struct m_user *u;
    dev_t devno = MKDEV(messagebox_major, messagebox_minor);

    for(i=0;i<device.user_count;i++){
      u=device.data[i];
      //TODO kfree all pointers
    }

    cdev_del(&device.cdev);
    device_destroy(c, devno);     // remove the device
    class_unregister(c);                          // unregister the device class
    class_destroy(c);                             // remove the device class
    unregister_chrdev_region(devno, DEVICE_NAME);
}


int messagebox_init_module(void)
{
    printk(KERN_INFO "init messagebox\n");
    int result;
    int i;
    int err;
    dev_t devno = 0;
    struct messagebox_dev *dev;

    if (messagebox_major) {
        devno = MKDEV(messagebox_major, messagebox_minor);
        result = register_chrdev_region(devno, messagebox_nr_devs, "messagebox");
    } else {
        result = alloc_chrdev_region(&devno, messagebox_minor, messagebox_nr_devs,
                                     "messagebox");
        messagebox_major = MAJOR(devno);
    }
    if (result < 0) {
        printk(KERN_WARNING "messagebox: can't get major %d\n", messagebox_major);
        return result;
    }

    printk(KERN_NOTICE "Major: ");
    printk(KERN_NOTICE "%d \n",messagebox_major);

    c = class_create(THIS_MODULE, DEVICE_NAME);
    dev = &device;
    dev->max_messages=100;
    dev->inc_read=false;
    dev->user_count=0;
    dev->max_user=10;
    sema_init(&dev->sem,1);
    devno = MKDEV(messagebox_major, messagebox_minor);
    cdev_init(&dev->cdev, &messagebox_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &messagebox_fops;
    dev->data = NULL;
    err = cdev_add(&dev->cdev, devno, 1);
    if (err) {
      printk(KERN_NOTICE "Error %d adding device%d \n", err, i);
      cdev_del(&dev->cdev);
    }
    d = device_create(c, NULL,	devno, NULL, DEVICE_NAME);
    if (IS_ERR(d)) {
      err = PTR_ERR(d);
      printk(KERN_WARNING "[target] Error %d while adding device %s%d \n",
        err, DEVICE_NAME, messagebox_minor);
        cdev_del(&dev->cdev);
      }
    return 0; /* succeed */
	goto fail;
  fail:
    messagebox_cleanup_module();
    return result;
}

module_init(messagebox_init_module);
module_exit(messagebox_cleanup_module);
