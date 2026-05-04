#include "include/task.h"
#include "include/task_queue.h"

struct priority_queue running_queue = {.size = 0};

void swap_node(struct task_struct** n1, struct task_struct** n2) {
  struct task_struct* tmp;
  tmp = *n1;
  *n1 = *n2;
  *n2 = tmp;
}

int num_runnable_tasks() {
    return running_queue.size;
}

void priority_queue_push(struct priority_queue* pq, struct task_struct* t) {
    pq->pq[pq->size++] = t;
    int cur_idx = pq->size - 1;
    while (cur_idx > 0) {
        int par_idx = (cur_idx - 1) / 2;
        if (pq->pq[cur_idx]->priority < pq->pq[par_idx]->priority) {
            swap_node(&pq->pq[par_idx], &pq->pq[cur_idx]);
            cur_idx = par_idx;
        } else cur_idx = -1;
    }
}

void minheapify(struct priority_queue* pq) {
    int cur_idx = 0;
    while (cur_idx < pq->size / 2) {
        int l = cur_idx * 2 + 1;
        int r = cur_idx * 2 + 2;
        int min_idx = cur_idx;
        if (l < pq->size && pq->pq[l]->priority < pq->pq[min_idx]->priority) min_idx = l;
        if (r < pq->size && pq->pq[r]->priority < pq->pq[min_idx]->priority) min_idx = r;
        if (min_idx != cur_idx) {
            swap_node(&pq->pq[min_idx], &pq->pq[cur_idx]);
            cur_idx = min_idx;
        } else cur_idx = pq->size;
    }
}

struct task_struct* priority_queue_pop(struct priority_queue* pq) {
    swap_node(&pq->pq[0], &pq->pq[--pq->size]);
    minheapify(pq);
    return pq->pq[pq->size];
}

struct task_struct* waiting_queue[TASK_QUEUE_SIZE];
int waiting_queue_head = 0, waiting_queue_tail = 0;

struct task_struct* zombie_queue[TASK_QUEUE_SIZE];
int zombie_queue_head = 0, zombie_queue_tail = 0;

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

