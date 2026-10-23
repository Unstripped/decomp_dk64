// func_80658DAC (src/global/55B20.c): stage 6: loop-end reloc as func_80658BD0 plus lui t7/lui v0 and sra delay-slot swaps
typedef struct M55P6Entry {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s16 unk4;
    /* 0x006 */ s16 unk6;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ u8 padA[0x2];
    /* 0x00C */ s32 unkC;
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 unk11;
    /* 0x012 */ u8 pad12[0x2];
} M55P6Entry;

extern s32 D_807F7290;
extern u8 D_807F72A1;
extern s32 D_807F72A4;
extern u8 D_807F72B5;
extern M55P6Entry D_807F72B8[];

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
