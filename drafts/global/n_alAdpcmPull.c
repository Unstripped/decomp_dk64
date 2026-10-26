// n_alAdpcmPull (src/global/144E00.c): stage 3: exact 0x80 frame and s0 loop-boundary boolean; canonical arg2 > nSam loop comparison improves isolated score 41880 to 38193; remaining scratch-register expression shapes
AdpcmNMAcmd *n_alAdpcmPull(AdpcmNMLoadFilter *arg0, s16 *arg1, s32 arg2, AdpcmNMAcmd *arg3) {
    AdpcmNMAcmd *sp7C;
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
    AdpcmNMLoadFilter *sp44;
    AdpcmNMAcmd *sp40;
    AdpcmNMAcmd *sp3C;
    AdpcmNMAcmd *sp38;

    sp7C = arg3;
    sp4C = 0;
    sp48 = 0;
    sp44 = arg0;
    if (arg2 == 0) {
        return sp7C;
    }
    sp7A = 0;
    sp40 = sp7C++;
    sp40->w0 = (sp44->unk24 & 0xFFFFFF) | 0x0B000000;
    sp40->w1 = ((u32)sp44->unk20->loop + 8) & 0x1FFFFFFF;
    sp48 = ((u32)sp44->unk18 < (u32)(sp44->unk30 + arg2)) && sp44->unk1C;
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
    sp70 = (sp74 + 0xF) >> 4;
    sp6C = sp70 * 9;
    if (sp48 != 0) {
        sp7C = alLoadParam(sp7C, sp44, sp74, sp6C, *arg1, sp7A, sp44->unk38);
        if (sp44->unk34 != 0) {
            *arg1 += sp44->unk34 * 2;
        } else {
            *arg1 += 0x20;
        }
        sp44->unk34 = sp44->unk14 & 0xF;
        sp44->unk3C = sp44->unk20->unk0 + ((u32)sp44->unk14 >> 4) * 9 + 9;
        sp44->unk30 = sp44->unk14;
        sp50 = *arg1;
        if (arg2 > sp5C) {
            do {
                arg2 -= sp5C;
                sp58 = (((sp70 + 1) << 5) + sp50 + 0x10) & ~0x1F;
                sp50 += sp5C * 2;
                if ((sp44->unk1C != -1) && (sp44->unk1C != 0)) {
                    sp44->unk1C = sp44->unk1C - 1;
                }
                sp5C = ((u32)arg2 < (u32)(sp44->unk18 - sp44->unk14)) ? arg2 : sp44->unk18 - sp44->unk14;
                sp74 = (sp5C + sp44->unk34) - 0x10;
                if (sp74 < 0) {
                    sp74 = 0;
                }
                sp70 = (sp74 + 0xF) >> 4;
                sp6C = sp70 * 9;
                sp7C = alLoadParam(sp7C, sp44, sp74, sp6C, sp58, sp7A, sp44->unk38 | 2);
                sp3C = sp7C++;
                sp3C->w0 = (((sp44->unk34 * 2) + sp58) & 0xFFFFFF) | 0x0A000000;
                sp3C->w1 = ((sp50 & 0xFFFF) << 0x10) | ((sp5C * 2) & 0xFFFF);
            } while (arg2 > sp5C);
        }
        sp44->unk34 = (sp44->unk34 + arg2) & 0xF;
        sp44->unk30 = sp44->unk30 + arg2;
        return sp7C;
    }
    sp5C = sp70 << 4;
    sp68 = (sp44->unk3C + sp6C) - (sp44->unk20->unk0 + sp44->unk20->unk4);
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
        sp7C = alLoadParam(sp7C, sp44, sp5C - sp60, sp6C, *arg1, sp7A, sp44->unk38);
        if (sp44->unk34 != 0) {
            *arg1 += sp44->unk34 * 2;
        } else {
            *arg1 += 0x20;
        }
        sp44->unk34 = (sp44->unk34 + arg2) & 0xF;
        sp44->unk30 = sp44->unk30 + arg2;
        sp44->unk3C = sp44->unk3C + (sp70 * 9);
    } else {
        sp44->unk34 = 0;
        sp44->unk3C = sp44->unk3C + (sp70 * 9);
    }
    if (sp60 != 0) {
        sp44->unk34 = 0;
        if (sp4C != 0) {
            sp64 = ((sp54 + sp5C) - sp60) * 2;
        } else {
            sp64 = 0;
        }
        sp38 = sp7C++;
        sp38->w0 = ((*arg1 + sp64) & 0xFFFFFF) | 0x02000000;
        sp38->w1 = sp60 * 2;
    }
    return sp7C;
}
