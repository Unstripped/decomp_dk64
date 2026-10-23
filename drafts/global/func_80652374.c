// func_80652374 (src/global/55B20.c): near miss; regalloc/scheduling stage
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

void func_80652374(M55P1_Unk80652374 *arg0) {
    s32 *sp40;
    s32 temp_v1;

    arg0->unk20 = func_806531B8(arg0->unk4, arg0->unk8, *(s32 *)&arg0->unkC, arg0->unk20);
    temp_v1 = func_80630324(arg0->unk24, arg0->unk0) & 0xFF;
    if (arg0->unk24 == 0) {
        *(s16 *)(arg0->unk0 + 0x12C) = arg0->unk20;
    }
    switch (temp_v1) {
    case 0:
        sp40 = (s32 *)((u8 *)D_807F6C18 + arg0->unk20 * 0x1C8 + 0x14);
        break;
    case 1:
        sp40 = (s32 *)((u8 *)D_807F6C18 + arg0->unk20 * 0x1C8 + 0x1C);
        break;
    }
    *sp40 = func_806303C4(*sp40, arg0->unk24, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC, arg0->unk1C, arg0->unk1E, arg0->unk22, arg0->unk20, 0);
}
