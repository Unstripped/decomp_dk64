// Stage 5: Gfx macro candidate; all command words and both func_8068C5A8 calls match.
// Remaining mismatch is IDO allocation: target retains the display-list cursor in s0,
// while this source keeps it in a0. The target additionally uses a0 for temp_a0.
Gfx *func_806FF628(Gfx *arg0, s32 arg1) {
    u8 temp_a0;
    R1F103AB0aState1EC *state;
    Gfx *temp_v0;
    Gfx *var_s0;
    Gfx *var_v0;

    state = (R1F103AB0aState1EC *)((Actor **)D_807FC924)[1]->unk174;
    temp_v0 = func_806FEDB0(arg0, ((R1F103AB0aState *)state)->unk1A4);
    temp_a0 = state->unk1EC;
    var_s0 = temp_v0;
    if (temp_a0 == 2) {
        gDPSetPrimColor(var_s0++, 0, 0, 0xFF, 0, 0, 0x64);
        var_v0 = func_8068C5A8(var_s0, 0x45, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
        goto block_4;
    }
    if (temp_a0 == 1) {
        gDPSetPrimColor(var_s0++, 0, 0, 0, 0xFF, 0, 0x64);
        var_v0 = func_8068C5A8(var_s0, 0x44, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
block_4:
        var_s0 = var_v0;
    }
    return var_s0;
}
