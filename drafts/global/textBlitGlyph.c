// textBlitGlyph (src/global/100180.c): UNPARKED 2026-11-02: park was 160 insns vs target 161 (count-inexact parks stay drafts); Text R5: stage 5, ANSI park unchanged (deadsweep full=74 shape=40, 160 vs 161 insns, frame 0x50). NEW levers found (not yet a win): (1) 'u8 lead' (instead of s32) reproduces the target idiom 'move t2,a3; andi t6,t2,1; move t2,t6' in both lead sites; (2) in-place narrowing 'andi t6,a0,0xff; move a0,t6' at entry comes from the RAW use of arg0 in '(u32)arg0 >> 1' (uopt cand list: ushr{arg0} raw vs ucvt{arg0} for '+' and '&'); with a K&R definition 's32 arg0' + '(u8)arg0' at every use (and head prototype 's32 textBlitGlyph();') the cvt cand 'andi t3,a0,0xff' is shared by add/and/shr exactly like the target, 161 insns, but then there is no 'sw a0,80(sp)' home store and prologue order/regs differ (full=88..111 with u8 lead + statement-order hill-climb, 40k iters, worse than 74 so not parked). Tried and no help on ANSI base: w2 spellings (cast/and/+0/|0/etc: cfe folds them), copy local a0v/half (frame 88), dead-test sweeps (only 'if (arg6 == 0) {}' -2), statement-order+spelling hill-climb (84->82), lead type/form grid, local merge/remove sweep.
s32 textBlitGlyph(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *src;
    s32 lead;
    u8 *dst;
    s32 w2;
    s16 row;
    s32 odd;
    s16 j;
    s32 phase;
    u8 *dstRow;
    u8 *srcRow;
    s32 ret;
    src = (u8 *)arg2;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
    phase = (*(u8 *)arg5 & 1) != 0;
    *(u8 *)arg5 += arg0;
    odd = (arg0 & 1) != 0;
    w2 = (u32)arg0 >> 1;
    dstRow = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    dst = dstRow;
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
