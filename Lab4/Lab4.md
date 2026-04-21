## Add function
### task.c
- [ ] task_struct {
    cpu_context {
        x19 to x28
        x29 (fp)
        x30 (lr)
        sp (sp_el1) -> assign after trapframe
    } -> save when context switch
    pid
    user_stack ( = trapframe->sp_el0 )
    kernel_stack ( = cpu_context->sp )

    trapframe {
        x0 to x30
        sp_el0 -> assign free page
        esr_el1
        elr_el1
    } -> save when enters EL1
}
- [ ] privilege_task_create()
- [ ] user_task_create()
- [ ] do_exec()
### scheduler.c
- [ ] switch_to(prev, next)
    1. Save registers to prev->cpu_context
    2. Load next->cpu_context to registers
### system_call_handler.c
- [ ] uart_read() and uart_write()
- [ ] exec()
### mm.c
- [ ] get_free_kernel_stack()
- [ ] get_free_user_stack()
- [ ] memzero()
