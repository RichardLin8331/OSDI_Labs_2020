#ifndef R_MAILBOX_H
#define R_MAILBOX_H

#include "gpio.h"

extern volatile unsigned int mbox[36];



#define VIDEOCORE_MBOX  (MEM_BASE+0x0000B880)
#define MBOX_READ       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x0))
#define MBOX_POLL       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SENDER     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x14))
#define MBOX_STATUS     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x18))
#define MBOX_CONFIG     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRITE      ((volatile unsigned int*)(VIDEOCORE_MBOX+0x20))

#define MBOX_REQUEST    0
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000


#define MBOX_CH_PROP    8
/* tags */
#define MBOX_TAG_REQUEST_CODE 0
#define MBOX_TAG_GETBOARDREVISION  0x10002
#define MBOX_TAG_GETSERIAL      0x10004
#define MBOX_TAG_GETVC          0x10006
#define MBOX_TAG_SETCLKRATE     0x38002
#define MBOX_TAG_LAST           0

int mbox_call(unsigned char ch);

#endif