#include "include/string.h"
#include "include/uart.h"
#include "include/core_timer.h"
#include "include/scheduler.h"
#include "include/irq_handler.h"

void svc_print_message() {
    unsigned long elr, esr, ec, iss;
    asm volatile ("mrs %0, elr_el1":"=r"(elr));
    asm volatile ("mrs %0, esr_el1":"=r"(esr));
    ec = (esr & 0xFFFFFFFF) >> 26;
    iss = esr & 0xFFFFFF;
    char elr_string[] = "0x00000000";
    char ec_string[] = "0x00000000";
    char iss_string[] = "0x00000000";
    htos(elr, elr_string);
    htos(ec, ec_string);
    htos(iss, iss_string);
    char elr_msg[] = "ELR_EL1 is ";
    string_concat(elr_msg, elr_string);
    uart_send_string(elr_msg);
    uart_send_string("\r\n");
    
    char ec_msg[] = "EC is ";
    string_concat(ec_msg, ec_string);
    uart_send_string(ec_msg);
    uart_send_string("\r\n");

    char iss_msg[] = "ISS is ";
    string_concat(iss_msg, iss_string);
    uart_send_string(iss_msg);
    uart_send_string("\r\n");

}

void svc_print_daif() {
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

int svc_uart_write(unsigned long buff_addr, unsigned long buff_size) {
    int uw_cnt = 0;
    char* buff_string = (char*) buff_addr;
    for (uw_cnt = 0; uw_cnt < buff_size; uw_cnt++) uart_send(*buff_string++);
    return uw_cnt;
}

int svc_uart_recv(unsigned long buff_addr, unsigned long buff_size) {
    irq_enable();
    char* buff_string = (char*) buff_addr;
    int uw_cnt = 0;        
    for (uw_cnt = 0; uw_cnt < buff_size; uw_cnt++) {
        current->task_status = TASK_WAITING;
        schedule();
        while (queue_empty(rq_head, rq_tail) == 1); 
        char tmp = queue_pop(receiver_queue, &rq_head);
        uart_send(tmp);
        buff_string[uw_cnt] = tmp; 
    }
    buff_string[uw_cnt] = '\0';
    irq_disable();
    return uw_cnt;
}

long system_call_handler() {
    int sc_num;
    asm volatile ("mov %0, x8": "=r"(sc_num));

    switch (sc_num) {
        case 0:
            svc_print_message();
            break;

        case 1:
            core_timer_enable();
            uart_send_string("Timer start\r\n");
        break;

        case 2:
            core_timer_disable();
            uart_send_string("Timer stop\r\n");
        break;

        case 3:
            svc_print_daif();
        break;

        case 4:
            return current->pid;
        break;

        case 5:
            unsigned long buff_addr, buff_size;
            buff_addr = current->trapframe->regs[0];
            buff_size = current->trapframe->regs[1];
            return svc_uart_write(buff_addr, buff_size);
        break;

        case 6:
            unsigned long buff_addr2, buff_size2;
            buff_addr2 = current->trapframe->regs[0];
            buff_size2 = current->trapframe->regs[1];
           
            return svc_uart_recv(buff_addr2, buff_size2);
        break;

        case 7:
            unsigned long fn = current->trapframe->regs[0];
            do_exec(fn);
            return 0;
        break;

        case 8:
            return user_task_create();
        break;

        case 9:
            int status = (int) current->trapframe->regs[0];
            task_exit(status);
        break;


        case -1:
        
        }
    return 0;
}