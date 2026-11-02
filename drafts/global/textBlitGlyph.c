// textBlitGlyph (src/global/100180.c): Text U6: stage 5 NON_MATCHING park in copy: count/frame EXACT (161 insns, frame 0x50, s0-s3), deadsweep full=103 shape=19 (was 74/40 at 160 insns). Left: w2 coloured s1 (s-reg) where target keeps it in t3 and dstRow in s0 (arg6 s1, dst s2); target has NO entry narrowing 'andi t6,a0,0xff; move a0,t6' (cvt of arg0 shared t3), lead/odd t-regs rotated. Levers: u8 lead (+3 insns idiom), odd=(u8)(arg0&1)!=0, ret via w2, decl-order/type/statement-order annealing (6 runs). Not found: C that removes the entry narrowing while keeping the home store (needs raw use of incoming arg0: 's16 aw = arg0' copy does it but noW+aw gives full 120+).
s32 textBlitGlyph(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *srcRow;
    u8 *dst;
    u8 lead;
    s16 j;
    s16 row;
    u8 *src;
    s32 phase;
    s32 w2;
    u8 *dstRow;
    s32 ret;
    s32 odd;
    src = (u8 *)arg2;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
    dstRow = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    phase = (*(u8 *)arg5 & 1) != 0;
    *(u8 *)arg5 += arg0;
    w2 = (u32)arg0 >> 1;
    dst = dstRow;
    odd = (u8)(arg0 & 1) != 0; // FAKE: narrow-local idiom for odd
    arg0 = w2;
    row = 0;
    do {
        j = 0;
        if (w2 > 0) {
            lead = arg3 & 1;
            do {
                if (lead && phase == 0) {
                    *dst |= *src++ << 4;
                    *dst++ |= (*src & 0xF0) >> 4;
                } else if (lead && phase != 0) {
                    *dst |= *src++ & 0xF;
                    dst++;
                    *dst |= *src & 0xF0;
                } else if (lead == 0 && phase != 0) {
                    *dst++ |= (*src & 0xF0) >> 4;
                    *dst |= *src++ << 4;
                } else {
                    *dst++ |= *src++;
                }
                j++;
            } while (j < w2);
        }
        srcRow += 0x100;
        if (odd != 0) {
            lead = arg3 & 1;
            if (lead && phase == 0) {
                *dst |= *src << 4;
            } else if (lead && phase != 0) {
                *dst |= *src << 4;
            } else if (lead == 0 && phase != 0) {
                *dst |= (*src & 0xF0) >> 4;
            } else {
                *dst |= *src;
            }
        }
        row++;
        dstRow -= arg6;
        src = srcRow;
        dst = dstRow;
    } while (row < 0x10);
    ret = phase;
    if (phase != 0) {
        ret = odd;
    }
    return ret + arg1 + arg0;
}
