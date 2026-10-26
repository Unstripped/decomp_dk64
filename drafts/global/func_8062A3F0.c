// func_8062A3F0 (src/global/2DE90.c): stage 3: same size (226 insns), structure matches (3 row loops, IV pointers in loop 2 via half var + bound expr D_80747B28/2), but frame 0x130 vs 0x128 (half spilled to 0x128; target has 0x20-byte hole between arrays and row at 0x120) and s-reg allocation differs (target: s0=D_80747B30 s1=src s2=dst s3=lut s4=W-n/2 s5=n/2 s6=&D_80747B28 s7=&r s8=&g ra=n).
extern s32 D_80747B28;
extern u8 *D_80747B2C;
extern s32 D_80747B38;
extern u16 *D_807F5D80;
extern s32 D_80747B30;
extern s32 D_80747B34;
extern s32 D_80747B3C;
void heapFree(void *);

void func_8062A3F0(void) {
    s32 row;
    s32 half;
    u8 r[0x34];
    u8 g[0x34];
    u8 b[0x34];
    u16 *src;
    u16 *dst;
    u8 *lut;
    s32 sumR;
    s32 sumG;
    s32 sumB;
    s32 i;
    s32 idx;
    u32 pix;
    u8 vr;
    u8 vg;
    u8 vb;

    dst = D_807F5D80;
    src = dst;
    lut = D_80747B2C;
    if ((D_80747B2C == 0) || (D_80747B3C < D_80747B38)) {
        if (D_80747B2C != 0) {
            heapFree(D_80747B2C);
            D_80747B2C = 0;
        }
    } else {
        for (row = 0; row < D_80747B34; row++) {
            sumR = 0;
            sumG = 0;
            sumB = 0;
            for (i = 0; i < D_80747B28; i++) {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
            }
            half = D_80747B28 / 2;
            for (i = 0; i < D_80747B28 / 2; i++) {
                pix = *src;
                vr = (pix >> 11) & 0x1F;
                r[half + i] = vr;
                sumR += vr;
                vg = (pix >> 6) & 0x1F;
                vb = (pix >> 1) & 0x1F;
                src++;
                g[half + i] = vg;
                sumG += vg;
                b[half + i] = vb;
                sumB += vb;
            }
            idx = 0;
            for (i = 0; i < D_80747B30 - D_80747B28 / 2; i++) {
                pix = *src++;
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                vr = (pix >> 11) & 0x1F;
                sumR = sumR - r[idx] + vr;
                vg = (pix >> 6) & 0x1F;
                sumG = sumG - g[idx];
                {
                    u8 ob = b[idx];
                    vb = (pix >> 1) & 0x1F;
                    r[idx] = vr;
                    g[idx] = vg;
                    b[idx] = vb;
                    sumG += vg;
                    sumB = sumB - ob + vb;
                }
                idx++;
                *dst = (lut[sumR] << 11) | 1 | (lut[sumB] << 1) | (lut[sumG] << 6);
                dst++;
            }
            for (i = D_80747B30 - D_80747B28 / 2; i < D_80747B30; i++) {
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                {
                    u8 orr = r[idx];
                    u8 og = g[idx];
                    u8 ob = b[idx];
                    sumR -= orr;
                    r[idx] = 0;
                    g[idx] = 0;
                    b[idx] = 0;
                    sumG -= og;
                    sumB -= ob;
                }
                idx++;
                *dst = (lut[sumR] << 11) | 1 | (lut[sumB] << 1) | (lut[sumG] << 6);
                dst++;
            }
        }
        D_80747B38++;
    }
}
