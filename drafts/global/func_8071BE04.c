// func_8071BE04 (src/global/11BC10.c): stage 3: compiled matrix/wave starter; state view has unresolved overlapping offsets 0x4/0x8 versus s16@0x10 and ptr@0x14, and frame is 0xC0 vs 0xB0
typedef struct { u8 unk0; u8 pad1; s16 unk2; f32 unk4; f32 unk8; } Ub6WaveData;
typedef struct { u8 pad0[4]; f32 unk4; f32 unk8; s16 unk10; u8 pad12[2]; Ub6WaveData *unk14; } Ub6WaveState;
typedef struct { u8 pad0[0x340]; f32 unk340; f32 unk344; f32 unk348; u8 pad34C[0x10]; Ub6WaveState *unk35C; f32 unk360; f32 unk364; u8 pad368[5]; s8 unk36D; } Ub6WaveActorView;

void func_8071BE04(Ub6WaveActorView *arg0, s8 *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];
    Ub6WaveState *sp28;
    Ub6WaveData *sp24;
    f32 sp20;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f64 temp_ft4;
    sp28 = arg0->unk35C;
    sp24 = sp28->unk14;
    temp_fv0 = func_80612794(sp28->unk10);
    arg0->unk36D = (s8)(u32)((f32)sp24->unk0 * temp_fv0);
    var_fa0 = arg0->unk364;
    temp_fv1 = 1.0f - temp_fv0;
    if (sp24->unk4 != 0.0f) {
        sp20 = temp_fv1;
        temp_ft4 = ((f64)func_80612794(sp24->unk2) * 0.15) + 0.85;
        sp24->unk2 = (sp24->unk2 + 0xAA) & 0xFFF;
        var_fa0 = (f32)(temp_ft4 * (f64)arg0->unk364);
    }
    sp20 = temp_fv1;
    guScaleF(sp70, arg0->unk360, var_fa0, 0.0f);
    guTranslateF(sp30, arg0->unk340 + (sp28->unk4 * sp20), arg0->unk344 + (sp28->unk8 * sp20), arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 3;
}
