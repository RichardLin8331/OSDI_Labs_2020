
// save general registers to stack
.macro save_all
  sub sp, sp, 32 * 9
  stp x0, x1, [sp ,16 * 0]
  stp x2, x3, [sp ,16 * 1]
  stp x4, x5, [sp ,16 * 2]
  stp x6, x7, [sp ,16 * 3]
  stp x8, x9, [sp ,16 * 4]
  stp x10, x11, [sp ,16 * 5]
  stp x12, x13, [sp ,16 * 6]
  stp x14, x15, [sp ,16 * 7]
  stp x16, x17, [sp ,16 * 8]
  stp x18, x19, [sp ,16 * 9]
  stp x20, x21, [sp ,16 * 10]
  stp x22, x23, [sp ,16 * 11]
  stp x24, x25, [sp ,16 * 12]
  stp x26, x27, [sp ,16 * 13]
  stp x28, x29, [sp ,16 * 14]
  mrs	x22, sp_el0
	mrs	x23, elr_el1
	mrs	x24, spsr_el1
  stp x22, x23, [sp ,16 * 15]
  stp x24, x30, [sp, 16 * 16]
.endm

// load general registers from stack
.global load_all
load_all:
  ldp x24, x30, [sp, 16 * 16]
  ldp x22, x23, [sp ,16 * 15]
  msr	sp_el0, x22
	msr	elr_el1, x23
	msr	spsr_el1, x24
  ldp x0, x1, [sp ,16 * 0]
  ldp x2, x3, [sp ,16 * 1]
  ldp x4, x5, [sp ,16 * 2]
  ldp x6, x7, [sp ,16 * 3]
  ldp x8, x9, [sp ,16 * 4]
  ldp x10, x11, [sp ,16 * 5]
  ldp x12, x13, [sp ,16 * 6]
  ldp x14, x15, [sp ,16 * 7]
  ldp x16, x17, [sp ,16 * 8]
  ldp x18, x19, [sp ,16 * 9]
  ldp x20, x21, [sp ,16 * 10]
  ldp x22, x23, [sp ,16 * 11]
  ldp x24, x25, [sp ,16 * 12]
  ldp x26, x27, [sp ,16 * 13]
  ldp x28, x29, [sp ,16 * 14]
  add sp, sp, 32 * 9
  eret

  // save general registers to stack
.macro save_all_el1_irq
  sub sp, sp, 32 * 9
  stp x0, x1, [sp ,16 * 0]
  stp x2, x3, [sp ,16 * 1]
  stp x4, x5, [sp ,16 * 2]
  stp x6, x7, [sp ,16 * 3]
  stp x8, x9, [sp ,16 * 4]
  stp x10, x11, [sp ,16 * 5]
  stp x12, x13, [sp ,16 * 6]
  stp x14, x15, [sp ,16 * 7]
  stp x16, x17, [sp ,16 * 8]
  stp x18, x19, [sp ,16 * 9]
  stp x20, x21, [sp ,16 * 10]
  stp x22, x23, [sp ,16 * 11]
  stp x24, x25, [sp ,16 * 12]
  stp x26, x27, [sp ,16 * 13]
  stp x28, x29, [sp ,16 * 14]
	mrs	x23, elr_el1
	mrs	x24, spsr_el1
  stp x22, x23, [sp ,16 * 15]
  stp x24, x30, [sp, 16 * 16]
.endm

// load general registers from stack
.global load_all_el1_irq
load_all_el1_irq:
  ldp x24, x30, [sp, 16 * 16]
  ldp x22, x23, [sp ,16 * 15]
	msr	elr_el1, x23
	msr	spsr_el1, x24
  ldp x0, x1, [sp ,16 * 0]
  ldp x2, x3, [sp ,16 * 1]
  ldp x4, x5, [sp ,16 * 2]
  ldp x6, x7, [sp ,16 * 3]
  ldp x8, x9, [sp ,16 * 4]
  ldp x10, x11, [sp ,16 * 5]
  ldp x12, x13, [sp ,16 * 6]
  ldp x14, x15, [sp ,16 * 7]
  ldp x16, x17, [sp ,16 * 8]
  ldp x18, x19, [sp ,16 * 9]
  ldp x20, x21, [sp ,16 * 10]
  ldp x22, x23, [sp ,16 * 11]
  ldp x24, x25, [sp ,16 * 12]
  ldp x26, x27, [sp ,16 * 13]
  ldp x28, x29, [sp ,16 * 14]
  add sp, sp, 32 * 9
  eret


// Simple vector table
.align 11 // vector table should be aligned to 0x800
.global exception_table
exception_table:
  save_all
  bl exception_handler // 0x000
  b load_all

  .align 7 // entry size is 0x80
  save_all
  bl exception_handler // 0x80
  b load_all

  .align 7
  save_all
  bl exception_handler // 0x100
  b load_all

  .align 7
  save_all
  bl exception_handler // 0x180
  b load_all

  .align 7
  save_all
  bl system_call_handler // 0x200
  str	x0, [sp, #0] 
  b load_all
  
  .align 7
  save_all_el1_irq
  bl irq_handler // 0x280
  b load_all_el1_irq

  .align 7
  save_all
  bl exception_handler // 0x300
  b load_all

  .align 7
  save_all
  bl exception_handler //0x380
  b load_all

  .align 7
  save_all
  bl system_call_handler //0x400
  str	x0, [sp, #0] 
  b load_all
  
  .align 7
  save_all
  bl irq_handler
  b load_all

  .align 7
  save_all
  bl exception_handler
  b load_all

  .align 7
  save_all
  bl exception_handler
  b load_all

  .align 7
  save_all
  bl exception_handler
  b load_all

  .align 7
  save_all
  bl exception_handler
  b load_all

  .align 7
  save_all
  bl exception_handler
  b load_all

  .align 7
  save_all
  bl exception_handler
  b load_all

  .align 7

.global return_from_fork
return_from_fork:
  cbz x19, return_to_el0
  blr x19
return_to_el0:
  mov x0, #0
  b load_all