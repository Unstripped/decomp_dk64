// func_8066C610 (src/global/70FD0.c): Closest diff: logic 100% matched, frame 0xF0 matched, callee-saved float f20 used for 0.0f CSE across guRotateF calls
typedef struct M70A_Unk24 {
    u8 pad0[0x60];
    s32 unk60;
} M70A_Unk24;
typedef struct M70A_Struct_C610 {
    u8 pad0[0x24];
    M70A_Unk24 *unk24;
    u8 pad28[0x50];
    s32 *unk78;
    u8 pad7C[0x14];
} M70A_Struct_C610;

extern u8 D_807444FC;
extern M70A_Struct_C610 *D_807F6000;

void modelSlotGetTransformVectors();
void func_8066C7F4();

void func_8066C610(s16 arg0, s8 arg1, f32 (*arg2)[4]) {
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    s32 spD0;
    float sp8C[4][4];
    float sp4C[4][4];
    s32 sp48;
    void *sp44;
    M70A_Struct_C610 *entry;

    entry = &D_807F6000[arg0];
    if (entry->unk78 != NULL) {
        sp48 = entry->unk78[D_807444FC];
    } else {
        sp48 = 0;
    }
    sp44 = (u8 *)entry->unk24 + entry->unk24->unk60;
    modelSlotGetTransformVectors(arg0, &spEC, &spE8, &spE4, &spE0, &spDC, &spD8, &spD4, &spD0, 0);
    guScaleF(sp8C, spD4, spD4, spD4);
    guRotateF(sp4C, spE0, 1.0f, 0, 0);
    guMtxCatF(sp8C, sp4C, sp8C);
    guRotateF(sp4C, spDC, 0, 1.0f, 0);
    guMtxCatF(sp8C, sp4C, sp8C);
    guRotateF(sp4C, spD8, 0, 0, 1.0f);
    guMtxCatF(sp8C, sp4C, sp8C);
    guTranslateF(sp4C, spEC, spE8, spE4);
    if (arg1 != -1) {
        guMtxCatF(sp8C, sp4C, sp8C);
        func_8066C7F4((u8 *)sp44 + (arg1 << 5), sp48, arg2);
        guMtxCatF(arg2, sp8C, arg2);
        return;
    }
    guMtxCatF(sp8C, sp4C, arg2);
}
