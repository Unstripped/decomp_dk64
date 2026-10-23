// func_80690190 (src/global/936B0.c): regalloc on t-regs; s16 arg1 spills to 0x2C(sp), ptr matches frame 0x28
extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
u32 func_806119A0(void);

void func_80690190(M93E_Struct4 *arg0, s16 arg1) {
    arg1 = D_80770628[((M93E_Actor6E *)D_807FBB40)->unk6E];
    if (((M93E_Actor6E *)D_807FBB40)->unk80 < ((M93E_Actor6E *)D_807FBB40)->unkAC + 4.0f) {
        D_80770B68[arg1] = ((f64)((M93E_Actor6E *)D_807FBB40)->unkB8 / 300.0) + 1.0;
        D_80770BC0[arg1] = 1.0f;
    } else {
        D_80770B68[arg1] = (f64)arg0->unk4 + 1.2;
        D_80770BC0[arg1] = 5.0f;
    }

    arg1 = D_80770628[((M93E_Actor6E *)D_807FBB40)->unk70];
    if (((M93E_Actor6E *)D_807FBB40)->unk80 < ((M93E_Actor6E *)D_807FBB40)->unkAC + 4.0f) {
        f32 *ptr = &D_80770BC0[arg1];
        if (*ptr == 0.0f) {
            D_80770B68[arg1] = (((((f64)(u32)func_806119A0() / 4294967295.0) * 0.05) + 0.975) *
                                (0.2 + ((f64)((M93E_Actor6E *)D_807FBB40)->unkB8 / 300.0)));
            *ptr = 1.0f;
        }
    } else {
        D_80770B68[arg1] = ((f64)arg0->unk4 * 1.5) + 0.2;
        D_80770BC0[arg1] = 8.0f;
    }
}
