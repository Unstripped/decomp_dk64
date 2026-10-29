// func_80713DFC (src/global/117190.c): Stage 4: behavior recovered; target has 0x40 frame and keeps the return value in a0, while the draft emits a 0x20 frame and v1 result.
extern s16 D_80744490;
extern s32 D_80755348;
s32 renderTimerMinutesSecondsHUD(void *, f32, f32, s32);
typedef struct R117jDisplayListWord {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} R117jDisplayListWord;

s32 func_80713DFC(s32 arg0) {
    f32 sp1C;
    R117jDisplayListWord sp20[2];
    R117jDisplayListWord *temp_v0;

    if ((func_80712628() != 0) && !(D_807FBB60 & 3)) {
        sp1C = (f32) D_80744490 * 0.5f;
        temp_v0 = func_807132DC();
        temp_v0->unk0 = 0xFC119623;
        temp_v0->unk4 = 0xFF2FFFFF;
        temp_v0->unkC = -1;
        temp_v0->unk8 = 0xFA000000;
        arg0 = renderTimerMinutesSecondsHUD(temp_v0 + 1, sp1C, 214.0f, D_80755348);
    }
    return arg0;
}
