#include "include/uart.h"
void exception_handler() {
    uart_send_string("EXCEPTION!!\r\n");
}