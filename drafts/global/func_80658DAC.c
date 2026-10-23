// func_80658DAC (src/global/55B20.c): stage 6: text identical to target except 2 swapped lui (D_807F72A4 before D_807F72A1) and loop-end reloc %lo(D_807F72B8+0xa0) vs %lo(D_807F7358); counted 8-slot loop is the exact idiom (4x unrolled, 2 iterations); pointer/nested forms produce extra move+early increment
typedef struct M55P7Slot {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u8 pad4[0xD];
    /* 0x011 */ u8 unk11;
} M55P7Slot;

extern s32 D_807F7290;
extern u8 D_807F72A1;
extern s32 D_807F72A4;
extern u8 D_807F72B5;
extern M55P7Slot D_807F72B8[];

u8 func_80658DAC(s32 arg0) {
    s32 i;

    if (arg0 == D_807F7290) {
        return D_807F72A1;
    }
    if (arg0 == D_807F72A4) {
        return D_807F72B5;
    }
    for (i = 0; i < 8; i++) {
        if (arg0 == D_807F72B8[i].unk0) {
            return D_807F72B8[i].unk11;
        }
    }
    return 0;
}
