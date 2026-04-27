#include "include/queue.h"
#include "include/task_queue.h"
#include "include/task.h"
#include "include/mm.h"
#include "include/uart.h"
#include "include/string.h"
#include "include/irq_handler.h"

void zombie_reaper() {
    while(1) {
        irq_enable();
        if (queue_empty(zombie_queue_head, zombie_queue_tail) != 1) {
            struct task_struct* tmp = task_queue_pop(zombie_queue, &zombie_queue_head);
            free_kernel_stack(tmp->context.sp_kernel);
            free_task_mem(tmp->pid);

            uart_send_string("Reclaimed resources of pid: ");
            char pid_str[4];
            itos(tmp->pid, pid_str);
            uart_send_string(pid_str);
            uart_send_string("\r\n# ");
        }
    }
    
}