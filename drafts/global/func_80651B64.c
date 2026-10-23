// func_80651B64 (src/global/55B20.c): near miss; regalloc/scheduling stage
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

extern M55P1_Unk807F6C18 *D_807F6C18;

s32 func_80651B64(s16 arg0) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = (arg0 + 1) != 0;
    if (var_v1 != 0) {
        var_v0 = 0;
        if (D_807F6C18[arg0].unk3 != 0) {
            var_v0 = 1;
        }
        var_v1 = var_v0 != 0;
    }
    return var_v1 & 0xFF;
}
