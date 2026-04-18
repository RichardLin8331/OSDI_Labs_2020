#ifndef R_TASK_H
#define R_TASK_H

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
    unsigned long x29;
    unsigned long x30;

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
    unsigned long pid;
    struct trapframe trapframe;
    
};



#endif