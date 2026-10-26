// func_80028878 (src/boss/3840.c): from .scratch/Boss3C/func_80028878_best.c
? func_80028680();                                  /* extern */
? func_80028820(u8);                                /* extern */
s32 func_805FCA64();                                /* extern */
? func_80602B60(?, ?);                              /* extern */
f32 func_80602D4C(?);                               /* extern */
? func_80609140(?, ?, ?, ?, s32, s32);              /* extern */
? func_80614EBC(void *, ?, void *);                 /* extern */
? func_8061CC40(void *, s16, ?);                    /* extern */
? func_8068C350(? *, void *, ?);                    /* extern */
? func_806A2B20(void *);                            /* extern */
? func_806A2B80(void *);                            /* extern */
? func_806FB370(?, ?, ?);                           /* extern */
? func_80709464(?);                                 /* extern */
? func_80712524(?, ?);                              /* extern */
s32 func_8071441C();                                /* extern */
? func_80714CC0(? *, ?, ?32, f32, f32);             /* extern */
? func_80724A20();                                  /* extern */
s32 flagGet(s16, ?, void *);                  /* extern */
? flagSet(s16, ?, ?);                         /* extern */
? func_80737AC4(s32, ?, s16);                       /* extern */
? n_alSndpAllocate(s32, ?, ?, ?, f32, s32, s32);    /* extern */
extern s16 D_800359A0;
extern ? D_800359AC;
extern ? D_800359B8;
extern ? D_800359C4;
extern ? D_8071FE08;
extern u8 D_80750AD4;
extern s32 D_80767CC0;
extern s32 D_8076A0A8;
extern s32 D_8076D1F8;
extern void *D_807FBB40;
extern void *D_807FBB48;
extern void *D_807FBB4C;
extern ? func_800286B8;

