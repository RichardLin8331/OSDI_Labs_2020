#include "include/string.h"
#include "include/uart.h"
#include "include/shell.h"
#include "include/task.h"
#include "include/task_queue.h"
#include "include/scheduler.h"
#include "include/irq_handler.h"
#include "include/user_lib.h"
#include "include/zombie_reaper.h"
#include "include/core_timer.h"

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

void delay(int delay_cnt){
    while(delay_cnt--);
    return;
}

/*
void idle () {
    while (1) {
        //schedule();
        irq_enable();
        uart_send_string("Return to kernel idle!!\r\n# ");
        int cnt = 10000000000;
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

void foo3(){
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
        uart_send_string("Goto shell... ...\r\n");
        do_exec(shell_run);

        int cnt = 10000000000;
        while(cnt--);
        //schedule();
    }
}
*/

void foo(){
    int tmp = 5;
    
    uart_send_string("Task id: ");
    char pid_s[4];
    itos(get_current_task_id(), pid_s);
    uart_send_string(pid_s);
    uart_send_string(" after exec, tmp address: ");
    char tmp_as[] ="0x00000000";
    htos((unsigned int) &tmp, tmp_as);
    uart_send_string(tmp_as);
    uart_send_string(", tmp value: ");
    char tmp_s[4];
    itos(tmp, tmp_s);
    uart_send_string(tmp_s);
    uart_send_string("\r\n# ");


    exit(0);
}

void test() {
    int cnt = 1;
    
    if (fork() == 0) {
        fork();
        delay(100000);
        fork();
        while(cnt < 10) {
        
            uart_send_string("Task id: ");
            char pid_s[4];
            itos(get_current_task_id(), pid_s);
            uart_send_string(pid_s);
            uart_send_string(", cnt: ");
            char cnt_s[4];
            itos(cnt, cnt_s);
            uart_send_string(cnt_s);
            uart_send_string("\r\n# ");
            
            delay(100000);
            ++cnt;
        }
        exit(0);
        uart_send_string("Should not be printed\r\n");
    } else {
        
        uart_send_string("Task id: ");
        char pid_s[4];
        itos(get_current_task_id(), pid_s);
        uart_send_string(pid_s);
        uart_send_string(" before exec, cnt address: ");
        char cnt_as[] ="0x00000000";
        htos((unsigned int) &cnt, cnt_as);
        uart_send_string(cnt_as);
        uart_send_string(", cnt value: ");
        char cnt_s[4];
        itos(cnt, cnt_s);
        uart_send_string(cnt_s);
        uart_send_string("\r\n# ");

        exec(foo);
    }

}

// -----------above is user code-------------
// -----------below is kernel code-------------

void user_test(){
    do_exec(test);
}

void idle(){
  while(1){
    irq_enable();
    if(num_runnable_tasks() == 2) {
      break;
    }
    schedule();
    delay(1000000);
  }
  uart_send_string("Test finished\r\n");
  while(1);
}

void main () {
    init_kernel_task();
    uart_init();
    uart_send_string("----- NYCU OSDI LAB 4 -----\r\n");
    
    char s0[] = "# Hello !!\r\n# Finish Booting !!\r\n# "; 
    uart_send_string(s0);
    get_daif();
    /*
    int N = 2;
    for(int i = 0; i < N; ++i) { // N should > 2
        privilege_task_create(foo);
        uart_send_string("Privilege task created\r\n");
    }
    */
    privilege_task_create(zombie_reaper);
    privilege_task_create(user_test);
    
    
    core_timer_enable();
    irq_enable();
    idle();
    
}