SECTIONS
{
    . = 0x80000;
    .text.boot : { *(.text.boot) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    . = ALIGN(0x16);
    _bss_begin = .;
    .bss : { *(.bss*) }
    _bss_end = .;
}