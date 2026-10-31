// textBlitGlyph (src/global/100180.c): from .scratch/Q100/textBlitGlyph_best.c
s32 textBlitGlyph(u8, s32, s32, s16, u8, s8 *, u8);
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
    s32 ret;

    srcRow = (u8 *)arg2 + (arg3 >> 1);
    dst = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    src = (u8 *)arg2;
    dstRow = dst;
    phase = (*(u8 *)arg5 & 1) != 0;
    *(u8 *)arg5 += arg0;
    odd = (arg0 & 1) != 0;
    arg0 = (u32)arg0 >> 1;
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
    ret = phase;
    if (phase != 0) {
        ret = odd;
    }
    return ret + arg1 + arg0;
}
