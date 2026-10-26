// func_8073BB10 (src/global/140600.c): stage 2: behavior identified; frame is 0x40 target vs 0x28 candidate, with local slots target 0x34/0x38/0x3C
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} SynVoiceBiquad;

f32 func_80611BB4(f32, f32);

void func_8073BB10(f32 arg0, f32 arg1, f32 arg2, SynVoiceBiquad *arg3, SynVoiceBiquad *arg4) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    if ((arg0 - 200.0f) <= arg1) {
        arg1 = arg0 - 200.0f;
    }
    sp3C = func_80611BB4(arg1 * 3.1415927f, arg0);
    sp38 = sp3C * sp3C;
    sp34 = (sp3C * 1.4142137f) / arg2;
    arg3->unk0 = sp38 / (1.0f + sp38 + sp34);
    arg3->unk4 = arg3->unk0 * 2.0f;
    arg3->unk8 = arg3->unk0;
    arg4->unk4 = ((sp38 - 1.0f) * 2.0f) / (1.0f + sp38 + sp34);
    arg4->unk8 = ((1.0f + sp38) - sp34) / (1.0f + sp38 + sp34);
}
