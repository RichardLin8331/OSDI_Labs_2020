#ifndef R_MM_H
#define R_MM_H

//#include "task.h"

#define PAGE_SIZE 4096
#define PAGE_NUM 256
#define KERNEL_STACK_BASE 0x3000000
#define USER_STACK_BASE 0x500000
#define TASK_BASE 0x700000
#define TASK_POOL_SIZE 64

#ifndef __ASSEMBLER__
void memzero(unsigned long mem_bottom, unsigned long mem_top);
unsigned long get_free_kernel_stack();
unsigned long get_free_user_stack();
int assign_task_mem(unsigned short i);

#endif

#endif