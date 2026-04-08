#include "include/string.h"
#include "include/uart.h"
#include "include/core_timer.h"

void print_svc_message() {
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

void system_call_handler() {
    int sc_num;
    asm volatile ("mov %0, x8": "=r"(sc_num));

    switch (sc_num) {
        case 0:
            print_svc_message();
            break;

        case 1:
            core_timer_enable();
        break;
        case -1:
        
        }
    return;
}