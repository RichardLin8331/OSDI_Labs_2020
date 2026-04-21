#include "include/string.h"
#include "include/uart.h"
#include "include/shell.h"
#include "include/task.h"
#include "include/scheduler.h"
#include "include/irq_handler.h"

void get_daif() {
    unsigned long daif = 0;
    asm volatile ("mrs %0, DAIF":"=r"(daif));
    daif = (daif >> 5) & 0xF;
    char daif_string[] = "0x00000000"; 
    htos(daif, daif_string);
    char daif_msg[30] = "DAIF is ";
    string_concat(daif_msg, daif_string);
    uart_send_string(daif_msg);
    uart_send_string("\r\n");
}


void idle () {
    while (1) {
        schedule();
        int cnt = 10000;
        while(cnt--);
    }
}

void foo(){
  while(1) {
    irq_enable();
    get_daif();
    uart_send_string("Task pid: ");
    char pid_str[6];
    itos(current->pid, pid_str);
    uart_send_string(pid_str);
    uart_send_string("\r\n");
    irq_disable();
    int cnt = 100000000;
    while(cnt--);
    schedule();
  }
}


void main () {
    uart_init();
    uart_send_string("----- NYCU OSDI LAB 4 -----\r\n");
    
    char s0[] = "# Hello !!\r\n# Finish Booting !!\r\n"; 
    uart_send_string(s0);
    get_daif();

    int N = 2;
    for(int i = 0; i < N; ++i) { // N should > 2
        privilege_task_create(foo);
        uart_send_string("Privilege task created\r\n");
    }
    idle();
}