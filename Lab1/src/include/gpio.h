#ifndef R_GPIO_H
#define R_GPIO_H
#define MEM_BASE (0x3F000000)

#define GPFSEL1         ((volatile unsigned int *) (MEM_BASE + 0x00200004))
#define GPPUD           ((volatile unsigned int *) (MEM_BASE + 0x00200094))
#define GPPUDCLK0       ((volatile unsigned int *) (MEM_BASE + 0x00200098))

#endif