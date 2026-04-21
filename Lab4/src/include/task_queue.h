#ifndef R_TASK_QUEUE_H
#define R_TASK_QUEUE_H

#include "task.h"

#define RUNNING_QUEUE_SIZE 100
extern struct task_struct* running_queue[RUNNING_QUEUE_SIZE];
extern int running_queue_head, running_queue_tail;

void running_queue_push(struct task_struct** r_queue, int* r_q_tail, struct task_struct *t);
struct task_struct* running_queue_pop(struct task_struct** r_queue, int* r_q_head);

#endif