// func_8070B05C (src/global/10E1D0.c): compilable flat six-store loop reconstruction; unroll and frame remain
typedef struct R1F10E1D0bMask {
    u16 data[24];
} R1F10E1D0bMask;

extern R1F10E1D0bMask D_80755074;
extern s32 D_80755068;

void func_8070B05C(u16 *arg0) {
    R1F10E1D0bMask temp = D_80755074;
    s32 i;
    s32 count = ((D_80755068 - 5) * 0xF0) / 0x50;
    u16 *pixels = arg0 + 0x9D;

    for (i = 0; i < count; i++) {
        pixels[0] &= temp.data[(i & 3) * 6];
        pixels[1] &= temp.data[(i & 3) * 6 + 1];
        pixels[2] &= temp.data[(i & 3) * 6 + 2];
        pixels[3] &= temp.data[(i & 3) * 6 + 3];
        pixels[4] &= temp.data[(i & 3) * 6 + 4];
        pixels[5] &= temp.data[(i & 3) * 6 + 5];
        pixels += 0x140;
    }
    for (; i < 0xF0; i++) {
        pixels[0] |= 1;
        pixels[1] |= 1;
        pixels[2] |= 1;
        pixels[3] |= 1;
        pixels[4] |= 1;
        pixels[5] |= 1;
        pixels += 0x140;
    }
}
