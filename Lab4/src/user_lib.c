#include "include/uart.h"

int get_current_task_id() {
    int ret_ri = 0;
    asm volatile ("mov x8, #4");
    asm volatile ("svc #0");
    asm volatile ("mov %0, x0":"=r"(ret_ri));
    return ret_ri;
}

int uart_write(char* buff, unsigned long buff_size) {
    unsigned long buff_addr = (unsigned long) buff;
    int ret_ri = 0;
    asm volatile ("mov x0, %0"::"r"(buff_addr));
    asm volatile ("mov x1, %0"::"r"(buff_size));
    asm volatile ("mov x8, #5");
    asm volatile ("svc #0");
    asm volatile ("mov %0, x0":"=r"(ret_ri));
    
    return ret_ri;
}

int uart_recv(char* buff, unsigned long buff_size) {
    
    unsigned long buff_addr = (unsigned long) buff;
    int ret_ri = 0;

    asm volatile ("mov x0, %0"::"r"(buff_addr));
    asm volatile ("mov x1, %0"::"r"(buff_size));
    asm volatile ("mov x8, #6");
    asm volatile ("svc #0");
    asm volatile ("mov %0, x0":"=r"(ret_ri));
    
    uart_send_string("\r\n# Buffer got: ");
    uart_send_string(buff);
    uart_send_string("\r\n# ");
    return ret_ri;
}

int exec(void* fn) {
    unsigned long fn_addr = (unsigned long) fn;
    int ret_ri = 0;

    asm volatile ("mov x0, %0"::"r"(fn_addr));
    asm volatile ("mov x8, #7");
    asm volatile ("svc #0");
    asm volatile ("mov %0, x0":"=r"(ret_ri));
    return ret_ri;
}

int fork() {
    int ret_ri = 0;
    asm volatile ("mov x8, #8");
    asm volatile ("svc #0");
    asm volatile ("mov %0, x0":"=r"(ret_ri));
    return ret_ri;
}

void exit(int status) {
    asm volatile ("mov x0, %0"::"r"(status));
    asm volatile ("mov x8, #9");
    asm volatile ("svc #0");
}