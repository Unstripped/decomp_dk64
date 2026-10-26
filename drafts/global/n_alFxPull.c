// n_alFxPull (src/global/141EF0.c): stage 3: built .text 5776 bytes vs expected 5808; remaining diff includes delay-flag loop preheader evaluation/order and swap-branch delay slot
Acmd *n_alFxPull(s32 arg0, Acmd *arg1, s32 arg2) {
    Acmd *sp84;
    FxPullRing *sp80;
    s16 sp7E;
    s16 sp7C;
    s16 sp7A;
    s16 sp78;
    s16 sp76;
    u8 *sp70;
    u8 *sp6C;
    s32 sp68;
    u8 *sp64;
    FxPullLine *sp60;
    s32 sp5C;
    s32 sp58;
    u32 sp54;
    Acmd *sp50;
    Acmd *sp4C;
    Acmd *sp48;
    s16 sp46;
    Acmd *sp40;
    Acmd *sp3C;
    Acmd *sp38;
    u32 sp34;
    Acmd *sp30;
    Acmd *sp2C;
    Acmd *sp28;
    Acmd *sp24;

    sp84 = arg1;
    sp80 = D_807563E4->unk34[arg2].unk20;
    sp64 = NULL;
    sp58 = 1;
    sp84 = n_alAuxBusPull(arg0, arg1, arg2, &sp58);
    sp78 = 0x7C0;
    sp76 = 0x930;
    sp7C = 0;
    sp7A = 0x170;
    if (D_807FF0F4[arg2] == 0) {
        sp50 = sp84++;
        sp50->words.w0 = 0x0C00C000;
        sp50->words.w1 = (sp78 & 0xFFFF) | 0x07C00000;
        sp4C = sp84++;
        sp4C->words.w0 = 0x0C004000;
        sp4C->words.w1 = (sp78 & 0xFFFF) | 0x09300000;
    }
    sp84 = _n_saveBuffer(sp80, 0, sp80->unk28[0], sp78, sp84);
    if (D_807FF0F4[arg2] != 0) {
        sp84 = _n_saveBuffer(sp80, 1, sp80->unk28[1], 0x930, sp84);
    }
    (void)*(volatile u8 *)&D_807FF0F4[arg2];
    for (sp54 = 0; D_807FF0F4[arg2] >= sp54; sp54++) {
        sp48 = sp84++;
        sp48->words.w0 = (sp76 & 0xFFFFFF) | 0x02000000;
        sp48->words.w1 = 0x170;
        if ((s32)sp80->unk8 > (sp7E = 0)) {
            do {
                sp60 = sp80->unk4 + sp7E;
                sp70 = sp80->unk28[sp54] + ((-sp60->unk0) * 2);
                sp6C = sp80->unk28[sp54] + ((-sp60->unk4) * 2);
                if ((D_807FF0F6[arg2] != 0) && (D_807FF0F4[arg2] != 0)) {
                    sp60->unk8 = -sp60->unk8;
                    sp60->unkA = -sp60->unkA;
                }
                if (sp70 == sp64) {
                    sp46 = sp7A;
                    sp7A = sp7C;
                    sp7C = sp46;
                } else {
                    sp84 = _n_loadBuffer(sp80, sp54, sp70, sp7C, 0xB8, sp84);
                }
                sp84 = _n_loadOutputBuffer(sp80, sp60, sp54, sp7A, sp84);
                if (sp60->unk8 != 0) {
                    sp40 = sp84++;
                    sp40->words.w0 = ((u16)sp60->unk8 & 0xFFFF) | 0x0C000000;
                    sp40->words.w1 = ((sp7C & 0xFFFF) << 16) | (sp7A & 0xFFFF);
                    if ((sp60->unk24 == 0) && (sp60->unk20 == 0)) {
                        sp84 = _n_saveBuffer(sp80, sp54, sp6C, sp7A, sp84);
                    }
                }
                if (sp60->unkA != 0) {
                    sp3C = sp84++;
                    sp3C->words.w0 = ((u16)sp60->unkA & 0xFFFF) | 0x0C000000;
                    sp3C->words.w1 = ((sp7A & 0xFFFF) << 16) | (sp7C & 0xFFFF);
                    sp84 = _n_saveBuffer(sp80, sp54, sp70, sp7C, sp84);
                }
                if (sp60->unk20 != 0) {
                    sp84 = _n_filterBuffer(sp60->unk20, sp54, sp7A, sp84);
                }
                if (sp60->unk24 == 0) {
                    sp84 = _n_saveBuffer(sp80, sp54, sp6C, sp7A, sp84);
                }
                if (sp60->unkC != 0) {
                    if (D_807FF0F4[arg2] != 0) {
                        sp38 = sp84++;
                        sp38->words.w0 = ((u16)sp60->unkC & 0xFFFF) | 0x0C000000;
                        sp38->words.w1 = ((sp7A & 0xFFFF) << 16) | (sp76 & 0xFFFF);
                    } else {
                        sp34 = (u32)((f32)sp60->unkC * 1.4142f);
                        if (sp34 >= 0x8000) {
                            sp34 = 0x7FFF;
                        }
                        sp30 = sp84++;
                        sp30->words.w0 = (sp34 & 0xFFFF) | 0x0C000000;
                        sp30->words.w1 = ((sp7A & 0xFFFF) << 16) | (sp76 & 0xFFFF);
                    }
                }
                sp64 = sp80->unk28[sp54] + (sp60->unk4 * 2);
            } while (++sp7E < (s32)sp80->unk8);
        }
        if ((D_807FF0F4[arg2] != 0) && (sp54 == 0)) {
            sp84 = _n_loadBuffer(sp80, 1, sp80->unk28[1], sp78, 0xB8, sp84);
            if (D_807FF0F6[arg2] != 0) {
                sp2C = sp84++;
                sp2C->words.w0 = 0x0C005A82;
                sp2C->words.w1 = ((sp76 & 0xFFFF) << 16) | 0x650;
            } else {
                sp28 = sp84++;
                sp28->words.w0 = 0x0C005A82;
                sp28->words.w1 = ((sp76 & 0xFFFF) << 16) | 0x4E0;
            }
        }
        sp24 = sp84++;
        sp24->words.w0 = (sp76 & 0xFFFFFF) | 0x0A000000;
        sp24->words.w1 = 0x07C00170;
        sp80->unk28[sp54] += 0x170;
        if ((u32)(sp80->unk20[sp54] + (sp80->unk0 * 2)) < (u32)sp80->unk28[sp54]) {
            sp80->unk28[sp54] -= sp80->unk0 * 2;
        }
    }
    return sp84;
}
