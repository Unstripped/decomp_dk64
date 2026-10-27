// func_8062A3F0 (src/global/2DE90.c): stage 5: frame 0x128, size 225 insns, stack layout (r 0xCC,g 0x98,b 0x64,row 0x120) and all uopt s-reg/temps allocation match. Remaining ~24 diff lines: (1) final 'or t7,t6,t8' operands swapped in loop3/loop4 output expr (needs (u32) on G term to get lut order right; cast on partial gives same), (2) loop3 'andi t9,t8,0xff' (vg u8 conv) sits before 'move a3,t8' vs after 'sb t8,0(v1)', (3) scratch t6/t8 naming in loop4 loads. Key tricks: idx reused as running index in loop2 (idx=n/2; r[idx]..idx++; src++ after idx++), dst/src loaded 'src=G; dst=G;', zero loop r,g,b separate stmts, arrays declared r,g,b, 'u32' cast on lut[sumG]<<6.
void func_8062A3F0(void) {
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
                sumG += vg;
                vb = (pix >> 1) & 0x1F;
                sumB -= b[idx];
                g[idx] = vg;
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
