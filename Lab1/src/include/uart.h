#ifndef R_UART_H
#define R_UART_H

#include "gpio.h"

#define AUX_ENABLES     ((volatile unsigned int *) (MEM_BASE  + 0x00215004))
#define AUX_MU_IO_REG   ((volatile unsigned int *) (MEM_BASE  + 0x00215040))
#define AUX_MU_IER_REG  ((volatile unsigned int *) (MEM_BASE  + 0x00215044))
#define AUX_MU_IIR_REG  ((volatile unsigned int *) (MEM_BASE  + 0x00215048))
#define AUX_MU_LCR_REG  ((volatile unsigned int *) (MEM_BASE  + 0x0021504C))
#define AUX_MU_MCR_REG  ((volatile unsigned int *) (MEM_BASE  + 0x00215050))
#define AUX_MU_LSR_REG  ((volatile unsigned int *) (MEM_BASE  + 0x00215054))
#define AUX_MU_CNTL_REG ((volatile unsigned int *) (MEM_BASE  + 0x00215060))
#define AUX_MU_BAUD_REG ((volatile unsigned int *) (MEM_BASE  + 0x00215068))

void uart_init();
void uart_send(unsigned int c);
char uart_get();
void uart_send_string(char* s);

#endif