#include "include/string.h"
#include "include/uart.h"
#include "include/shell.h"
#include "include/task.h"
#include "include/scheduler.h"
#include "include/irq_handler.h"
#include "include/user_lib.h"

void get_daif() {
    unsigned long daif = 0;
    asm volatile ("mrs %0, DAIF":"=r"(daif));
    daif = (daif >> 5) & 0xF;
    char daif_string[] = "0x00000000"; 
    htos(daif, daif_string);
    char daif_msg[30] = "DAIF is ";
    string_concat(daif_msg, daif_string);
    uart_send_string(daif_msg);
    uart_send_string("\r\n\r\n# ");
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
        uart_send_string("Task pid: ");
        char pid_str[6];
        itos(current->pid, pid_str);
        uart_send_string(pid_str);
        uart_send_string("\r\n# ");
        get_daif();
        //uart_send_string("\r\n\r\n# ");

        //schedule();
        int cnt = 10000000000;
        while(cnt--);
    }
}
void user_task() {
    while(1) {
        //uart_send_string("Goto EL0 user_task()\r\n# ");
        char buff_s[] = "Goto EL0 user_task()\r\n# Current PID is ";
        int pid = get_current_task_id();
        char pid_s[5];
        itos(pid, pid_s);
        string_concat(buff_s, pid_s);
        char buff_2[] = "\r\n# ";
        string_concat(buff_s, buff_2);
        char buff_3[] = "Type something: ";
        //string_concat(buff_s, buff_3);
        int buff_size = get_length(buff_3);
        uart_write(buff_3, buff_size);

        char buff_r[10];
        int buff_size_r = 6;
        uart_recv(buff_r, buff_size_r);

        buff_size = get_length(buff_s);
        uart_write(buff_s, buff_size);
        int cnt = 10000000000;
        while(cnt--);
    }
    
}

void user_task_22() {
    while(1) {
        //uart_send_string("Goto EL0 user_task()\r\n# ");
        char buff_s[] = "Goto EL0 user_task_22()\r\n# Current PID is ";
        int pid = get_current_task_id();
        char pid_s[5];
        itos(pid, pid_s);
        string_concat(buff_s, pid_s);
        char buff_2[] = "\r\n# ";
        string_concat(buff_s, buff_2);
        
        int buff_size = get_length(buff_s);
        uart_write(buff_s, buff_size);
        int cnt = 10000000000;
        while(cnt--);
    }
    
}

void user_task_21() {
    while(1) {
        //uart_send_string("Goto EL0 user_task()\r\n# ");
        char buff_s[] = "Goto EL0 user_task_21()\r\n# Current PID is ";
        int pid = get_current_task_id();
        char pid_s[5];
        itos(pid, pid_s);
        string_concat(buff_s, pid_s);
        char buff_2[] = "\r\n# ";
        string_concat(buff_s, buff_2);
        
        int buff_size = get_length(buff_s);
        uart_write(buff_s, buff_size);
        exec(user_task_22);
        int cnt = 10000000000;
        while(cnt--);
    }
    
}

void user_task_3() {
    int pid = fork();
    while(1) {
        //uart_send_string("Goto EL0 user_task()\r\n# ");
        if (pid != 0) {
            char buff_s[] = "Goto EL0 user_task_3()\r\n# This is parent process\r\n# Current PID is ";
            int pid = get_current_task_id();
            char pid_s[5];
            itos(pid, pid_s);
            string_concat(buff_s, pid_s);
            char buff_2[] = "\r\n\r\n# ";
            string_concat(buff_s, buff_2);
            
            int buff_size = get_length(buff_s);
            uart_write(buff_s, buff_size);

            int cnt = 10000000000;
            while(cnt--);
        } else {
            char buff_s[] = "Goto EL0 user_task_3()\r\n# This is child process\r\n# Current PID is ";
            int pid = get_current_task_id();
            char pid_s[5];
            itos(pid, pid_s);
            string_concat(buff_s, pid_s);
            char buff_2[] = "\r\n\r\n# ";
            string_concat(buff_s, buff_2);
            
            int buff_size = get_length(buff_s);
            uart_write(buff_s, buff_size);

            int cnt = 10000000000;
            while(cnt--);
        }
    }
    
}



void foo2(){
    while(1) {
        irq_enable();
        get_daif();
        uart_send_string("Task pid: ");
        char pid_str[6];
        itos(current->pid, pid_str);
        uart_send_string(pid_str);
        uart_send_string("\r\n# ");
        get_daif();
        //irq_disable();
        do_exec(user_task_3);

        int cnt = 10000000000;
        while(cnt--);
        //schedule();
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
    privilege_task_create(foo2);
    core_timer_enable();
    irq_enable();
    idle();
    //irq_disable();
    
}