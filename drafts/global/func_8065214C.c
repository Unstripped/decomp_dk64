// func_8065214C (src/global/55B20.c): near miss; regalloc/scheduling stage
typedef struct M55P1_Unk807F6C18 {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0xF];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ u8 pad18[0x4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 pad20[0x48];
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ u8 pad78[0x150];
} M55P1_Unk807F6C18;

typedef struct M55P1_Unk807F70B0 {
    /* 0x000 */ u8 pad0[0x19];
    /* 0x019 */ u8 unk19;
    /* 0x01A */ u8 pad1A[0x2];
} M55P1_Unk807F70B0;

extern M55P1_Unk807F6C18 *D_807F6C18;
extern s32 D_807F6C28;
extern s32 D_807F70AC;
extern M55P1_Unk807F70B0 *D_807F70B0;

void func_8065214C(void) {
    s32 i;

    for (i = 0; i < D_807F6C28; i++) {
        D_807F6C18[i].unk1 = 0;
        D_807F6C18[i].unk2 = 1;
        D_807F6C18[i].unk4 = 0;
    }
    for (i = 0; i < D_807F70AC; i++) {
        D_807F70B0[i].unk19 = 0;
    }
}
