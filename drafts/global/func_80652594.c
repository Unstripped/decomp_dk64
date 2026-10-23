// func_80652594 (src/global/55B20.c): near miss; regalloc/scheduling stage
typedef struct M55P1_Unk807F6C18 {
    u8 unk0; u8 unk1; u8 unk2; u8 unk3; u8 unk4; u8 pad5[0xF];
    s32 unk14; u8 pad18[0x4]; s32 unk1C; u8 pad20[0x48];
    s32 unk68; s32 unk6C; s32 unk70; s32 unk74; u8 pad78[0x150];
} M55P1_Unk807F6C18;

extern u8 D_807F7078[];
extern s32 D_807F6C28;
extern M55P1_Unk807F6C18 *D_807F6C18;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;
extern s32 D_807F70AC;

u8 func_80652594(s32 arg0, s16 *arg1, u8 arg2) {
    s16 i;
    u8 flag;

    flag = 0;
    for (i = 0; i < D_807F6C28 && (!flag || arg2); i++) {
        D_807F6C18[i].unk14 = func_80630588(D_807F6C18[i].unk14, arg0, 0, &flag);
        if (flag) {
            *arg1 = i;
        }
        if (!flag || arg2) {
            D_807F6C18[i].unk1C = func_80630588(D_807F6C18[i].unk1C, arg0, 0, &flag);
            if (flag) {
                *arg1 = i;
            }
        }
    }
    return flag;
}
