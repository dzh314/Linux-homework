#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched/task.h>
#include<linux/sched.h>

// 模块许可证声明
MODULE_LICENSE("Dual BSD/GPL");

// 模块加载函数
int init_module(void){
    struct task_struct *curr_proc;
    struct mm_struct *curr_mm;
    // curr_vm_area是当前虚拟内存空间的描述符
    struct vm_area_struct *curr_vm_area;
    // curr_vm_start是当前虚拟内存空间的首地址
    unsigned long curr_vm_start;
    unsigned long size;

    printk(KERN_INFO "This is for homework7.\n");
    curr_proc = current;
    curr_mm = curr_proc->active_mm;
    down_read(&(curr_mm->mmap_sem));
    // curr_vm_area首先指向第一个虚拟内存空间,即mmap
    curr_vm_area = curr_mm->mmap;
    while (curr_vm_area) {
        curr_vm_start = curr_vm_area->vm_start;
        // 空间大小即end - start
        size = curr_vm_area->vm_end - curr_vm_start;
        printk(KERN_INFO "VM AREA START: %lx , LENGTH: %lx\n", curr_vm_start, size);
        curr_vm_area = curr_vm_area->vm_next;
    }
    up_read(&(curr_mm->mmap_sem));
    return 0;
}

// 模块卸载函数
void cleanup_module(void){
    printk("Homework7 ends.\n");
}