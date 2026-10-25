// func_806FD7A8 (src/global/100180.c): Stage 3: frame and control flow reconstructed; outer font index remains allocated in a0 rather than target a2. A 900-second permuter run improved to score 70 but found no clean score-zero match.
s16 func_806FD7A8(s16 arg0, s32 arg1) {
    s16 temp_a2;
    u8 var_v1;
    NmF10D2D0b_CharInfo *var_a0;

    temp_a2 = arg0;
    arg0 = temp_a2;
    if (arg0 & 0x80) {
        var_a0 = &D_80754A34[(s16)(arg0 ^ 0x80)];
        var_v1 = var_a0->unk5;
    } else if (((u8 *)&arg1)[3] == 0x20) {
        var_a0 = &D_80754A34[temp_a2];
        var_v1 = var_a0->unk3;
    } else {
        func_806FB914(temp_a2, &((u8 *)&arg1)[3], temp_a2);
        var_v1 = ((u8 *)D_80754A18[temp_a2])[((u8 *)&arg1)[3] * 4 + 2];
        var_a0 = &D_80754A34[temp_a2];
    }
    return var_v1 + var_a0->unk4;
}
