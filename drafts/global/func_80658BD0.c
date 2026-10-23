// func_80658BD0 (src/global/55B20.c): stage 6, NOT reloc-only (verified by linking): besides the D_807F72B8+0xa0 vs D_807F7358 reloc, the D_807F72B4 sb is scheduled before the two loop-pointer addiu (target: after them)
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

extern u8 D_807F72A0;
extern u8 D_807F72B4;
extern M55P6Entry D_807F72B8[];
extern s16 D_807F7358;

void func_80658BD0(void) {
    s32 i;

    D_807F72A0 = 0;
    D_807F72B4 = 0;
    for (i = 0; i < 8; i++) {
        D_807F72B8[i].unk10 = 0;
    }
}
