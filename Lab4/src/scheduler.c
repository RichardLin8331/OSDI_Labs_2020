#include "include/scheduler.h"
#include "include/task_queue.h"
#include "include/core_timer.h"

void context_switch(struct task_struct* next) {
    if (current->task_status == TASK_RUNNING) {
        current->priority = 0;
        priority_queue_push(&running_queue, current);
    }

    else if (current->task_status == TASK_WAITING) task_queue_push(waiting_queue, &waiting_queue_tail, current);
    else if (current->task_status == TASK_ZOMBIE) task_queue_push(zombie_queue, &zombie_queue_tail, current);
    switch_to(current, next);
}

void schedule() {
    core_timer_handler();
    if (num_runnable_tasks() > 0) {
            struct task_struct* next = priority_queue_pop(&running_queue);
            context_switch(next);
        }
    
};
