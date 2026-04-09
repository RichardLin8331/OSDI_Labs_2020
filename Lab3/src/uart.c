#include "include/uart.h"
#include "include/mailbox.h"
#include "include/queue.h"

char sender_queue[QUEUE_SIZE];
char receiver_queue[QUEUE_SIZE];
int sq_head, sq_tail, rq_head, rq_tail;

void uart_init() {

    *UART0_CR = 0;         // turn off UART0

    /* set up clock for consistent divisor values */
    mbox[0] = 9*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;           // UART clock
    mbox[6] = 4000000;     // 4Mhz
    mbox[7] = 0;           // clear turbo
    mbox[8] = MBOX_TAG_LAST;
    mbox_call(MBOX_CH_PROP);



    // GPIO
    unsigned int r = *GPFSEL1;
    r &= ~((7 << 12) | (7 << 15)); // 清除 pin 14, 15 的設定
    r |= (2 << 12) | (2 << 15);    // 2 代表 Alt5 功能 (Mini UART)
    *GPFSEL1 = r;

    // 關閉 Pull-up/down 以節省電力並確保訊號純淨
    *GPPUD = 0;
    for(int i=0; i<150; i++) asm volatile("nop");
    *GPPUDCLK0 = ((1 << 14) | (1 << 15));
    for(int i=0; i<150; i++) asm volatile("nop");
    *GPPUDCLK0 = 0;

    *UART0_ICR = 0x7FF;    // clear interrupts
    *UART0_IBRD = 2;       // 115200 baud
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0x7<<4;  // 8n1, enable FIFOs
    *UART0_IMSC = 0x30;
    *UART0_CR = 0x301;     // enable Tx, Rx, UART
    *UART0_IRQ_ENABLE = 0x2000000;
    
    sq_head = 0; sq_tail = 0; rq_head = 0; rq_tail = 0;
}

void uart_send(unsigned int c) {

    if (((*UART0_FR)&0x80)) {
        if (queue_empty(sq_head, sq_tail) == 0) {
            char tmp = queue_pop(sender_queue, &sq_head);
            *UART0_DR = tmp;
            queue_push(sender_queue, &sq_tail, c);
        } else {
            *UART0_DR = c;
        } 
    } else {
        if (!queue_full(sq_head, sq_tail)) {
            queue_push(sender_queue, &sq_tail, c);
        }
    }

}

char uart_get() {
    while (queue_empty(rq_head, rq_tail) == 1);

    char c = queue_pop(receiver_queue, &rq_head);
    return c == '\r' ? '\n' : c;
}

void uart_send_string(char* s) {
    while (*s != '\0') uart_send(*s++);
}

void uart_IRQ_handler() {
    unsigned int uart_irq_mis = *UART0_MIS;
    if (uart_irq_mis & 0x10) { 

        while (!((*UART0_FR) & 0x10) && !queue_full(rq_head, rq_tail)) {
            queue_push(receiver_queue, &rq_tail, (*UART0_DR));
        }

    } else if (uart_irq_mis & 0x20) {
        while (queue_empty(sq_head, sq_tail) == 0) {
            while ((*UART0_FR) & 0x20);
            *UART0_DR = queue_pop(sender_queue, &sq_head);
        }
    }
    *UART0_ICR |= uart_irq_mis;
    return;
}