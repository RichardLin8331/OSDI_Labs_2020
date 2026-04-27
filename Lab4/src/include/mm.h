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
void memcpy(unsigned long dst_stack_bottom, unsigned long src_stack_bottom, unsigned long stack_size);
unsigned long get_free_kernel_stack();
void free_kernel_stack(unsigned long ks_addr);
unsigned long get_free_user_stack();
void free_user_stack(unsigned long us_addr);
int assign_task_mem(unsigned short i);
void free_task_mem(unsigned short i);

#endif

#endif