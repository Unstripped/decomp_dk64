// func_80614C38 (src/global/17B90.c): stage 4: exact frame, callee saves, and operation order; remaining diff is u8 index allocated in v0 instead of target v1, shifting caller-saved register choices.
s32 *func_80614C38(s32 *arg0, void *arg1, void *arg2) {
    s32 *temp_s2;
    s32 *var_s1;
    u16 temp_s4;
    u32 var_v0;
    u8 temp_v1;
    void *var_s0;

    var_s0 = arg2->unk14;
    var_s1 = arg0;
    temp_s4 = arg1->unk146;
    if (var_s0 != NULL) {
        do {
            temp_v1 = var_s0->unk8;
            temp_s2 = var_s1;
            if (((s32) temp_s4 >> ((temp_v1 - 7) & 0xFF)) & 1) {
                var_s1->unk0 = ((temp_v1 * 4) & 0xFFFF) | 0xDB060000;
                var_s1 += 8;
                var_v0 = osVirtualToPhysical(var_s0->unk0);
            } else {
                temp_s2->unk0 = ((temp_v1 * 4) & 0xFFFF) | 0xDB060000;
                var_s1 += 8;
                var_v0 = osVirtualToPhysical(var_s0->unk4);
            }
            temp_s2->unk4 = var_v0;
            var_s0 = var_s0->unkC;
        } while (var_s0 != NULL);
    }
    return var_s1;
}
