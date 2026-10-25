// func_8070DDDC (src/global/112080.c): stage 2: resource-node creation candidate compiled; stack and global traversal allocation differ
// Best stage-2 reconstruction is retained in the private copy history; this draft records the m2c control flow.
s32 func_8070DDDC(u16 arg0, s32 arg1) {
    s32 sp20;
    s32 sp1C;
    void **sp18;
    s32 temp_a0;
    u8 temp_v1;
    void **var_v1;
    void *var_a0;
    void *var_v0;
    void *var_v0_2;

    var_v0 = func_8070D928(arg0);
    var_a0 = var_v0;
    if (var_v0 == NULL) {
        temp_a0 = func_8066B0F8(0xC, arg0, 1, 1);
        var_v1 = &D_807550C0;
        if (D_807550C0 != NULL) {
            var_v0_2 = D_807550C0;
            do {
                var_v1 = var_v0_2 + 0xC;
                var_v0_2 = var_v0_2->unkC;
            } while (var_v0_2 != NULL);
        }
        sp18 = var_v1;
        sp1C = temp_a0;
        sp20 = func_8070D6D8(temp_a0);
        assetFreeBuffer(temp_a0, 0x1F1, 0x50);
        var_v0 = func_80610FE8(0x10);
        var_a0 = var_v0;
        *var_v1 = var_v0;
        var_v0->unk4 = sp20;
        var_v0->unk0 = arg0;
        var_v0->unk2 = 0;
        var_v0->unkC = 0;
        var_v0->unk8 = (s8) arg1;
    }
    temp_v1 = var_v0->unk8;
    if (temp_v1 != 0) {
        if (temp_v1 == 1) {
            var_v0->unk2 = 2U;
        }
    } else {
        var_v0->unk2 = (u8) (var_v0->unk2 + 1);
    }
    return var_a0->unk4;
}
