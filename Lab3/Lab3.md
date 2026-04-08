## Add function
### entry.S
[ ] Set exception table
    + 0x280 -> irq()
    + 0x400 ->system call table
[X] save_status

### shell.c
[X] svc_test()
[X] brk_test()
[X] daif()
[X] irq_cmd()


### irq.c
[X] core_timer
    + Routing: EL0 -> shell.c irq_cmd -> svc #0 -> EL1 -> sys_table[] -> enable_timer() -> EL0 ... wait for timer triggered ... -> EL1 -> irq.c -> core_timer() -> write to uart software buffer -> EL0
    + print("timer triggered")
[ ] uart
    + Transmit Routing: EL0 -> FIFO queue lower than watermark -> trigger IRQ -> EL1 -> handler -> move data from software buffer to FIFO -> EL0
        + In qemu: If FIFO queue empty -> manually move first data to queue
    + Receive Routining: EL0 -> FIFO queue more than watermark -> trigger IRQ -> EL1 -> handler -> move data from FIFO to software buffer -> EL0

### systemcall_handler.c
[X] daif()
[X] timer()
[X] sys_call_handler()


### queue.c
Software queue for PL011 uart interrupt
[ ] queue_empty()
[ ] queue_push()
[ ] queue_pop()
