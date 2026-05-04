#ifndef R_SCHEDULER_H
#define R_SCHEDULER_H

#define current get_current()

#include "task.h"
#include "queue.h"

void switch_to(struct task_struct* prev, struct task_struct* next);
struct task_struct* get_current();
void schedule();


#endif