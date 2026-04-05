#include "include/uart.h"

void uart_init() {
    // GPIO
    unsigned int r = *GPFSEL1;
    r &= ~((7 << 12) | (7 << 15)); // 清除 pin 14, 15 的設定
    r |= (2 << 12) | (2 << 15);    // 2 代表 Alt5 功能 (Mini UART)
    *GPFSEL1 = r;

    // 關閉 Pull-up/down 以節省電力並確保訊號純淨
    *GPPUD = 0;
    for(int i=0; i<150; i++) asm volatile("nop");
    *GPPUDCLK0 = ((1 << 14) | (1 << 15));
    for(int i=0; i<150; i++) asm volatile("nop");
    *GPPUDCLK0 = 0;
    // 1. 開啟 Mini UART 的電源/時鐘
    *AUX_ENABLES = 1;    
    
    // 2. 暫時關閉中斷與收發功能，確保設定過程不被打擾
    *AUX_MU_CNTL_REG = 0; 
    *AUX_MU_IER_REG = 0;  // 關閉中斷
    
    // 3. 設定資料格式為 8-bit (這是 QEMU 與終端機通訊的標準)
    *AUX_MU_LCR_REG = 3;  
    
    // 4. 設定 Modem 控制為 0 (不使用 RTS/CTS)
    *AUX_MU_MCR_REG = 0;  
    
    // 5. 設定波特率 (Baud Rate)
    // 在 QEMU 中數值不影響速度，但在實體 Rpi3 上公式為:
    // baudrate = system_clock / (8 * (baud_reg + 1))
    *AUX_MU_BAUD_REG = 270; // 對應 115200 鮑率
    
    // 6. 清除 FIFO 緩衝區
    *AUX_MU_IIR_REG = 6;  

    

    // 7. 最後一步：重新開啟收發器
    *AUX_MU_CNTL_REG = 3;
}

void uart_send(unsigned int c) {
    while (!((*AUX_MU_LSR_REG)&0x20)) asm volatile("nop");
    *AUX_MU_IO_REG = c;
}

char uart_get() {
    while (!((*AUX_MU_LSR_REG)&0x1)) asm volatile("nop");
    char c = (char) *AUX_MU_IO_REG;
    return c == '\r' ? '\n' : c;
}

void uart_send_string(char* s) {
    while (*s != '\0') uart_send(*s++);
}