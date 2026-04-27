#ifndef R_SCHEDULER_H
#define R_SCHEDULER_H

#define current get_current()

#include "task.h"
#include "queue.h"

//extern struct task_struct* running_queue[TASK_POOL_SIZE];
//extern int running_queue_head, running_queue_tail;

void switch_to(struct task_struct* prev, struct task_struct* next);
struct task_struct* get_current();
void schedule();


#endif