// func_80719B88 (src/global/11BC10.c): Stage 6: frame and all operations match; one extra register copy around countdown selection remains.
void func_80719A0C(TimedEffectActorView *, s8 *);

void func_80719B88(TimedEffectActorView *arg0, s8 *arg1) {
    u8 temp_t6;
    u8 temp_v0;
    u8 var_v1;

    func_80719A0C(arg0, arg1);
    temp_v0 = arg0->unk36D;
    var_v1 = 0x10;
    arg0->unk344 = (f32)((f64)arg0->unk344 + 0.8);
    if ((s32)temp_v0 < 0x10) {
        var_v1 = temp_v0;
    }
    temp_t6 = temp_v0 - var_v1;
    arg0->unk36D = temp_t6;
    if (!(temp_t6 & 0xFF)) {
        *arg1 = 1;
    }
}
