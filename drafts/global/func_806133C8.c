// func_806133C8 (src/global/17B90.c): stage 4; closest permuter result 275; remaining prologue and loop branch-likely scheduling
void func_806133C8(Perm3bCommand *arg0, Perm3bCommand *arg1) {
    Perm3bCommand *var_s0;
    u32 temp_v0;

    var_s0 = arg0;
    if (var_s0 != arg1) {
        temp_v0 = var_s0->unk0;
        do {
            if ((temp_v0 >> 0x18) == 0xFD) {
                temp_v0 = var_s0->unk4;
                if (((temp_v0 * 0x10) >> 0x1C) == 0) {
                    var_s0->unk4 = func_8066B0F8(0x19, temp_v0, 0, 0);
                }
            }
            var_s0++;
            temp_v0 = var_s0->unk0;
        } while (var_s0 != arg1);
    }
}
