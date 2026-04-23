#ifndef R_TASK_QUEUE_H
#define R_TASK_QUEUE_H

#include "task.h"

#define TASK_QUEUE_SIZE 100
extern struct task_struct* running_queue[TASK_QUEUE_SIZE];
extern int running_queue_head, running_queue_tail;

extern struct task_struct* waiting_queue[TASK_QUEUE_SIZE];
extern int waiting_queue_head, waiting_queue_tail;

void task_queue_push(struct task_struct** t_queue, int* t_q_tail, struct task_struct *t);
void task_queue_push_head(struct task_struct** t_queue, int* t_q_head, struct task_struct *t); 
struct task_struct* task_queue_pop(struct task_struct** t_queue, int* t_q_head);

#endif