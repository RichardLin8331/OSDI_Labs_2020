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
    else if (strcmp(cmd, "timer") == 0) return 8;
    else if (strcmp(cmd, "timer_stop") == 0) return 9;
    else if (strcmp(cmd, "daif") == 0) return 10;
    else if (strcmp(cmd, "ri") == 0) return 11;
    else if (strcmp(cmd, "uwt") == 0) return 12;
    else if (strcmp(cmd, "urt") == 0) return 13;
    return -1;
}
int sys_calll_ri() {
    asm volatile ("mov x8, #4");
    asm volatile ("svc #0");
    int ret_ri;
    asm volatile("mov %0, x0":"=r"(ret_ri):: "x0");
    return ret_ri;
}

int uart_write_test() {
    char buff[] = "Test uart_write\r\n";
    unsigned long buff_addr = (unsigned long) buff;
    int buff_size = get_length(buff);
    int ret_ri = 0;
    asm volatile (
        "mov x3, %[ptr] \n\t"  // Map buffer to x0
        "mov x1, %[len] \n\t"  // Map size to x1
        "mov x8, #5     \n\t"  // Syscall number
        "svc #0         \n\t"  // THE ATOMIC TRIGGER
        "mov %[res], x0 \n\t"  // Capture return value
        : [res] "=r" (ret_ri)              // Output
        : [ptr] "r" (buff_addr), [len] "r" (buff_size) // Inputs
        : "x0", "x1", "x3", "x8", "memory"       // Clobber list
    );
    return ret_ri;
}

int uart_recv_test() {
    //uart_send_string("Test uart_recv\r\n");
    char buff[10];
    unsigned long buff_addr = (unsigned long) buff;
    int buff_size = 6;
    int ret_ri = 0;
    asm volatile (
        "mov x3, %[ptr] \n\t"  // Map buffer to x0
        "mov x1, %[len] \n\t"  // Map size to x1
        "mov x8, #6     \n\t"  // Syscall number
        "svc #0         \n\t"  // THE ATOMIC TRIGGER
        "mov %[res], x0 \n\t"  // Capture return value
        : [res] "=r" (ret_ri)              // Output
        : [ptr] "r" (buff_addr), [len] "r" (buff_size) // Inputs
        : "x0", "x1", "x3", "x8", "memory"       // Clobber list
    );
    uart_send_string("\r\nBuffer got: ");
    uart_send_string(buff);
    uart_send_string("\r\n");
    return ret_ri;
}

void execute_command(int cmd_num) {
    switch (cmd_num) {
        case 0:
            uart_send_string("NYCU OSDI Lab3 Shell\r\n\n");
            uart_send_string("Supported Commands: \r\n");
            uart_send_string("help: print shell information\r\n");
            uart_send_string("hello: print hello message\r\n");
            uart_send_string("reboot: reboot the raspi3b board\r\n");
            uart_send_string("timestamp: get current timestamp\r\n");
            uart_send_string("board_revision: get board revision\r\n");
            uart_send_string("vc_base: get VC core base address\r\n");
            uart_send_string("svc_test: test svc instruction\r\n");
            uart_send_string("brk_test: test brk instruction\r\n");
            uart_send_string("timer: start core timer\r\n");
            uart_send_string("timer_stop: stop core timer\r\n");
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
            asm volatile ("svc #0");
        break;

        case 9:
            asm volatile ("mov x8, #2");
            asm volatile ("svc #0");
        break;

        case 10:
            asm volatile ("mov x8, #3");
            asm volatile ("svc #0");
        break;

        case 11:
            long ri = sys_calll_ri();
            char ri_string[5];
            itos(ri, ri_string);
            uart_send_string(ri_string);
        break;

        case 12:
            long ri2 = uart_write_test();
            uart_send_string("Get wrote bytes: ");
            char ri2_string[5];
            itos(ri2, ri2_string);
            uart_send_string(ri2_string);
        break;

        case 13:
            long ri3 = uart_recv_test();
            uart_send_string("Get recv bytes: ");
            char ri3_string[5];
            itos(ri3, ri3_string);
            uart_send_string(ri3_string);
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

