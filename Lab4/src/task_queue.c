#include "include/task.h"
#include "include/task_queue.h"

struct task_struct* running_queue[RUNNING_QUEUE_SIZE];
int running_queue_head = 0, running_queue_tail = 0;

void running_queue_push(struct task_struct** r_queue, int* r_q_tail, struct task_struct *t) {
    r_queue[(*r_q_tail)++] = t;
    (*r_q_tail) %= RUNNING_QUEUE_SIZE;
}

struct task_struct* running_queue_pop(struct task_struct** r_queue, int* r_q_head) {
    struct task_struct* tmp = r_queue[(*r_q_head)++];
    (*r_q_head) %= RUNNING_QUEUE_SIZE;
    return tmp;
}