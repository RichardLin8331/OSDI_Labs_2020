.section ".text.boot"
.global _start

_start:
      mrs x0, mpidr_el1
      and x0, x0, 3
      cbz x0, 2f
1:
      wfe
      b 1b


2:

// load exception_table to vbar_el2
    ldr x0, =exception_table
    msr vbar_el2, x0

    ldr x1, =_start
    mov sp, x1

    ldr     x0, =_bss_begin
    ldr     x1, =_bss_end
3:
    cmp     x0, x1
    b.ge    4f
    str     xzr, [x0], #8  
    b       3b


4:
    bl main
    b 1b