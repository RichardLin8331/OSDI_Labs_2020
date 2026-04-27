#ifndef R_IRQ_HANDLER_H
#define R_IRQ_HANDLER_H

#define CORE0INTSRC ((unsigned int*)0x40000060)
void irq_enable();
void irq_disable();

#endif