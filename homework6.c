#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<linux/sched/task.h>

// 模块许可证声明
MODULE_LICENSE("Dual BSD/GPL");

// 模块加载函数
int init_module(void){
    struct task_struct *curr_proc;
    
    printk(KERN_INFO "This is for homework6.\n");
    curr_proc = &init_task;
    do{
        printk(KERN_INFO "name: %20s, pid: %8d\n", curr_proc->comm, curr_proc->pid);
        curr_proc = next_task(curr_proc); 
    } while(curr_proc != &init_task);
    return 0;
}

// 模块卸载函数
void cleanup_module(void){
    printk("Homework6 ends.\n");
}
