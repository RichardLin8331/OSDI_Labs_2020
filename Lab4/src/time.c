float get_timestamp() {
    //return 100.0;
    unsigned long f, c;
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(c));

    return (float) c / f;
}