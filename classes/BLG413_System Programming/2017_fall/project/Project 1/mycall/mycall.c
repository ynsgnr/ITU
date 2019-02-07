#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/cred.h>

asmlinkage long set_myFlag(pid_t pid, int flag){

  task_struct *task;
  task=find_task_by_vpid(pid_t);

  if(current_cred()->uid <= 0 || current_cred()->gid<=0){ //https://www.kernel.org/doc/Documentation/security/credentials.txt
      //Process has root priv. set flag
      task->myFlag=flag;
      printk(KERN_INFO 'my_flag value of process %d has been set to %d by %d.',pid_t,flag,current_cred()=>uid); //https://www.ibm.com/developerworks/library/l-kernel-logging-apis/index.html
      return 0;
  }
  else{
    //Not Root throw error
    printk(KERN_INFO 'my_flag value of process %d can not set to %d by %d.',pid_t,flag,current_cred()=>uid); //https://www.ibm.com/developerworks/library/l-kernel-logging-apis/index.html
    return -EPERM; // http://man7.org/linux/man-pages/man2/syscalls.2.html
  }
}
