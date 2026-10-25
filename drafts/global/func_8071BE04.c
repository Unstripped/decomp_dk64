// func_8071BE04 (src/global/11BC10.c): stage 3: compiled; frame now matches target at 0xB0 and the state view confirms s16@0x10 plus data pointer@0x14, but register allocation retains s1 where target spills state/data locals and the scale-update order remains divergent.
typedef struct { u8 unk0; u8 pad1; s16 unk2; u8 unk4; } Ub6bWaveData;
typedef struct { u8 pad0[4]; f32 unk4; f32 unk8; u8 padC[4]; s16 unk10; u8 pad12[2]; Ub6bWaveData *unk14; } Ub6bWaveState;
typedef struct { u8 pad0[0x340]; f32 unk340; f32 unk344; f32 unk348; u8 pad34C[0x10]; Ub6bWaveState *unk35C; f32 unk360; f32 unk364; u8 pad368[5]; s8 unk36D; } Ub6bWaveActorView;
void func_8071BE04(Ub6bWaveActorView *arg0, s8 *arg1) {
    f32 sp70[4][4]; f32 sp30[4][4]; Ub6bWaveState *sp28; Ub6bWaveData *sp24; f32 sp20;
    sp28 = arg0->unk35C;
    sp24 = sp28->unk14;
    sp20 = func_80612794(sp28->unk10);
    arg0->unk36D = (s8)(u32)((f32)sp24->unk0 * sp20);
    sp20 = 1.0f - sp20;
    if (sp24->unk4 != 0) { sp24->unk2 = (sp24->unk2 + 0xAA) & 0xFFF; guScaleF(sp70, arg0->unk360, (f32)((((f64)func_80612794(sp24->unk2) * 0.15) + 0.85) * (f64)arg0->unk364), 0.0f); }
    else guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guTranslateF(sp30, arg0->unk340 + (sp28->unk4 * sp20), arg0->unk344 + (sp28->unk8 * sp20), arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 3;
}
