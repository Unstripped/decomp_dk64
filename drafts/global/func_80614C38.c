// func_80614C38 (src/global/17B90.c): stage 4; closest permuter result 230; remaining byte temporary register assignment and call delay slots
u32 *func_80614C38(u32 *arg0, Perm3bRenderActor *arg1, Perm3bDisplay *arg2) {
    u32 *temp_s2;
    u32 *var_s1;
    u16 temp_s4;
    u8 temp_v1;
    s32 temp_v0;
    u32 temp_t2;
    u32 var_v0;
    Perm3bSegmentNode *var_s0;

    var_s0 = arg2->unk14;
    var_s1 = arg0;
    temp_s4 = arg1->unk146;
    if (var_s0 != NULL) {
        do {
            temp_v1 = var_s0->unk8;
            temp_s2 = var_s1;
            temp_v0 = temp_v1 - 7;
            temp_t2 = temp_v1 * 4;
            if (((s32) temp_s4 >> (temp_v0 & 0xFF)) & 1) {
                var_s1[0] = ((temp_v1 * 4) & 0xFFFF) | 0xDB060000;
                var_s1 += 2;
                var_v0 = osVirtualToPhysical(var_s0->unk0);
            } else {
                temp_s2[0] = (temp_t2 & 0xFFFF) | 0xDB060000;
                var_s1 += 2;
                var_v0 = osVirtualToPhysical(var_s0->unk4);
            }
            temp_s2[1] = var_v0;
            var_s0 = var_s0->unkC;
        } while (var_s0 != NULL);
    }
    return var_s1;
}
