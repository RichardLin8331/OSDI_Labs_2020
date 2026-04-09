#ifndef R_UART_H
#define R_UART_H

#include "gpio.h"
#include "queue.h"

#define UART0_DR        ((volatile unsigned int*)(MEM_BASE+0x00201000))
#define UART0_FR        ((volatile unsigned int*)(MEM_BASE+0x00201018))
#define UART0_IBRD      ((volatile unsigned int*)(MEM_BASE+0x00201024))
#define UART0_FBRD      ((volatile unsigned int*)(MEM_BASE+0x00201028))
#define UART0_LCRH      ((volatile unsigned int*)(MEM_BASE+0x0020102C))
#define UART0_CR        ((volatile unsigned int*)(MEM_BASE+0x00201030))
#define UART0_IMSC      ((volatile unsigned int*)(MEM_BASE+0x00201038))
#define UART0_MIS       ((volatile unsigned int*)(MEM_BASE+0x00201040))
#define UART0_ICR       ((volatile unsigned int*)(MEM_BASE+0x00201044))
#define UART0_PENDING   ((volatile unsigned int*)(MEM_BASE+0x0000B208))
#define UART0_IRQ_ENABLE   ((volatile unsigned int*)(MEM_BASE+0x0000B214))

extern char sender_queue[QUEUE_SIZE];
extern char receiver_queue[QUEUE_SIZE];

extern int sq_head, sq_tail, rq_head, rq_tail;

void uart_init();
void uart_send(unsigned int c);
char uart_get();
void uart_send_string(char* s);
void uart_IRQ_handler() ;

#endif