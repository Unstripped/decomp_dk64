// func_80658DAC (src/global/55B20.c): matched: two ifs must share one source line (IDO scheduling); otherwise lui %hi(D_807F72A4) is hoisted after %hi(D_807F72A1)
typedef struct M55P7Slot {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u8 pad4[0xD];
    /* 0x011 */ u8 unk11;
} M55P7Slot;

extern u8 D_807F72A1;
extern s32 D_807F72A4;
extern u8 D_807F72B5;
extern M55P7Slot D_807F72B8[];

u8 func_80658DAC(s32 arg0) {
    s32 i;

    if (arg0 == D_807F7290) { return D_807F72A1; } if (arg0 == D_807F72A4) { return D_807F72B5; }
    for (i = 0; i < 8; i++) {
        if (arg0 == D_807F72B8[i].unk0) {
            return D_807F72B8[i].unk11;
        }
    }
    return 0;
}
