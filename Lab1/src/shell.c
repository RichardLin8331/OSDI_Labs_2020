#include "include/string.h"
#include "include/uart.h"
#include "include/reboot.h"
#include "include/time.h"

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

        break;

        case 1:
        uart_send_string("Hello World !\r\n");

        break;

        case 2:
        uart_send_string("Start Reboot\r\n");
        reset(1000);
        break;

        case 3:
        char ts_msg[] = "Timestamp is: ";
        char ts[128];
        float ts_float = get_timestamp();
        ftos(ts_float, ts);
        string_concat(ts_msg, ts);
        string_concat(ts_msg, "\r\n");
        uart_send_string(ts_msg);

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

