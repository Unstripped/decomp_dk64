// func_807135B4 (src/global/117190.c): stage 3: behavior and blocks recovered; current frame 0x58 rather than target 0x48 because arg0 spills in a3 instead of s0, then FP allocation diverges
// func_807135B4: stage 3; reconstructs all blocks but frame is 0x58 vs target 0x48 and keeps arg0 in a spill rather than s0.
typedef struct {
    s32 unk0;
    s32 unk4;
} R117fPair;

extern s16 D_80744490;
extern u8 D_8074450C;
extern R117fPair D_80755370;
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_807ECD09;
u8 func_806FD894(s16);
void *func_8070E750(s32, s32, s32);
s32 func_807142D8();
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

void *func_807135B4(void *arg0) {
    s32 sp40;
    R117fPair sp38;
    f32 sp34;
    f32 sp30;
    f32 var_ft1;
    s32 temp_v0;
    void *temp_v0_2;
    s32 var_v1;
    void *var_s0;

    temp_v0 = D_8076A064 - 0x5A;
    var_s0 = arg0;
    if ((temp_v0 >= 0) && !(temp_v0 & 0x10)) {
        sp38 = D_80755370;
        sp40 = 0;
        sp34 = (f32) D_80744490;
        var_v1 = sp40;
        sp30 = (f32) (0xBD - func_806FD894(6));
        if ((D_807ECD09 != 0) && ((func_807142D8() == 0) || (var_v1 = 1, (D_8076A0A8 == 0x4C)))) {
        } else {
            sp34 = (f32) ((f64) sp34 * 0.5);
            R117D_WRITE_GFX(var_s0, 0xFCFFFFFF, 0xFFFCF279);
            var_s0 = (Gfx *) var_s0 + 1;
            temp_v0_2 = func_8070E750(0xC, (s32) (&sp38.unk0)[var_v1], 1);
            var_ft1 = (f32) D_8074450C;
            var_s0 = hudDrawScaledText(var_s0, (s16) (s32) (sp34 * 4.0f), (s16) (s32) (var_ft1 * sp30 * 4.0f), 0.7f, temp_v0_2);
        }
    }
    return var_s0;
}
