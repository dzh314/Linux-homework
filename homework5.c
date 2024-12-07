#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/thread_info.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/sched/task.h>

// 模块许可证声明
MODULE_LICENSE("Dual BSD/GPL");

// 模块加载函数
int init_module(void){
    struct task_struct *curr_proc;
    struct mm_struct *curr_mm;

    printk(KERN_INFO "This is for homework5.\n");
    
    // 获取当前进程
    curr_proc = current;
    // 获取当前mm_struct
    curr_mm = curr_proc->active_mm;
    
    // start_stack存用户栈起始地址
    printk(KERN_INFO "User stack begins at %lx.\n", curr_mm->start_stack);
    // task_struct->stack存内核栈起始地址
    printk(KERN_INFO "Kernel stack begins at %lx.\n", (unsigned long)(curr_proc->stack));
    return 0;
}

// 模块卸载函数
void cleanup_module(void){
    printk(KERN_INFO "Homework5 ends.\n");
}