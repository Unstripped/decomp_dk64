// func_807135B4 (src/global/117190.c): stage 4: direct Gfx parameter now matches target s0 entry and display write; frame 0x50 vs target 0x48 and local slots remain unresolved
// func_807135B4: stage 4; direct Gfx* parameter produces target s0 entry and command sequence. Remaining frame/local layout mismatch: current 0x50 vs target 0x48; pair and float slots must be 0x38/0x34/0x30, sp40 at 0x40. Prefer short-circuit conditional form for target's first beqz return.
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
s32 func_807142D8();
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

Gfx *func_807135B4(Gfx *arg0) {
    s32 sp40;
    R117fPair sp38;
    f32 sp34;
    f32 sp30;
    f32 var_ft1;
    s32 temp_v0;
    void *temp_v0_2;
    s32 var_v1;

    temp_v0 = D_8076A064 - 0x5A;
    if ((temp_v0 >= 0) && !(temp_v0 & 0x10)) {
        sp38 = D_80755370;
        sp40 = 0;
        sp34 = (f32) D_80744490;
        var_v1 = sp40;
        sp30 = (f32) (0xBD - func_806FD894(6));
        if ((D_807ECD09 != 0) && ((func_807142D8() == 0) || (var_v1 = 1, (D_8076A0A8 == 0x4C)))) {
        } else {
            sp34 = (f32) ((f64) sp34 * 0.5);
            R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
            temp_v0_2 = func_8070E750(0xC, (s32) (&sp38.unk0)[var_v1], 1);
            var_ft1 = (f32) D_8074450C;
            arg0 = hudDrawScaledText(arg0, (s16) (s32) (sp34 * 4.0f), (s16) (s32) (var_ft1 * sp30 * 4.0f), 0.7f, temp_v0_2);
        }
    }
    return arg0;
}
