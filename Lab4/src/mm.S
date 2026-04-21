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
