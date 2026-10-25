// func_8070B05C (src/global/10E1D0.c): stage 2: mask/fill behavior recovered; source uses 4-way unrolled six-halfword loops, draft has nested loops
typedef struct R1F10E1D0bMask {
    u16 data[24];
} R1F10E1D0bMask;

extern R1F10E1D0bMask D_80755074;
extern s32 D_80755068;

void func_8070B05C(u16 *arg0) {
    R1F10E1D0bMask temp = D_80755074;
    s32 i;
    s32 j;
    s32 count = ((D_80755068 - 5) * 0xF0) / 0x50;
    u16 *pixels = arg0 + 0x9D;

    for (i = 0; i < count; i++) {
        for (j = 0; j < 6; j++) {
            pixels[j] &= temp.data[((i & 3) * 6) + j];
        }
        pixels += 0x140;
    }
    for (; i < 0xF0; i++) {
        for (j = 0; j < 6; j++) {
            pixels[j] |= 1;
        }
        pixels += 0x140;
    }
}
