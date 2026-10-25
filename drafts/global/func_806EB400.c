// func_806EB400 (src/global/EFDC0.c): Stage 4 predicate reconstruction: only register allocation and branch scheduling remain.
s32 func_806EB400(Actor *arg0) {
    s32 temp_t6;
    s32 var_a1;
    s32 var_v1;
    u8 temp_v1;
    EfASubActor *temp_v0;

    temp_v0 = (EfASubActor *)arg0->unk174;
    temp_t6 = temp_v0->unkD4 == 0;
    var_v1 = temp_t6;
    if (temp_t6 == 0) {
        var_v1 = EfA_Q[D_807FC929].unk29C == 0x3F;
    }
    if ((D_8074E77C[D_807FC929] == 7) || (temp_v0->unk1F0 & 0x8000)) {
        return 0;
    }
    temp_v1 = arg0->unk154;
    if ((temp_v1 != 0x34) && (temp_v1 != 0x36)) {
        var_a1 = var_v1 & 1;
    } else {
        var_a1 = 0;
    }
    return var_a1;
}
