#ifndef R_TASK_H
#define R_TASK_H

#define TASK_POOL_SIZE 64

struct cpu_context{
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long fp;
    unsigned long lr;

    unsigned long sp_kernel;

};

struct trapframe{
    unsigned long regs[31];
    unsigned long sp_user;
    unsigned long elr_el1;
    unsigned long esr_el1;
};

struct task_struct{
    struct cpu_context context;
    struct trapframe* trapframe;
    unsigned long pid;
    unsigned short reschedule_flag;
    
    
};

extern struct task_struct* task_pool[TASK_POOL_SIZE];

void init_kernel_task();
int privilege_task_create(void(*fn));
int user_task_create();


#endif