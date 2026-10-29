// func_8071DB74 (src/global/11BC10.c): stage 5: frame 0x20 and s0 set match; state pointer colored v0-whole vs target v1-early + move v0,v1 split (late uses v0). Tried redef placement in/out of if, two-local copy (coalesced away), field-access form, test-then-load, s32/u32/u8 callee returns, deadsweep, permuter 31k iters (plateau 146).
void func_8071DB74(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BGFallState *var_v1;
    Fx11BGSource *floor;
    u8 state;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        func_8071D94C(0, arg0, arg1);
        var_v1 = arg0->unk384;
    }
    var_v1->unk8 = var_v1->unk8 + -0.5f;
    arg0->unk340 = arg0->unk340 + var_v1->unk0;
    arg0->unk344 = arg0->unk344 + var_v1->unk8;
    arg0->unk348 = arg0->unk348 + var_v1->unk4;
    state = *arg1;
    if (state == 0) {
        floor = arg0->unk338;
        if (floor != NULL) {
            if (arg0->unk344 <= floor->unkAC) {
                state = *arg1 = 1;
            }
        } else {
            if (arg0->unk344 <= var_v1->unkC) {
                state = *arg1 = 1;
            }
        }
        if (state != 0) {
            func_80718124(arg0->unk360 * 5.0f, arg0->unk340, arg0->unk344, arg0->unk348);
        }
    }
}
