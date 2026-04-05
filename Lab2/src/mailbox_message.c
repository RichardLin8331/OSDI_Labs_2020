#include "include/string.h"
#include "include/mailbox.h"

void get_board_revision(char* bv) {
    if (get_length(bv) !=10 ) return;

    mbox[0] = 7 * 4; // buffer size in bytes
    mbox[1] = MBOX_REQUEST;
    // tags begin
    mbox[2] = MBOX_TAG_GETBOARDREVISION; // tag identifier
    mbox[3] = 4; // maximum of request and response value buffer's length.
    mbox[4] = MBOX_TAG_REQUEST_CODE;
    mbox[5] = 0; // value buffer
    // tags end
    mbox[6] = MBOX_TAG_LAST;

    mbox_call(MBOX_CH_PROP); 
    unsigned int bv_int = mbox[5];
    htos(bv_int, bv);
}

void get_vc_base(char* vc_base) {
    if (get_length(vc_base) !=10 ) return;
    mbox[0] = 8 * 4; // buffer size in bytes
    mbox[1] = MBOX_REQUEST;
    // tags begin
    mbox[2] = MBOX_TAG_GETVC; // tag identifier
    mbox[3] = 8; // maximum of request and response value buffer's length.
    mbox[4] = MBOX_TAG_REQUEST_CODE;
    mbox[5] = 0; // value buffer
    mbox[6] = 0; // value buffer
    // tags end
    mbox[7] = MBOX_TAG_LAST;

    mbox_call(MBOX_CH_PROP); 
    unsigned int vc_base_int = mbox[5];
    htos(vc_base_int, vc_base);
}