// func_8067DCC0 (src/global/80150.c): Stage 5: 1 insn diff (move a0, s6 vs li a0, 2), frame 0x80 matches, all callee saves match; .rodata constant D_80759550 reloc diff
extern s32 D_8071FE64;
extern s32 D_8071FE88;
extern s32 D_8071FEAC;
void func_8071910C(void);
void func_8060E7EC(s32, s32, s32);
u32 func_806119A0(void);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);

void func_8067DCC0(void) {
    void (*sp5C)(void);
    f32 temp_fs0;
    u32 temp_s0;
    s32 var_s1;

    temp_fs0 = (f64) D_807FBB40->unk4->unk38 / 0.15;
    func_8060E7EC(0, 0xB4, 0xA);
    func_807149B8(0);
    func_807149FC(1);
    func_80714CC0(&D_8071FE08, (f64) temp_fs0 * 0.75, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x23, 0xFF, 0x7F, 1);

    for (var_s1 = 0; var_s1 != 7; var_s1++) {
        temp_s0 = ((s32) (func_806119A0() / 10000U)) % 3;
        func_807149B8(1);
        func_807149FC(0xA);
        func_8071498C(func_8071910C);
        func_80714998(2);
        func_80714950(2);
        switch (temp_s0) {
        case 0:
            func_80714CC0(&D_8071FE64, (f64) temp_fs0 * 0.25, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            break;
        case 1:
            func_80714CC0(&D_8071FE88, (f64) temp_fs0 * 0.25, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            break;
        case 2:
            func_80714CC0(&D_8071FEAC, (f64) temp_fs0 * 0.25, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            break;
        }
    }
}
