#ifndef R_TASK_QUEUE_H
#define R_TASK_QUEUE_H

#include "task.h"

#define TASK_QUEUE_SIZE 100

struct priority_queue {
    struct task_struct* pq[TASK_QUEUE_SIZE];
    int size;
};

extern struct priority_queue running_queue;

int num_runnable_tasks();
void priority_queue_push(struct priority_queue* pq, struct task_struct* n);
struct task_struct* priority_queue_pop(struct priority_queue* pq);

extern struct task_struct* waiting_queue[TASK_QUEUE_SIZE];
extern int waiting_queue_head, waiting_queue_tail;

extern struct task_struct* zombie_queue[TASK_QUEUE_SIZE];
extern int zombie_queue_head, zombie_queue_tail;

void task_queue_push(struct task_struct** t_queue, int* t_q_tail, struct task_struct *t);
void task_queue_push_head(struct task_struct** t_queue, int* t_q_head, struct task_struct *t); 
struct task_struct* task_queue_pop(struct task_struct** t_queue, int* t_q_head);
int num_runnable_tasks();
#endif