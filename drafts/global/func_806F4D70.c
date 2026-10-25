// func_806F4D70 (src/global/F9450.c): stage 3: stores and offsets recovered; scalar global typing/register allocation unresolved
extern ? D_807FD740;
extern ? D_807FD780;

void func_806F4D70(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 temp_t6;
    void *temp_v0;

    temp_t6 = arg0 & 0xFF;
    temp_v0 = (temp_t6 * 0x10) + &D_807FD740;
    temp_v0->unk0 = arg1;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = arg4;
    *(&D_807FD780 + (temp_t6 * 4)) = 0;
}
