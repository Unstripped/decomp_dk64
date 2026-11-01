// screenBlurApply (src/global/2DE90.c): screenBlurApply (src/global/2DE90.c): stage 5, 22 diff lines, shape=0, exact matching function length (225 insns, frame 0x128). Single remaining cause: loop 3 final 'or t7,t6,t8' operands emitted swapped (t8 vs t6) by IDO ugen/as1, which swaps t6/t8 scratch register names throughout loop 4.
void screenBlurApply(void) {
    u16 *src;
    s32 row;
    u16 *dst;
    u8 *lut;
    s32 sumR;
    s32 sumG;
    s32 sumB;
    s32 i;
    s32 idx;
    u32 pix;
    u8 r[0x34];
    u8 g[0x34];
    u8 b[0x34];
    u8 vr;
    u8 vg;
    u8 vb;

    src = D_807F5D80;
    dst = D_807F5D80;
    lut = D_80747B2C;
    if ((D_80747B2C == 0) || (D_80747B3C < D_80747B38)) {
        if (D_80747B2C != 0) {
            heapFree(D_80747B2C);
            D_80747B2C = 0;
        }
    } else {
        for (row = 0; row < D_80747B34; row++) {
            sumR = 0;
            sumB = 0;
            sumG = 0;
            for (i = 0; i < D_80747B28; i++) {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
            }
            idx = D_80747B28 / 2;
            for (i = 0; i < D_80747B28 / 2; i++) {
                pix = *src;
                vr = (pix >> 11) & 0x1F;
                r[idx] = vr;
                sumR += vr;
                vg = (pix >> 6) & 0x1F;
                vb = (pix >> 1) & 0x1F;
                idx++;
                src++;
                g[idx - 1] = vg;
                sumG += vg;
                b[idx - 1] = vb;
                sumB += vb;
            }
            idx = 0;
            for (i = 0; i < D_80747B30 - D_80747B28 / 2; i++) {
                pix = *src++;
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                vr = (pix >> 11) & 0x1F;
                sumR -= r[idx];
                sumR += vr;
                r[idx] = vr;
                vg = (pix >> 6) & 0x1F;
                sumG -= g[idx];
                g[idx] = vg;
                sumG += vg;
                vb = (pix >> 1) & 0x1F;
                sumB -= b[idx];
                b[idx] = vb;
                idx++;
                sumB += vb;
                *dst = (lut[sumR] << 11) | 1 | (lut[sumB] << 1) | ((u32)lut[sumG] << 6);
                dst++;
            }
            for (i = D_80747B30 - D_80747B28 / 2; i < D_80747B30; i++) {
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                sumR -= r[idx];
                sumG -= g[idx];
                sumB -= b[idx];
                r[idx] = 0;
                g[idx] = 0;
                b[idx] = 0;
                idx++;
                *dst = (lut[sumR] << 11) | 1 | (lut[sumB] << 1) | ((u32)lut[sumG] << 6);
                dst++;
            }
        }
        D_80747B38++;
    }
}
