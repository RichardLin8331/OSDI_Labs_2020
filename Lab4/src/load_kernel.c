#include "include/uart.h"
#include "include/string.h"

void load_kernel() {
    unsigned long addr = 0;
    int size = 0;

    //uart_send_string("Waiting for Loading Kernel");
    while (uart_get() != 'a') uart_send('E');
    uart_send('A');
    addr = uart_get();
    addr |= uart_get() << 8;
    addr |= uart_get() << 16;
    addr |= uart_get() << 24;
    uart_send('C');
    char addr_str[] = "0x00000000";
    htos(addr, addr_str);
    char addr_msg[] = "RPI: Set addr at ";
    string_concat(addr_msg, addr_str);
    uart_send_string(addr_msg);

    char tmp = uart_get();
    while(tmp == '\n') {
        tmp = uart_get();
    }
    while (tmp != 's') {
        uart_send('E');
        uart_send(tmp);
        tmp = uart_get();
    } 
    uart_send('R');
    while (tmp != 's') {
        uart_send('E');
        uart_send(tmp);
        tmp = uart_get();
    } 
    size = uart_get();
    size |= uart_get() << 8;
    size |= uart_get() << 16;
    size |= uart_get() << 24;
    uart_send('C');
    char* new_kernel_addr = (char*) addr;
    while (size--) *new_kernel_addr++ = uart_get();
    uart_send_string("Finish loading new Kernel.\r\n");
    //char total_bytes_msg[] = "Got ";

    asm volatile (
        "mov x30, %0\n\t"
        "ret"
        :
        : "r" (addr)
        : "x30"
    );
    /*
    asm volatile (
        //"ldr x30, =0x88000;"
        "ret;"
    );*/
    
}

/*
load_kernel()
    get_addr()
        get 'a'
        get long addr
        send '\x03'
    get_size()
        get 's'
        get int size
        send '\x03'
    get_kernel()
    set_addr()

*/