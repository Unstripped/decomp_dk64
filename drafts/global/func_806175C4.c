// func_806175C4 (src/global/19A00.c): stage 4: direct f64 expression candidate with the target literals and clamped conversion; fdiff retains a larger frame and different FP/register scheduling around the byte-to-double conversion.
typedef struct P19c4ActorSub { u8 pad0[0x34]; f32 unk34; } P19c4ActorSub;
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_806175C4(Actor *arg0) {
    s16 sp46;
    u8 sp45;
    u8 sp44;
    u8 sp43;
    u8 sp42;
    f32 var_fv1;
    f64 temp_fv0;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp46);
    func_80614F28(&sp43);
    func_80614F28(&sp42);
    func_80614F28(&sp45);
    func_80614F28(&sp44);
    temp_fv0 = (((((f64)((P19c4ActorSub *)arg0->unk4)->unk34 / 0.4381361) * 200.0) + 55.0) * (f64)sp43) / 255.0;
    if (temp_fv0 > 255.0) {
        var_fv1 = (f32)255.0;
    } else {
        var_fv1 = (f32)temp_fv0;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp46, (u32)var_fv1, (s32)sp42, (s32)sp45, (s32)sp44, 0.3f, 0);
    return 1;
}
