// func_806F3DC8 (src/global/F56F0.c): stage 4: exact body except target saves a3 at sp+0xC before masking; arg3 &= 0xFFFF did not induce home-slot store
void func_806F3DC8(u16 *arg0, s16 *arg1, u8 *arg2, s32 arg3) {
    s16 temp_v0;
    u8 temp_v0_2;

    arg3 &= 0xFFFF;
    temp_v0 = *arg1;
    if (temp_v0 != 0) {
        *arg1 = temp_v0 - 1;
        return;
    }
    temp_v0_2 = *arg2;
    if (temp_v0_2 != 0) {
        *arg2 = temp_v0_2 - 1;
        *arg0 |= arg3;
    }
}
