// textBlitGlyph (src/global/100180.c): textBlitGlyph stage 5: frame 0x50 OK, 161 vs 162 insns, deadsweep full=74 shape=40 (was 83/40). New this pass: pre-loop statement order src, srcRow, phase, *p5+=, odd, w2, dstRow, dst, arg0=w2, row=0 (exhaustive 504-order search, dist 139->119) puts srcRow=t1, row=s3, dstRow/dst/arg6 s-regs like target. Left: target's odd/phase and-temps (andi t2,t3,1 / andi t4,t5,1) are coloured candidates (t2/t4) with cvt(arg0)=t3, cvt(*p5)=t5 and 'sb *p5' last; mine uses ugen temps + extra 'move a0,cvt'; lead in target is move t2,a3/andi t6,t2,1/move t2,t6 (lead=arg3;lead&=1 and s8/u8/s16 lead types did not reproduce it); dead-use forms on (arg0&1),(*p5&1) did nothing. deadsweep round1 found only 74->72 with a FAKE.
s32 textBlitGlyph(u8, s32, s32, s16, u8, s8 *, u8);

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
