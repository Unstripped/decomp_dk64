// func_8070A848 (src/global/10E1D0.c): stage 4: full loop and instructions; register allocation differs
void func_8070A848(u32 *arg0, u32 *arg1) {
    s32 i = 0;
    if (((D_80744490 * D_80744494) / 16) > 0) do {
        arg0[0] = arg1[0] | 0x10001; arg0[1] = arg1[1] | 0x10001;
        arg0[2] = arg1[2] | 0x10001; arg0[3] = arg1[3] | 0x10001;
        arg0[4] = arg1[4] | 0x10001; arg0[5] = arg1[5] | 0x10001;
        arg0[6] = arg1[6] | 0x10001; arg0[7] = arg1[7] | 0x10001;
        i++; arg0 += 8; arg1 += 8;
    } while (i < ((D_80744490 * D_80744494) / 16));
}
