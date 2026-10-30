// func_807144B8 (src/global/117190.c): Stage 6: C matches text-identical; only reloc differs (D_807445BC vs D_807445B8+0x4: D_807445B8 is a u64 in 450.c so 'D_807445B8 = osGetTime()' emits +4 reloc). Key: nested if/else assigning var_a0/var_a1 in each arm (not goto block_6) fixes frame 0x18.
extern u64 D_807445B8;
extern u8 D_80755350;
extern s32 D_80755338;
extern s32 D_8075533C;
extern u8 D_80755318;
extern s8 D_8074452C;
extern u8 D_807467C8;
extern s8 D_8074E77C;
void func_806C9AE0(void);
void func_80731030(void);
void func_8060DC3C(u8, s32);
s32 func_8060C6B8(s32, s32, s32, u8);
s32 flagGet(s32, s32);
void func_805FF4D8(s32, s32);

void func_807144B8(u8 arg0) {
    s32 var_a0;
    s32 var_a1;

    D_807445B8 = osGetTime();
    D_80755350 = 0;
    func_806C9AE0();
    func_80731030();
    func_8060DC3C(arg0, 1);
    D_8074E77C = 0;
    if ((func_8060C6B8(0xD, 0, 0, D_807467C8) != 0) || (D_8074452C != 0)) {
        if (flagGet(0x186, 0) != 0) {
            var_a0 = 0x22;
            var_a1 = 0;
        } else {
            var_a0 = 0xB0;
            var_a1 = 1;
        }
    } else {
        D_80755338 = 1;
        D_8075533C = 0;
        var_a0 = 0x99;
        var_a1 = 0;
    }
    func_805FF4D8(var_a0, var_a1);
    D_80755318 = 6;
}
