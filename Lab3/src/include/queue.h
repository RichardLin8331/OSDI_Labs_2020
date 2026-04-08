#ifndef R_QUEUE_H
#define R_QUEUE_H
#define QUEUE_SIZE 0xFFF

int queue_empty(int q_head, int q_tail) ;
int queue_full(int q_head, int q_tail);
void queue_push(char* q, int* q_tail, char c);
char queue_pop(char* q, int* q_head);

#endif