// func_80713DFC (src/global/117190.c): Stage 4: behavior and draw commands recovered; frame, result register, and immediate scheduling differ.
extern s16 D_80744490;
extern s32 D_80755348;
extern s32 D_807FBB60;
s32 func_8068E7B4(void *, f32, f32, s32);
typedef struct R117d2DisplayListWord { s32 unk0; s32 unk4; s32 unk8; s32 unkC; } R117d2DisplayListWord;

s32 func_80713DFC(s32 arg0) {
    f32 sp1C;
    s32 var_a0;
    R117d2DisplayListWord *temp_v0;
    var_a0 = arg0;
    if ((func_80712628() != 0) && !(D_807FBB60 & 3)) {
        sp1C = (f32)D_80744490 * 0.5f;
        temp_v0 = func_807132DC(var_a0);
        temp_v0->unk0 = 0xFC119623;
        temp_v0->unk4 = 0xFF2FFFFF;
        temp_v0->unkC = -1;
        temp_v0->unk8 = 0xFA000000;
        var_a0 = func_8068E7B4(temp_v0 + 1, sp1C, 214.0f, D_80755348);
    }
    return var_a0;
}
