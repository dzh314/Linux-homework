#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/mm_types.h>
#include<linux/sched/task.h>
#include<linux/pid.h>

// 模块许可证声明
MODULE_LICENSE("Dual BSD/GPL");

// 模块加载函数
int init_module(void){
    // curr_proc指向当前进程
    struct task_struct *curr_proc;
    // curr_mm指向当前进程的内存描述符
    struct mm_struct *curr_mm;
    // 第一个PDE的地址
    pgd_t *curr_pgd;
    // 为了通过编译，在这里声明循环变量i
    int i;
    
    printk(KERN_INFO "This is for homework2.\n");
    curr_proc = current;
    curr_mm = curr_proc->active_mm;
    curr_pgd = curr_mm->pgd;
    // PTRS_PER_PGD中维护着PGD里表项的个数，即PDE的数目
    for(i = 0; i < PTRS_PER_PGD; i++)
        printk(KERN_INFO "PDE %d: %lx\n", i, pgd_val(curr_pgd[i]));
    return 0;
}

// 模块卸载函数
void cleanup_module(void){
    printk(KERN_INFO "Homework2 ends.\n");
}