void func_80028878(s32 arg0) {
    void *sp44;
    u8 sp43;
    s32 sp30;
    ? var_a0_2;
    s16 temp_a0;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 var_v1;
    s32 temp_t8;
    u8 temp_t0;
    u8 temp_t3;
    u8 temp_t7;
    u8 temp_v0;
    u8 var_a0;
    u8 var_v1_2;
    void *temp_a2;
    void *temp_s0;
    void *temp_v0_2;
    void *var_a2;

    temp_a2 = D_807FBB40;
    sp43 = D_8076A0A8 - 0xCB;
    sp44 = temp_a2->unk178;
    temp_s0 = temp_a2->unk17C;
    if (D_807FBB4C->unk80 < 30.0f) {
        D_807FBB4C->unk7C = 0x44430000;
        D_807FBB4C->unk80 = 50.0f;
        D_807FBB4C->unk84 = 750.0f;
        func_80714CC0(&D_8071FE08, 0x3F800000, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84);
    }
    if (!(temp_a2->unk60 & 0x10)) {
        func_806FB370(5, 0, 1);
        func_806FB370(2, 0, 1);
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 & 0xFFFDFFFF);
        if ((sp44->unk14 == 0) || (D_807FBB40->unk58 != 0x126)) {
            if (flagGet(0x5A, 2, D_807FBB40) == 0) {
                func_80709464(0);
            }
            temp_t0 = D_80750AD4 + 1;
            D_80750AD4 = temp_t0;
            if ((temp_t0 & 0xFF) >= 0xD) {
                func_80602B60(0x2B, 0);
                func_80709464(0);
                flagSet(0x55, 0, 2);
                func_80712524(0xD7, 0);
                D_80750AD4 = 0;
                D_807FBB40->unk154 = 0x6AU;
                D_807FBB40->unk155 = 0U;
            }
        }
        n_alSndpAllocate(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, temp_s0 + 4);
        n_alSndpAllocate(D_8076D1F8, 0x119, 0, 0x40, 1.0f, 0x80, temp_s0 + 8);
    }
    func_80724A20();
    var_a2 = D_807FBB40;
    temp_v0 = var_a2->unk154;
    switch (temp_v0) {                              /* switch 1; irregular */
    case 0x37:                                      /* switch 1 */
        if (var_a2->unk155 == 0) {
            func_806A2B20(var_a2->unk11C);
block_25:
            var_a2 = D_807FBB40;
        }
        break;
    case 0x6A:                                      /* switch 1 */
        if (var_a2->unk155 == 0) {
            func_80614EBC(var_a2, 0, var_a2);
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            goto block_25;
        }
        break;
    case 0x6C:                                      /* switch 1 */
        sp44->unk12 = (u16) (sp44->unk12 | 1);
        func_80028680();
        if ((sp44->unk14 != 0) && (D_807FBB40->unk58 == 0x126)) {
            func_806A2B80(D_807FBB40->unk11C);
        }
        D_807FBB40->unk154 = (u8) *(sp44->unk15 + arg0);
        sp44->unk15 = (u8) (sp44->unk15 + 1);
        D_807FBB40->unk155 = 0U;
        goto block_25;
    default:                                        /* switch 1 */
        temp_v0_2 = var_a2->unk11C;
        if ((temp_v0_2 != NULL) && (temp_v0_2->unk154 == 5)) {
            func_80028820();
            D_807FBB40->unk154 = 0x6AU;
            D_807FBB40->unk155 = 0U;
            func_8061CC40(D_807FBB40, *(&D_800359C4 + (sp43 * 2)), 1);
            flagSet(0x5A, 1, 2);
            goto block_25;
        }
        break;
    }
    if (!(var_a2->unk60 & 0x10)) {
        if (func_8071441C() != 0) {
            flagSet(0x55, 0, 2);
        }
        var_a0 = 0x5C;
        if ((flagGet(0x5D, 2) == 0) || (var_a0 = sp43, (flagGet(0x5C, 2) != 0))) {
            func_80028820(var_a0);
            D_80750AD4 = 1;
            if (flagGet(0x5D, 2) == 0) {
                func_8061CC40(D_807FBB40, 0x19, 1);
                flagSet(0x5D, 1, 2);
            } else {
                func_8061CC40(D_807FBB40, D_800359A0, 1);
            }
            flagSet(0x5C, 0, 2);
            flagSet(0x55, 1, 2);
        } else {
            temp_a0 = var_a0 + 0x55;
            sp30 = (s32) temp_a0;
            if (flagGet(temp_a0, 2) == 0) {
                func_8061CC40(D_807FBB40, (&D_800359A0)[sp43], 1);
                flagSet(unksp32, 1, 2);
            } else if (flagGet(0x5A, 2) != 0) {
                if (flagGet(0x5B, 2) != 0) {
                    func_8061CC40(D_807FBB40, *(&D_800359AC + (sp43 * 2)), 1);
                    flagSet(0x5A, 0, 2);
                } else {
                    func_80602B60(0x2B, 0);
                    D_807FBB40->unk154 = 0x6AU;
                    D_807FBB40->unk155 = 0U;
                    flagSet(0x5B, 1, 2);
                    func_80712524(0xD7, 1);
                    D_80750AD4 -= 1;
                }
            } else {
                func_8061CC40(D_807FBB40, *(&D_800359B8 + (sp43 * 2)), 1);
            }
        }
    }
    if ((D_807FBB48->unk154 == 0x67) || ((f64) func_80602D4C(0xF) > 0.1)) {
        var_v1 = 0x1D4C;
        temp_s0->unkE = 0x1D4C;
        temp_v0_3 = temp_s0->unk10 - 0x3E8;
        if (temp_v0_3 < 0x1D4C) {
            goto block_52;
        }
        temp_s0->unk10 = temp_v0_3;
    } else {
        temp_v0_4 = temp_s0->unkE - 0x64;
        if (temp_v0_4 < 0x1F40) {
            temp_s0->unkE = 0x1F40;
        } else {
            temp_s0->unkE = temp_v0_4;
        }
        temp_v0_5 = temp_s0->unkE;
        var_v1 = temp_s0->unk10 + 0x3E8;
        if (temp_v0_5 < var_v1) {
            temp_s0->unk10 = temp_v0_5;
        } else {
block_52:
            temp_s0->unk10 = var_v1;
        }
    }
    func_80737AC4(temp_s0->unk4, 8, temp_s0->unk10);
    func_80737AC4(temp_s0->unk8, 8, temp_s0->unk10);
    var_v1_2 = temp_s0->unkD;
    if (var_v1_2 & 0x17) {
        var_a0_2 = 0x1E8;
        if ((u32) (D_80767CC0 - temp_s0->unk0) >= 6U) {
            temp_s0->unk0 = (s32) D_80767CC0;
            temp_s0->unkC = 0U;
            if (var_v1_2 & 0x10) {
                var_a0_2 = 0x42B;
            } else if (var_v1_2 & 4) {
                var_a0_2 = 0x1EA;
            } else if (var_v1_2 & 2) {
                var_a0_2 = 0x1E7;
            }
            func_80609140(var_a0_2, 0x58EF, 0x42800000, 0x3F800000, 0x14, 0x80);
        }
        temp_v0_6 = temp_s0->unkE + 0x4650;
        if (temp_v0_6 >= 0x8000) {
            temp_s0->unkE = 0x7FFF;
        } else {
            temp_s0->unkE = temp_v0_6;
        }
        temp_t3 = temp_s0->unkD & 0xFFE0;
        temp_s0->unkD = temp_t3;
        var_v1_2 = temp_t3 & 0xFF;
    }
    if (var_v1_2 & 8) {
        if ((u32) (D_80767CC0 - temp_s0->unk0) >= 6U) {
            if (temp_s0->unkC == 0) {
                temp_s0->unk0 = (s32) D_80767CC0;
            }
            temp_t7 = temp_s0->unkC + 1;
            temp_t8 = temp_t7 & 0xFF;
            temp_s0->unkC = temp_t7;
            switch (temp_t8) {                      /* switch 2 */
            case 0x3E:                              /* switch 2 */
                temp_s0->unkC = 0U;
                temp_s0->unkD = (u8) (temp_s0->unkD & 0xFFF7);
                /* fallthrough */
            case 0x1:                               /* switch 2 */
            case 0x10:                              /* switch 2 */
            case 0x1D:                              /* switch 2 */
            case 0x29:                              /* switch 2 */
            case 0x34:                              /* switch 2 */
                func_80609140(0x1E9, 0x58EF, 0x42800000, 0x3F800000, 0, 0x80);
                break;
            }
        }
        temp_v0_7 = temp_s0->unkE + 0x4650;
        if (temp_v0_7 >= 0x8000) {
            temp_s0->unkE = 0x7FFF;
        } else {
            temp_s0->unkE = temp_v0_7;
        }
    }
    if ((sp44->unk12 & 1) && (func_805FCA64() != 0)) {
        func_8068C350(&func_800286B8, D_807FBB40, 3);
    }
}
