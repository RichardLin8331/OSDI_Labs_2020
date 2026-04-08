#include "include/uart.h"
#include "include/core_timer.h"
#include "include/string.h"
int core_timer_cnt = 0;
void irq_handler() {
    core_timer_cnt++;
    uart_send_string("Core timer triggered.\r\n# ");
    uart_send_string("Jiffies: ");
    char timer_cnt_string[3];
    itos(core_timer_cnt, timer_cnt_string);
    uart_send_string(timer_cnt_string);
    uart_send_string("\r\n# ");
    core_timer_handler();
}