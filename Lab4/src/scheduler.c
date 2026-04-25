#include "include/scheduler.h"
#include "include/task_queue.h"
#include "include/core_timer.h"

void context_switch(struct task_struct* next) {
    if (current->task_status == TASK_RUNNING) task_queue_push(running_queue, &running_queue_tail, current);
    else if (current->task_status == TASK_WAITING) task_queue_push(waiting_queue, &waiting_queue_tail, current);
    else if (current->task_status == TASK_ZOMBIE) task_queue_push(zombie_queue, &zombie_queue_tail, current);
    switch_to(current, next);
}

void schedule() {
    core_timer_handler();
    if (queue_empty(running_queue_head, running_queue_tail) != 1) {
            struct task_struct* next = task_queue_pop(running_queue, &running_queue_head);
            context_switch(next);
        }
    
};
