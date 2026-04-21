.section ".text.boot"
#define USER_STACK 0x800000

.global _start

_start:
      mrs x0, mpidr_el1
      and x0, x0, 3
      cbz x0, el2_init
1:
      wfe
      b 1b

el2_init:
    ldr x0, =exception_table
    msr vbar_el2, x0
    mrs x0, hcr_el2
    orr x0, x0, #(1 << 31) // EL1 use aarch64
    bic x0, x0, #(1 << 4)
    msr hcr_el2, x0
    mov x0, 0x3c5 // EL1h (SPSel = 1) with interrupt disabled
    msr spsr_el2, x0
    adr x0, el1_init // load exception return address
    msr elr_el2, x0
    mov x0, 0x200000 // init kernel sp for el1 option 1
    msr sp_el1, x0

    eret

el1_init:
    mrs x0, cpacr_el1
    orr x0, x0, #(3 << 20)      // Full access to CP10 and CP11
    msr cpacr_el1, x0
    isb

    ldr x0, =exception_table
    msr vbar_el1, x0

    ldr     x0, =_bss_begin
    ldr     x1, =_bss_end
3:
    cmp     x0, x1
    b.ge    4f
    str     xzr, [x0], #8  
    b       3b
4:
    mov x0, #0 // EL0 with interrupt enabled
    msr spsr_el1, x0

    bl main
    b 1b