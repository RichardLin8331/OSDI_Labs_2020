#include "include/task.h"
#include "include/task_queue.h"

struct task_struct* running_queue[TASK_QUEUE_SIZE];
int running_queue_head = 0, running_queue_tail = 0;

struct task_struct* waiting_queue[TASK_QUEUE_SIZE];
int waiting_queue_head = 0, waiting_queue_tail = 0;

void task_queue_push(struct task_struct** t_queue, int* t_q_tail, struct task_struct *t) {
    t_queue[(*t_q_tail)++] = t;
    (*t_q_tail) %= TASK_QUEUE_SIZE;
}

void task_queue_push_head(struct task_struct** t_queue, int* t_q_head, struct task_struct *t) {
    *t_q_head = *t_q_head -1 + TASK_QUEUE_SIZE;
    (*t_q_head) %= TASK_QUEUE_SIZE;
    t_queue[(*t_q_head)] = t;
    
}

struct task_struct* task_queue_pop(struct task_struct** t_queue, int* t_q_head) {
    struct task_struct* tmp = t_queue[(*t_q_head)++];
    (*t_q_head) %= TASK_QUEUE_SIZE;
    return tmp;
}