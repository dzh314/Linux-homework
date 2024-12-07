#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/types.h>

// 模块许可证声明
MODULE_LICENSE("Dual BSD/GPL");

// 模块加载函数
int init_module(void){
    // GDTR寄存器
    struct desc_ptr GDTR;
    // GDT首地址
    struct desc_struct *gdt;
    // 段描述符基址
    unsigned long base;
    // 段长度限制
    unsigned long limit;
    // nums_of_entry表示GDT的表项数目
    int i, nums_of_entry;

    printk(KERN_INFO "This is for homework3.\n");
    // 通过汇编指令拿到GDTR寄存器的值
    asm volatile("sgdt %0" : "=m" (GDTR));

    // GDT基址
    gdt = (struct desc_struct *)GDTR.address;
    printk(KERN_INFO "GDT base address: 0x%lx\n", GDTR.address);
    // GDT长度限制
    printk(KERN_INFO "GDT limit: 0x%x\n", GDTR.size);

    nums_of_entry = (GDTR.size + 1) / sizeof(struct desc_struct);

    for(i = 0; i<nums_of_entry; i++){
        // 段描述符被分为三个部分，16+8+8=32位
        base = (gdt[i].base0) | (gdt[i].base1 << 16) | (gdt[i].base2 << 24);
        printk(KERN_INFO "GDT Entry %d base address = 0x%08lx\n", i, base);

        // 长度限制被分为两个部分，如果G=1，在20位limit后补充0xFFF
        limit = (gdt[i].limit0) | (gdt[i].limit1 << 16);
        if(gdt[i].g){
            limit = (limit << 12) | 0xFFF;
        }
        printk(KERN_INFO "GDT Entry %d limit = 0x%08lx\n", i, limit);
    }

    return 0;
}

// 模块卸载函数
void cleanup_module(void){
    printk("Homework3 ends.\n");
}