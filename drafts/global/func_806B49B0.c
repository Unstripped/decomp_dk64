// func_806B49B0 (src/global/B7490.c): stage 4-5: 8 insns short. plain switch(arg0): switch temp 1085|1 and expr ucvt(arg0) uncolored (-ve save) so t0 never allocated; locals order temp_v0,dead1,dead2,sp32 gives sp32 at 0x32 like target. var_t0=arg0 copies get copy-propagated into call args (lw a0,0x24); s16/s8 var gives var in memory + lh t0 temp (8 bytes too big). Permuter got 762 only with UB uninitialised var switch(var_t0){var_t0=arg0;..}: shows target t0 web has only compares uses.
extern f32 D_807502EC;
void func_80724CA4(s32, s32);

void func_806B49B0(u8 arg0, s16 arg1, s16 arg2) {
    s16 *temp_v0;
    s32 *dead1;
    s32 *dead2;
    s16 sp32;

    temp_v0 = B7490A->unk178;
    dead1 = (s32 *) temp_v0;
    dead2 = (s32 *) temp_v0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(1, 1);
        D_807FDC90->unk30 = D_807FBB40->unk4->unk38;
        D_807FBB40->unkB8 = (f32) (u32) D_807FDC9C->unkC;
        *temp_v0 = D_807FDC9C->unkA;
        B7490A->unkC4 = D_807502EC;
    }
    sp32 = D_807FDC9C->unk6 + *temp_v0;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (arg0 != 0x37)) {
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
    }
    switch (arg0) {
        case 2:
        case 3:
            if (D_807FBB40->unk155[0] == 0) {
                func_80614EBC(D_807FBB40, arg1);
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            }
            func_8072AB74(arg0, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0xE1, 0.0f);
            if (D_807FBB40->unk80 < (f32) sp32) {
                if (D_807FBB40->unk155[0] == 2) {
                    D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.03125));
                } else {
                    D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.015625));
                }
            }
            B7490A->unkE8 = func_806CC190(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                case 1:
                case 2:
                    func_80614EBC(D_807FBB40, arg2);
                    D_807FBB40->unk155[0] = 3;
                case 3:
                    func_806B3F90((void *) D_807FDC90, 0x26);
                    break;
            }
            break;
        case 0x37:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                D_807FBB40->unk154 = 0x40;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(arg1);
            break;
    }
    switch (arg0) {
        case 2:
        case 3:
            func_8072D13C(arg0, 1);
            break;
        case 0x26:
            if (func_8072D13C(arg0, 1) != 0) {
                D_807FBB40->unk154 = D_807FDC9C->unk10;
                D_807FBB40->unk155[0] = 0;
            }
            break;
    }
}
