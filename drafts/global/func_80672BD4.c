// func_80672BD4 (src/global/70FD0.c): Closest diff: 4 of 5 checks match target (branches and moves in delay slots); 4th check (flags & 8) regalloc difference
u8 func_80672BD4(M70F_Actor *arg0) {
    M70F_ActorSub140 *temp_v0;
    u16 temp_v0_2;
    s32 var_v1;

    if ((var_v1 = (arg0->unk110 != 0))) goto end;
    temp_v0 = arg0->unk140;
    if ((var_v1 = (temp_v0->unk6C != 0))) goto end;
    if ((var_v1 = (temp_v0->unk24 != 0))) goto end;
    temp_v0_2 = arg0->unk6A;
    if ((var_v1 = ((temp_v0_2 & 8) != 0))) goto end;
    var_v1 = (temp_v0_2 & 0x400) != 0;
end:
    return var_v1;
}
