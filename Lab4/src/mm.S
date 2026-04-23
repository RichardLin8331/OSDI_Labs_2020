.global memzero
memzero:
    cmp     x0, x1
    b.ge    memzero_fin
    str     xzr, [x0], #8  
    b       memzero
memzero_fin:
    ret

.global memcpy
memcpy:
    ldr x3, [x1], #8
    str x3, [x0], #8
    sub x2, x2, #8
    cmp x2, #0
    b.le memcpy_fin
    b memcpy
memcpy_fin:
    ret