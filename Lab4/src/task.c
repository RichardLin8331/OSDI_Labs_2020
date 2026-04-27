#include "include/task.h"
#include "include/mm.h"
#include "include/exception.h"
#include "include/task_queue.h"
#include "include/scheduler.h"
#include "include/string.h"

struct task_struct* task_pool[TASK_POOL_SIZE];

void init_kernel_task() {
    struct task_struct* tmp = (struct task_struct*) TASK_BASE;
    memzero(TASK_BASE, (TASK_BASE + sizeof(struct task_struct)));
    tmp->task_status = TASK_RUNNING;
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
    tmp->context.x19 = (unsigned long) fn;

    tmp->trapframe = (struct trapframe*) (tmp->context.sp_kernel);
    
    
    tmp->reschedule_flag = 0;
    tmp->task_status = TASK_RUNNING;
    task_pool[pid] = tmp;

    task_queue_push(running_queue, &running_queue_tail, tmp);
    

    return pid;
}

// called by fork() system call
int user_task_create() {
    struct task_struct* tmp;
    int pid = get_task_id();
    unsigned long ks = get_free_kernel_stack();
    unsigned long us = get_free_user_stack();
    if (pid == -1 || ks == -1 || us == -1) return -1;
    tmp = (struct task_struct*) TASK_BASE + pid * PAGE_SIZE;
    memzero((unsigned long) tmp, (unsigned long) tmp + sizeof(struct task_struct));
    tmp->pid = pid;
    tmp->context = current->context;
    
    memzero(ks - PAGE_SIZE, ks);
    memzero(us - PAGE_SIZE, us);

    tmp->context.sp_kernel = ks - sizeof(struct trapframe);
    tmp->context.lr = (unsigned long) return_from_fork;
    tmp->trapframe = (struct trapframe*) (tmp->context.sp_kernel);
    *(tmp->trapframe) = *(current->trapframe);

    // copy user stack 
    unsigned long cur_user_stack_offset = PAGE_SIZE - (current->trapframe->sp_user - USER_STACK_BASE) % PAGE_SIZE;
    tmp->trapframe->sp_user = us - cur_user_stack_offset;
    memcpy(tmp->trapframe->sp_user, current->trapframe->sp_user, cur_user_stack_offset);


    tmp->context.x19 = 0;
    tmp->reschedule_flag = 0;
    tmp->task_status = TASK_RUNNING;
    tmp->trapframe->regs[0] = 0;
    task_pool[pid] = tmp;
    task_queue_push(running_queue, &running_queue_tail, tmp);
    return pid;
}

void do_exec(void* fn) {
    memzero((unsigned long) current->trapframe, (unsigned long) current->trapframe + sizeof(struct trapframe));
    current->trapframe->elr_el1 = (unsigned long) fn;
    current->trapframe->esr_el1 = 0x0;
    unsigned long sp_k = (unsigned long)current->trapframe;
    char spks[] = "0x00000000";
    htos(sp_k, spks);
    unsigned long us = get_free_user_stack();
    if (us == -1) return;
    memzero(us - PAGE_SIZE, us);
    current->trapframe->sp_user = us;

    asm volatile ("mov sp, %0"::"r"(current->trapframe));
    asm volatile ("b load_all");

    return;
}

void task_exit(int status) {
    free_user_stack(current->trapframe->sp_user);
    current->task_status = TASK_ZOMBIE;
    schedule();
    /*
        free(user_stack)
        task->state = zombie
        schedule()
    */
}