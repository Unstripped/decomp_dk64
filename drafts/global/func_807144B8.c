// func_807144B8 (src/global/117190.c): Stage 4: behavior recovered; 0x20 frame versus target 0x18 and final call argument allocation remain.
extern s8 D_8074452C;
extern s32 D_807445B8;
extern u32 D_807445BC;
extern u8 D_807467C8;
extern s8 D_8074E77C;
extern s8 D_80755318;
extern s32 D_80755338;
extern s32 D_8075533C;
extern s8 D_80755350;
void func_806C9AE0(void);
void func_80731030(void);
void func_8060DC3C(u8, s32);
s32 func_8060C6B8(s32, s32, s32, u8);
s32 func_8073110C(s32, s32);
void func_805FF4D8(s32, s32);

void func_807144B8(u8 arg0) {
    s32 var_a0;
    s32 var_a1;
    u64 temp_ret;

    temp_ret = osGetTime();
    D_807445B8 = temp_ret;
    D_807445BC = (u32) temp_ret;
    D_80755350 = 0;
    func_806C9AE0();
    func_80731030();
    func_8060DC3C(arg0, 1);
    D_8074E77C = 0;
    if ((func_8060C6B8(0xD, 0, 0, D_807467C8) != 0) || (var_a0 = 0x99, (D_8074452C != 0))) {
        var_a0 = 0xB0;
        if (func_8073110C(0x186, 0) != 0) {
            var_a0 = 0x22;
            goto block_6;
        }
        var_a1 = 1;
    } else {
        D_80755338 = 1;
        D_8075533C = 0;
block_6:
        var_a1 = 0;
    }
    func_805FF4D8(var_a0, var_a1);
    D_80755318 = 6;
}
