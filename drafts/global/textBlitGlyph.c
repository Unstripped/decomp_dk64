// textBlitGlyph (src/global/100180.c): W3Fp: unchanged park, stage 5 count/frame exact (161 insns, frame 0x50, s0-s3), deadsweep full 103 shape 19. Root cause found (uopt -l 6): unconstrained candidates are coloured in INDEX (first-appearance) order; ours colours dstRow t2 (ordinal 9) before arg6 s0, then phantom ucvt(arg6)/cvt candidates take t3,t4,t5, w2 s1; target has no ucvt(arg6) candidate (all arg6 uses raw s1), lead t2 + cvt/w2 t3 before dstRow, so dstRow s0, arg6 s1, dst s2, row s3. Tried W3Fp: K&R definition (same 103), arg0 >>= 1 / arg0 = arg0 >> 1 / (u32) / (s32) / /2 without w2 (frame collapses 80 -> 24, 150+), u8/s16/u32 w2 and other local widths, local copies of every formal subset (copy-propagated, +2), 2 annealing runs x 7000 evals on statement order of the 10 head statements + declaration order of the 11 locals (no gain), 2 more on dead tests + local widths (no gain).
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
