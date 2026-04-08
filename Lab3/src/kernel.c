#include "include/string.h"
#include "include/uart.h"
#include "include/shell.h"
void main () {
    uart_init();
    
    uart_send_string("----- NYCU OSDI LAB 3 -----\r\n");
    /*
    unsigned long el = 0;
    asm volatile("mrs %0, CurrentEL" : "=r" (el));
    el = (el >> 2) & 3;
    char el_string[20] = "0x00000000";
    htos(el, el_string);
    uart_send_string("Current EL is ");
    uart_send_string(el_string);
    uart_send_string("\r\n");*/
    
    char s0[] = "# Hello !!\r\n# Finish Booting !!\r\n"; 
    uart_send_string(s0);
    
    shell_run();
}