// textBlitGlyph (src/global/100180.c): from .scratch/W2Ring/textBlitGlyph_best.c
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
