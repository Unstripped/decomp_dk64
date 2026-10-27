// func_8061B4E4 (src/global/201B0.c): bss-blocked: text-exact (TEXT OK) with 'u64 D_807F5CE0;' DEFINED in this TU. Nested __ull_div(__ull_div(__ll_mul(osGetTime()-D,0x40),0xBB8),0x2710) avoids spills; needs extern u8 D_807F5D14 and D_80747708 table {u32; u8; u8; pad[2]}.
u64 D_807F5CE0;
extern u8 D_807F5D14;
extern struct {
    u32 unk0;
    u8 unk4;
    u8 unk5;
    u8 pad6[2];
} D_80747708[];
extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
void func_80712524(s32, s32);

void func_8061B4E4(void) {
    u64 t = __ull_div(__ull_div(__ll_mul(osGetTime() - D_807F5CE0, 0x40), 0xBB8), 0x2710);

    if ((u32)t >= D_80747708[D_807F5D14].unk0) {
        func_80712524(D_80747708[D_807F5D14].unk4, D_80747708[D_807F5D14].unk5);
        if (++D_807F5D14 >= 6) {
            D_807F5CE0 = 0;
        }
    }
}
