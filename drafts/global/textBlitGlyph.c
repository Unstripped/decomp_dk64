// textBlitGlyph (src/global/100180.c): stage 5: count 161 + frame 80 exact, entire diff regalloc/entry-schedule (deadsweep full=79 shape=23 vs stored 81/25). Lever: for (row = 0; row < 0x10; row++) header (not do-while) fixes tail order slti,subu,move,bnez. Open: expected keeps ucvt(arg0)=t3 + *arg5 load t5 as block-local cands and ring t2/t4 for the andi of odd/phase (sltu v0/v1 direct); ours colours cands t2/t4/t5 so the ring falls to v0 (andi v0; sltu t7; move v0,t7) and keeps entry narrowing andi t6,a0,0xff; move a0,t6. Tried: arg0 >>= 1 in place (srl+andi shape right but loses the two sw s1/s2 spill-temp stores and frame), old-value local, w2 types, K&R, formal types, 9-word decl order/type climbs, order/alt annealing (best 78 only with frame 88)
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
    srcRow = (u8 *)(arg2 + (arg3 >> 1));
    phase = (*(u8 *)arg5 & 1) != 0;
    w2 = arg0 >> 1;
    dstRow = (u8 *)arg1 + arg6 * 16 + arg6 * arg4;
    odd = arg0 & 1;
    dst = dstRow;
    *(u8 *)arg5 = *(u8 *)arg5 + arg0;
    arg0 = w2;
    for (row = 0; row < 0x10; row++) {
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
        dstRow -= arg6;
        src = srcRow;
        dst = dstRow;
    }
    ret = phase;
    if (phase != 0) {
        ret = odd;
    }
    return ret + arg1 + arg0;
}
