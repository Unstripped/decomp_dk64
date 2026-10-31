// textBlitGlyph (src/global/100180.c): stage 5 (parked NON_MATCHING): frame 0x50 + spill slot 0x1C match, 160 vs 161 insns, deadsweep full=83 shape=40 (old park 159/36). Loop body (all 4 cases, delay slots) identical to target; phase v0 odd v1 src t0 srcRow t1 match. Found: ret var (ret=phase; if(phase) ret=odd) gives the beqz/move/move tail; *(u8*)arg5 directly (no p5 local); dst++; *dst|= (no temp); (u32)arg0>>1 gives srl; statement order search (hill-climb in harness) put phase/odd first. Remaining: prologue order (target sb *p5 last, no 'move a0,cvt' copy), s32 lead emits 1-insn andi vs target's u8 move/andi/move, t2/t3 taken by cvt isops 631/637 (target lead t2, w2 t3), row/srcRow regs. Index-order model: unconstrained candidates colour in first-reference order, constrained by adjsave.
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
    row = 0;
    phase = (*(u8 *)arg5 & 1) != 0;
    odd = (arg0 & 1) != 0;
    *(u8 *)arg5 += arg0;
    dstRow = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    w2 = (u32)arg0 >> 1;
    dst = dstRow;
    arg0 = w2;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
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
