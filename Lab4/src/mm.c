#include "include/mm.h"
//#include "include/task.h"


static unsigned short kernel_stack_table[PAGE_NUM];
static unsigned short user_stack_table[PAGE_NUM];
static unsigned short task_mem_table[TASK_POOL_SIZE];

unsigned long get_free_kernel_stack() {
    for (int i = 1; i < PAGE_NUM; i++) {
        if (kernel_stack_table[i] == 0) {
            kernel_stack_table[i] = 1;
            return KERNEL_STACK_BASE + (i + 1) * PAGE_SIZE;
        }
    }
    return -1;
}

void free_kernel_stack(unsigned long ks_addr) {
    int i = 0;
    i = (ks_addr - KERNEL_STACK_BASE - 1) / PAGE_SIZE;
    kernel_stack_table[i] = 0;
}

unsigned long get_free_user_stack() {
    for (int i = 1; i < PAGE_NUM; i++) {
        if (user_stack_table[i] == 0) {
            user_stack_table[i] = 1;
            return USER_STACK_BASE + (i + 1) * PAGE_SIZE;
        }
    }
    return -1;
}

void free_user_stack(unsigned long us_addr) {
    int i = 0;
    i = (us_addr - USER_STACK_BASE - 1) / PAGE_SIZE;
    user_stack_table[i] = 0;
}

int assign_task_mem(unsigned short i) {
    if (task_mem_table[i] == 1) return -1;
    task_mem_table[i] = 1;
    return i;
}

void free_task_mem(unsigned short i) {
    task_mem_table[i] = 0;
}