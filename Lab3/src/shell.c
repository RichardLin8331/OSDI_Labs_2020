#include "include/string.h"
#include "include/uart.h"
#include "include/reboot.h"
#include "include/time.h"
#include "include/mailbox_message.h"
#include "include/load_kernel.h"

int debug = 0;
int parse_command(char* cmd) {
    
    if (debug == 1) {
        char debug_msg[] = "Current Command: ";
        string_concat(debug_msg, cmd);
        uart_send_string(debug_msg);
        uart_send_string("\r\n");
    }
    if (strcmp(cmd, "help") == 0) return 0;
    else if (strcmp(cmd, "hello") == 0) return 1;
    else if (strcmp(cmd, "reboot") == 0) return 2;
    else if (strcmp(cmd, "timestamp") == 0) return 3;
    else if (strcmp(cmd, "board_revision") == 0) return 4;
    else if (strcmp(cmd, "vc_base") == 0) return 5;
    else if (strcmp(cmd, "svc_test") == 0) return 6;
    else if (strcmp(cmd, "brk_test") == 0) return 7;
    else if (strcmp(cmd, "irq") == 0) return 8;
    else if (strcmp(cmd, "daif") == 0) return 9;
    return -1;
}

void execute_command(int cmd_num) {
    switch (cmd_num) {
        case 0:
            uart_send_string("NYCU OSDI Lab1 Shell\r\n\n");
            uart_send_string("Supported Commands: \r\n");
            uart_send_string("help: print shell information\r\n");
            uart_send_string("hello: print hello message\r\n");
            uart_send_string("reboot: reboot the raspi3b board\r\n");
            uart_send_string("timestamp: get current timestamp\r\n");
            uart_send_string("board_revision: get board revision\r\n");
            uart_send_string("vc_base: get VC core base address\r\n");
            uart_send_string("svc_test: test svc instruction\r\n");
            uart_send_string("brk_test: test brk instruction\r\n");
            uart_send_string("daif: get current DAIF value\r\n");

        break;

        case 1:
            uart_send_string("Hello World!\r\n");

        break;

        case 2:
            uart_send_string("Start Reboot\r\n");
            reset(1000);
        break;

        case 3:
            char ts_msg[] = "Timestamp is: ";
            char ts[12];
            //float ts_float = get_timestamp();
            //ftos(ts_float, ts);
            //string_concat(ts_msg, ts);
            string_concat(ts_msg, "\r\n");
            uart_send_string(ts_msg);

        break;
        
        case 4:
            char bv_msg[] = "Board revision is: ";
            char bv[] = "0x00000000";
            get_board_revision(bv);
            string_concat(bv_msg, bv);
            string_concat(bv_msg, "\r\n");
            uart_send_string(bv_msg);
            
        break;

        case 5:
            char vc_msg[] = "VC Core: ";
            char vc_base[] = "0x00000000";
            get_vc_base(vc_base);
            string_concat(vc_msg, vc_base);
            string_concat(vc_msg, "\r\n");
            uart_send_string(vc_msg);
        
        break;

        case 6:
            asm volatile ("mov x8, #0");
            asm volatile ("svc #0");
        break;

        case 7:
            asm volatile ("mov x8, #0");
            asm volatile ("brk #0");
        break;

        case 8:
            asm volatile ("mov x8, #1");
            asm volatile ("brk #0");
        break;

        case 9:
            unsigned long daif = 0;
            asm volatile ("mrs %0, DAIF":"=r"(daif));
            daif = (daif >> 5) & 0xF;
            char daif_string[] = "0x00000000"; 
            htos(daif, daif_string);
            char daif_msg[30] = "DAIF is ";
            string_concat(daif_msg, daif_string);
            uart_send_string(daif_msg);
            uart_send_string("\r\n");
        break;

        case 10:
            unsigned long elr, esr, ec, iss;
            unsigned int el;
            asm volatile("mrs %0, CurrentEL" : "=r" (el));
            el = (el >> 2) & 3;
            char el_string[] = "0x00000000";
            htos(el, el_string);
            uart_send_string("Current EL is ");
            uart_send_string(el_string);
            uart_send_string("\r\n");
        break;
        case -1:
            uart_send_string("Warning: Command Not Found");
        break;
    }
}

void shell_run() {
    uart_send_string("# Shell Start Running\r\n");
    while (1) {
        char cmd[128];
        char *cur_c = cmd;
        uart_send_string("# ");
        while (1){
            char c = uart_get();
            if (c != '\n') {
                *cur_c++ = c;
                uart_send(c);
            } else {
                uart_send_string("\r\n");
                *cur_c++ = '\0';
                execute_command(parse_command(cmd));
                break;
            }
        }
        uart_send_string("\r\n");
    }
}

