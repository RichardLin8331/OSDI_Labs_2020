#ifndef R_USER_LIB_H
#define R_USER_LIB_H

int get_current_task_id();
int uart_write(char* buff, unsigned long buff_size);
int uart_recv(char* buff, unsigned long buff_size);
#endif