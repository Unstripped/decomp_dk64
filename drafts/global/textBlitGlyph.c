// textBlitGlyph (src/global/100180.c): stage 5 (parked NON_MATCHING in 100180.c): frame 0x50 and spill slot 0x1C match, 164 vs 161 insns, regs differ (target phase v0, odd v1, src t0, srcRow t1, lead t2, w2 t3, dst s2, dstRow s0, row s3, arg6 s1, j a2; mine dst v0, src v1, odd s0). u8 lead gives the move/andi/move copy; arg0=arg0>>1; w2=arg0 gives a0 copy; dst++; *dst|= (instead of *++dst) removes a temp (shape 33) but shrinks frame to 0x18. Permuter (2x900s) and deadsweep (no globals) did not converge.
s32 textBlitGlyph(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *src;
    u8 *srcRow;
    u8 *dst;
    s32 w2;
    s32 phase;
    s32 odd;
    s16 row;
    s16 j;
    u8 *dstRow;
    u8 lead;
    u8 *p5;

    p5 = (u8 *)arg5;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
    dst = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    src = (u8 *)arg2;
    dstRow = dst;
    phase = (*p5 & 1) != 0;
    *p5 += arg0;
    odd = (arg0 & 1) != 0;
    arg0 = arg0 >> 1;
    w2 = arg0;
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
                    *++dst |= *src & 0xF0;
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
    if (phase != 0) {
        phase = odd;
    }
    return phase + arg1 + arg0;
}
