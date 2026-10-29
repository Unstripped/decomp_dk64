// func_80719B88 (src/global/11BC10.c): stage 6: if/else diamond + mask-reads-field; only ugen scratch numbering differs (t7/t8/t0/t9 vs t6/t7/t9/t8); mask operand load node reserves t6 before store-to-load forwarding
void func_80719A0C(TimedEffectActorView *, s8 *);

void func_80719B88(TimedEffectActorView *arg0, s8 *arg1) {
    u8 temp_t6;
    s32 temp_v0;
    s32 var_v1;

    func_80719A0C(arg0, arg1);
    temp_v0 = arg0->unk36D;
    arg0->unk344 = (f32)((f64)arg0->unk344 + 0.8);
    if (temp_v0 < 0x10) {
        var_v1 = temp_v0;
    } else {
        var_v1 = 0x10;
    }
    temp_t6 = temp_v0 - var_v1;
    arg0->unk36D = temp_t6;
    if ((arg0->unk36D & 0xFF) == 0) {
        *arg1 = 1;
    }
}
