// func_806175C4 (src/global/19A00.c): stage 4: 0x48 frame and exact stack offsets matched; diff is 255.0 CSE and clamp regalloc
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_806175C4(Actor *arg0) {
    s16 sp46;
    u8 sp45;
    u8 sp44;
    u8 sp43;
    u8 sp42;
    f32 var_fv1;
    f64 val;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp46);
    scriptReadU8(&sp43);
    scriptReadU8(&sp42);
    scriptReadU8(&sp45);
    scriptReadU8(&sp44);
    val = (((((f64)arg0->unk4->unk34 / 0.4381361) * 200.0) + 55.0) * (f64)sp43) / 255.0;
    if (val > 255.0) {
        var_fv1 = 255.0f;
    } else {
        var_fv1 = val;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp46, (u32)var_fv1, sp42, sp45, sp44, 0.3f, 0);
    return 1;
}
