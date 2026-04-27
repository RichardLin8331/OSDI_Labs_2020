#include "include/uart.h"
#include "include/core_timer.h"
#include "include/string.h"
#include "include/irq_handler.h"
#include "include/task.h"
#include "include/scheduler.h"

int core_timer_cnt = 0;

void irq_enable() {
    asm volatile("msr DAIFClr, 0x2");
}

void irq_disable() {
    asm volatile("msr DAIFSet, 0xf");
}

void irq_handler() {
    unsigned int core0int = 0;
    core0int = *CORE0INTSRC;
    unsigned int uart0_pending = 0;
    uart0_pending = *UART0_PENDING;

    if (core0int & 0x2) {
        core_timer_cnt++;
        uart_send_string("Core timer triggered.\r\n# ");
        uart_send_string("Jiffies: ");
        char timer_cnt_string[3];
        itos(core_timer_cnt, timer_cnt_string);
        uart_send_string(timer_cnt_string);
        uart_send_string("\r\n# ");
        current->reschedule_flag = 1;
    } else if (uart0_pending & 0x2000000) {
        uart_IRQ_handler();
    }
    if (current->reschedule_flag == 1) {
        current->reschedule_flag = 0;
        schedule();
    }
    return;
}

