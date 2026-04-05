#include "include/string.h"
#include "include/uart.h"
#include "include/shell.h"
void main () {
    uart_init();
    uart_send_string("----- NYCU OSDI LAB 1 -----\r\n");
    
    char s0[] = "# Hello !!\r\n# Finish Booting !!\r\n"; 
    uart_send_string(s0);
    
    shell_run();
}