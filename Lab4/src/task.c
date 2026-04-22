#include "include/task.h"
#include "include/mm.h"
#include "include/exception.h"
#include "include/task_queue.h"

struct task_struct* task_pool[TASK_POOL_SIZE];

void init_kernel_task() {
    struct task_struct* tmp = (struct task_struct*) TASK_BASE;
    memzero(TASK_BASE, (TASK_BASE + sizeof(struct task_struct)));
    //tmp->pid = 0;
    task_pool[0] = tmp;
    asm volatile ("msr tpidr_el1, %0"::"r"(tmp));
}

int get_task_id() {
    for (int i = 1; i < TASK_POOL_SIZE; i++) {
        if (task_pool[i] == 0) {
            int assign_mem = assign_task_mem(i);
            if (assign_mem == -1) return -1;
            task_pool[i] = (struct task_struct*) 0x1;
            return i;
        }
    }

    return -1;
}

unsigned long get_task_trapframe(struct task_struct* t) {
    return (unsigned long) t->trapframe;
}

// called by kernel process
int privilege_task_create(void* fn) {
    struct task_struct* tmp;
    int pid = get_task_id();
    unsigned long ks = get_free_kernel_stack();
    if (pid == -1 || ks == -1 ) return -1;
    tmp = (struct task_struct*) TASK_BASE + pid * PAGE_SIZE;
    memzero((unsigned long) tmp, (unsigned long) tmp + sizeof(struct task_struct));
    tmp->pid = pid;

    memzero(ks - PAGE_SIZE, ks);
    tmp->context.sp_kernel = ks - sizeof(struct trapframe);
    tmp->context.lr = (unsigned long) return_from_fork;
    tmp->trapframe = (struct trapframe*) (tmp->context.sp_kernel);
    
    tmp->context.x19 = (unsigned long) fn;
    tmp->reschedule_flag = 0;
    task_pool[pid] = tmp;

    running_queue_push(running_queue, &running_queue_tail, tmp);
    

    return pid;
}

// called by fork() system call
/*
int user_task_create() {
    struct task_struct* tmp;
    int pid = get_task_id();
    unsigned long ks = get_free_kernel_stack();
    unsigned long us = get_free_user_stack();
    if (pid == -1 || ks == -1 || us == -1) return -1;
    tmp = (struct task_struct*) TASK_BASE + pid * PAGE_SIZE;
    memzero(tmp, tmp + sizeof(struct task_struct));
    tmp->pid = pid;
    //memcpy(tmp->context)
    memcpy(tmp->trapframe);

    memzero(ks - PAGE_SIZE, ks);
    memzero(us - PAGE_SIZE, us);
    tmp->context.sp_kernel = ks - sizeof(struct trapframe);
    tmp->context.lr = (unsigned long) return_from_fork;
    tmp->trapframe = (struct trapframe*) (tmp->context.sp_kernel);
    //tmp->trapframe->sp_user = us;
    
    tmp->context.x19 = 0;
    task_pool[pid] = tmp;
    return pid;
}

*/