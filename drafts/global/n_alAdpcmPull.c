// n_alAdpcmPull (src/global/144E00.c): stage 2: m2c control-flow draft; requires shared decoder/filter layout and exact 0x80 local-slot ordering
void *alLoadParam(void *, void *, s32, s32, s32, s32, s32); /* extern */

void *n_alAdpcmPull(void *arg0, s16 *arg1, s32 arg2, void *arg3) {
    void *sp7C;
    s16 sp7A;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    void *sp44;
    void *sp40;
    void *sp3C;
    void *sp38;
    s32 *temp_t0_2;
    s32 temp_t0;
    s32 var_s0;
    void *temp_t3;
    void *temp_t6;
    void *temp_t9;

    sp7C = arg3;
    sp4C = 0;
    sp48 = 0;
    sp44 = arg0;
    if (arg2 == 0) {
        return sp7C;
    }
    sp7A = 0;
    temp_t9 = sp7C;
    sp7C = temp_t9 + 8;
    sp40 = temp_t9;
    sp40->unk0 = (s32) ((sp44->unk24 & 0xFFFFFF) | 0x0B000000);
    sp40->unk4 = (s32) ((sp44->unk20->unk10 + 8) & 0x1FFFFFFF);
    var_s0 = (u32) sp44->unk18 < (u32) (sp44->unk30 + arg2);
    if (var_s0 != 0) {
        var_s0 = sp44->unk1C != 0;
    }
    sp48 = var_s0;
    if (sp48 != 0) {
        sp5C = sp44->unk18 - sp44->unk30;
    } else {
        sp5C = arg2;
    }
    if (sp44->unk34 != 0) {
        sp54 = 0x10 - sp44->unk34;
    } else {
        sp54 = 0;
    }
    sp74 = sp5C - sp54;
    if (sp74 < 0) {
        sp74 = 0;
    }
    sp70 = (s32) (sp74 + 0xF) >> 4;
    sp6C = sp70 * 9;
    if (sp48 != 0) {
        sp7C = alLoadParam(sp7C, sp44, sp74, sp6C, (s32) *arg1, (s32) sp7A, sp44->unk38);
        if (sp44->unk34 != 0) {
            *arg1 += sp44->unk34 * 2;
        } else {
            *arg1 += 0x20;
        }
        sp44->unk34 = (s32) (sp44->unk14 & 0xF);
        sp44->unk3C = (s32) (*sp44->unk20 + (((u32) sp44->unk14 >> 4) * 9) + 9);
        sp44->unk30 = (u32) sp44->unk14;
        sp50 = (s32) *arg1;
        if (sp5C < arg2) {
            do {
                arg2 -= sp5C;
                sp58 = (((sp70 + 1) << 5) + sp50 + 0x10) & ~0x1F;
                sp50 += sp5C * 2;
                temp_t0 = sp44->unk1C;
                if ((temp_t0 != -1) && (temp_t0 != 0)) {
                    sp44->unk1C = (s32) (sp44->unk1C - 1);
                }
                if ((u32) arg2 < (u32) (sp44->unk18 - sp44->unk14)) {
                    sp5C = arg2;
                } else {
                    sp5C = sp44->unk18 - sp44->unk14;
                }
                sp74 = (sp5C + sp44->unk34) - 0x10;
                if (sp74 < 0) {
                    sp74 = 0;
                }
                sp70 = (s32) (sp74 + 0xF) >> 4;
                sp6C = sp70 * 9;
                sp7C = alLoadParam(sp7C, sp44, sp74, sp6C, sp58, (s32) sp7A, sp44->unk38 | 2);
                temp_t6 = sp7C;
                sp7C = temp_t6 + 8;
                sp3C = temp_t6;
                sp3C->unk0 = (s32) ((((sp44->unk34 * 2) + sp58) & 0xFFFFFF) | 0x0A000000);
                sp3C->unk4 = (s32) (((sp50 & 0xFFFF) << 0x10) | ((sp5C * 2) & 0xFFFF));
            } while (sp5C < arg2);
        }
        sp44->unk34 = (s32) ((sp44->unk34 + arg2) & 0xF);
        sp44->unk30 = (u32) (sp44->unk30 + arg2);
        sp44->unk3C = (s32) (sp44->unk3C + (sp70 * 9));
        return sp7C;
    }
    sp5C = sp70 * 0x10;
    temp_t0_2 = sp44->unk20;
    sp68 = (sp44->unk3C + sp6C) - (temp_t0_2->unk0 + temp_t0_2->unk4);
    if (sp68 < 0) {
        sp68 = 0;
    }
    sp60 = (sp68 / 9) * 0x10;
    if ((sp5C + sp54) < sp60) {
        sp60 = sp5C + sp54;
    }
    sp6C -= sp68;
    if ((sp60 - (sp60 & 0xF)) < arg2) {
        sp4C = 1;
        sp7C = alLoadParam(sp7C, sp44, sp5C - sp60, sp6C, (s32) *arg1, (s32) sp7A, sp44->unk38);
        if (sp44->unk34 != 0) {
            *arg1 += sp44->unk34 * 2;
        } else {
            *arg1 += 0x20;
        }
        sp44->unk34 = (s32) ((sp44->unk34 + arg2) & 0xF);
        sp44->unk30 = (u32) (sp44->unk30 + arg2);
        sp44->unk3C = (s32) (sp44->unk3C + (sp70 * 9));
    } else {
        sp44->unk34 = 0;
        sp44->unk3C = (s32) (sp44->unk3C + (sp70 * 9));
    }
    if (sp60 != 0) {
        sp44->unk34 = 0;
        if (sp4C != 0) {
            sp64 = ((sp54 + sp5C) - sp60) * 2;
        } else {
            sp64 = 0;
        }
        temp_t3 = sp7C;
        sp7C = temp_t3 + 8;
        sp38 = temp_t3;
        sp38->unk0 = (s32) (((*arg1 + sp64) & 0xFFFFFF) | 0x02000000);
        sp38->unk4 = (s32) (sp60 * 2);
    }
    return sp7C;
}
