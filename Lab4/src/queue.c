#include "include/queue.h"

int queue_empty(int q_head, int q_tail) {
    return (q_head == q_tail)? 1 : 0;
}

int queue_full(int q_head, int q_tail) {
    if ((q_tail + 1) % QUEUE_SIZE == q_head) return 1;
    return 0;
}

void queue_push(char* q, int* q_tail, char c) {
    q[(*q_tail)++] = c;
    *(q_tail) %= QUEUE_SIZE;
}

char queue_pop(char* q, int* q_head) {
    char tmp = q[(*q_head)++];
    *(q_head) %= QUEUE_SIZE;
    return tmp;
}