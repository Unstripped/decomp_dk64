// textBlitGlyph (src/global/100180.c): Text R7: stage 5 count/frame exact (161 insns, frame 0x50, s0-s3), deadsweep full 81 shape 25 (was 103/19; no FAKEs). Re-spelled head: src/srcRow/phase/w2/dstRow/odd/dst/add statement order + forms (srcRow=(u8*)(arg2+(arg3>>1)); w2=arg0>>1; dstRow=(u8*)arg1+arg6*16+arg6*arg4; odd=arg0&1; *(u8*)arg5=*(u8*)arg5+arg0). Now arg6 s1, dstRow s0, dst s2, row s3, lead t2, src t0, srcRow t1, both spills at one slot like target (0x18 vs target 0x1C). Left: entry block only: ucvt(arg0) coloured t3 in target (single andi, srl a0,t3,1; andi t3,a0,0xff; move a0,t3) vs ours andi t6,a0,0xff;move a0,t6 + sra t3; phase andi/sltu/move v0 copy vs target andi t4,t5,1;sltu v0,zero,t4; byte lbu t2 vs t5; ring phase shifted by 3 => loop t6-t9 rotation. Tried: 18144 statement orders (exhaustive) x forms, random 9000 + 7000 (dstRow first), 3 hill-climbs incl. types/decl order/dead tests (annealed), arg0>>=1 in place (frame collapses), no arg0=w2 (107), u8/u16 w2 (count +5), u8 *arg5 (same).
s32 textBlitGlyph(u8, s32, s32, s16, u8, s8 *, u8);

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
