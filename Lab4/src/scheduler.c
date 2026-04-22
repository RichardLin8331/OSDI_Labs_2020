#include "include/scheduler.h"
#include "include/task_queue.h"

void context_switch(struct task_struct* next) {
    running_queue_push(running_queue, &running_queue_tail, current);
    switch_to(current, next);
}

void schedule() {
    /*
        q_push(running_queue, current)
    */
    if (queue_empty(running_queue_head, running_queue_tail) != 1) {
            struct task_struct* next = running_queue_pop(running_queue, &running_queue_head);
            context_switch(next);
        }
    
};

void timer_tick() {
    /*
    if q_top(running_queue) == current
        return
    context_switch()
    
    
    */
}
/*
void context_switch(struct task_struct* next){
  struct task_struct* prev = current;
  switch_to(prev, next);
};
*/