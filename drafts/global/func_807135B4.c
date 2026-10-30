// func_807135B4 (src/global/117190.c): stage 5: instruction stream, frame 0x48 and slots identical; only diff is as1 delay slot: ours 'bnel t5,at,L; lwc1 f16,0x34(sp)' vs target 'bne t5,at,L; nop' at the func_8076A0A8==0x4C compare (2 lines, rest of function identical). Needs: temp_v0 declared first, var_v1 second, then pair, sp34, sp30; var_ft1/temp_v0_2/sp40 removed; (f32)D_8074450C inlined in the call arg; 'return arg0;' inside the condition. Caller proto func_807135B4 in 117190.c must become Gfx *func_807135B4(Gfx *).
typedef struct {
    s32 unk0;
    s32 unk4;
} R117fPair;

extern R117fPair D_80755370;
extern u8 D_8074450C;
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_807ECD09;
extern s16 D_80744490;
u8 textGetFontHeight(s16);
s32 func_807142D8();
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

Gfx *func_807135B4(Gfx *arg0) {
    s32 temp_v0;
    s32 var_v1;
    R117fPair sp38;
    f32 sp34;
    f32 sp30;

    temp_v0 = D_8076A064 - 0x5A;
    if ((temp_v0 >= 0) && !(temp_v0 & 0x10)) {
        sp38 = D_80755370;
        var_v1 = 0;
        sp34 = (f32) D_80744490;
        sp30 = (f32) (0xBD - textGetFontHeight(6));
        if ((D_807ECD09 != 0) && ((func_807142D8() == 0) || (var_v1 = 1, (D_8076A0A8 == 0x4C)))) {
            return arg0;
        }
        sp34 = (f32) ((f64) sp34 * 0.5);
        R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
        arg0 = hudDrawScaledText(arg0, (s16) (s32) (sp34 * 4.0f), (s16) (s32) ((f32) D_8074450C * sp30 * 4.0f), 0.7f, func_8070E750(0xC, (s32) (&sp38.unk0)[var_v1], 1));
    }
    return arg0;
}
