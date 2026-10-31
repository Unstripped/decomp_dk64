// textBlitGlyph (src/global/100180.c): stage 5 (R3d wave 3): unchanged C, 160 vs 161 insns, frame 0x50 OK, harness text-diff 119 (old parked block was 269/164 insns: parked block in 100180.c replaced by this body). Left: target's odd/phase and-temps are SEPARATE coloured expression cands (andi t2,t3,1 / andi t4,t5,1 then sltu v1/v0,zero,tmp) with cvt(arg0)=t3 cand used 3x (andi t2,t3,1; srl a0,t3,1; addu t9,t5,t3) and w2=arg0=narrowed t3 shared (blez t3 / slt a2,t3 / or a0,t3,zero); mine ANDs into the var reg then sltu t9 + move, arg0 is a var with entry def 'andi t6,a0,0xff; move a0,t6'. Target lead idiom 'move t2,a3; andi t6,t2,1; move t2,t6' (lead=arg3; lead&=1 did not reproduce). This pass no gain: phase/odd as !!x, x?1:0, two-step, 0<x; w2/arg0 as arg0>>=1;w2=arg0 / chained / u8 w2 (size 161 but frame 72); dead if(x==0){} sweep of every local/param at every statement (213 equal, none better).

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
