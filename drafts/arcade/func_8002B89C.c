// func_8002B89C (src/arcade/0.c): stage 4: frame 0x48 + no callee-saved match; 1232 vs 1230 insns, ~64 norm diff lines, ALL from uopt coloring the lda of D_8004BC80/BC84 (lui+addiu+lw 0(reg)) in the case-5 else-if arm 2 and the post-switch tail where target keeps plain lui/lw + lui at/sw. Tried: struct/array decl (merges BC80/BC84 lda), volatile, statement order, += forms, goto arms, nested ifs, local temp for BC84, pointer local E (worse). Keys that matched: break inside each case-2 arm (replicates i spill store per arm), (B|C)|A operand order of case-5 cond, E.unkC+E.unk4 operand order, E.unk4=(f32)coll before unk10-=1.0 in case 4, D_8004BC84 via local (reuse pad slot).
extern s32 D_8004BC80;
extern s32 D_8004BC84;
extern s32 D_8004C6FC;
extern s32 D_8004C700;
extern s32 D_8004C704;
extern s32 D_80770DFC;
extern ArcadeEntity D_8004A5F8;
extern u8 D_800383B8[];
extern u8 D_800385C0[];
extern u8 D_8003B180[];
void func_8002B390(s32);
void n_alSndpPostEvent(s32, s32, s32);
#define E D_8004BCD0[arg0]
#define P D_8004BCD0[D_8004C71F]
void func_8002B89C(s32 arg0) {
    f32 sp44;
    s32 coll;
    s32 i;
    s32 n;
    s32 phase;

    if (E.unk19 == 8 || D_8004C71D == 0) {
        if (E.unk19 == 2) {
            arcadeCheckPlayerCollision((s32)E.unk0, (s32)E.unk4);
            if (E.unk8 < 0.0f) {
                E.unk1A = E.unk1A & 1;
            } else if (E.unk8 > 0.0f) {
                E.unk1A = E.unk1A | 2;
            }
            if (((*(u16 *)D_807ECDE8 & 0x200) || (s8)D_807ECDE8[2] < -0x14) && (f32)D_8004C6F0 < E.unk0) {
                D_8004BC80 += 3;
                E.unk8 = -0.7f;
                E.unk10 = (f32)((f64)E.unk10 + 0.3);
            } else if (((*(u16 *)D_807ECDE8 & 0x100) || (s8)D_807ECDE8[2] >= 0x15) && E.unk0 < (f32)D_8004C6F4) {
                D_8004BC80 += 3;
                E.unk8 = 0.7f;
                E.unk10 = (f32)((f64)E.unk10 + 0.3);
            } else {
                E.unk8 = 0.0f;
            }
            if ((D_807ECD48 & 0xE000) && D_8004C710 == 0) {
                n_alSndpPlay(D_8076D1F8, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk10 = 0.0f;
                E.unkC = -1.2f;
                E.unk8 = (f32)((f64)E.unk8 * 0.65);
                E.unk1D = (u32)E.unk4;
                E.unk19 = 3;
            }
        }
        if (E.unk4 < (f32)(arcadeCheckPlayerCollision((s32)(E.unk0 + E.unk8), (s32)E.unk4) + 3)) {
            E.unk0 = E.unk8 + E.unk0;
        } else {
            E.unk8 = 0.0f;
        }
        if (E.unk19 != 8 && D_8004C722 == 3 &&
            ((76.0f < E.unk0 && E.unk0 < 100.0f) || (140.0f < E.unk0 && E.unk0 < 164.0f)) &&
            ((E.unk4 < 116.0f && 90.0f < E.unk4) || 239.0f < E.unk4)) {
            arcadeKillPlayer();
            return;
        }
        D_8004C700 = arcadeCheckStageLadders((s32)E.unk0, (s32)E.unk4);
        coll = arcadeCheckPlayerCollision((s32)E.unk0, (s32)E.unk4);
        D_8004C6FC = D_8004C6F8;
        switch (E.unk19) {
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_8004C6F8 == i) {
                    P.unk0 += (f32)D_8004A308[i];
                }
            }
            if (E.unk0 <= (f32)(D_8004C6F0 - 1)) {
                E.unk0 = (f32)D_8004C6F0;
            }
            if ((f32)(D_8004C6F4 + 1) <= E.unk0) {
                E.unk0 = (f32)D_8004C6F4;
            }
            if ((f32)D_8004C6EC < E.unk4 &&
                ((((s8)D_807ECDE8[3] >= 0x15) | (*(u16 *)D_807ECDE8 & 0x800)) != 0) &&
                (s8)D_807ECDE8[2] < 0x29 && (s8)D_807ECDE8[2] >= -0x28 &&
                !(*(u16 *)D_807ECDE8 & 0x300) && D_8004C710 == 0) {
                E.unk19 = 5;
                E.unk8 = 0.0f;
                E.unk4 = E.unk4 - 1.0f;
                E.unk0 = (f32)D_8004C6E0;
                break;
            } else if (E.unk4 < (f32)D_8004C6E8 && (f32)D_8004C6EC <= E.unk4 &&
                       !(*(u16 *)D_807ECDE8 & 0x300) &&
                       (s8)D_807ECDE8[2] < 0x29 && (s8)D_807ECDE8[2] >= -0x28 &&
                       ((((s8)D_807ECDE8[3] < -0x14) | (*(u16 *)D_807ECDE8 & 0x400)) != 0) &&
                       D_8004C710 == 0) {
                E.unk19 = 5;
                E.unk8 = 0.0f;
                E.unk4 = E.unk4 + 1.0f;
                E.unk0 = (f32)D_8004C6E0;
                break;
            } else {
                if ((f32)coll - E.unk4 < 2.0f) {
                    E.unk4 = (f32)coll;
                } else {
                    E.unk19 = 3;
                    E.unk8 = 0.0f;
                    E.unkC = 0.0f;
                    E.unk1D = (u32)E.unk4;
                }
            }
            break;
        case 5:
            if ((f32)coll == E.unk4 &&
                (((((s8)D_807ECDE8[2] >= 0x15) | ((s8)D_807ECDE8[2] < -0x14)) | (*(u16 *)D_807ECDE8 & 0x300)) ||
                 (D_8004C6F8 == 2 && D_8004A308[2] != 0) ||
                 (D_8004C6F8 == 1 && D_8004A308[1] != 0) ||
                 (D_8004C6F8 == 3 && D_8004A308[3] != 0))) {
                E.unk19 = 2;
            } else if ((f32)coll == E.unk4 && (D_807ECD48 & 0xE000)) {
                n_alSndpPlay(D_8076D1F8, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk10 = 0.0f;
                E.unkC = -1.2f;
                E.unk8 = (f32)((f64)E.unk8 * 0.65);
                E.unk19 = 3;
                E.unk1D = (u32)E.unk4;
            } else {
                if (E.unk4 < (f32)D_8004C6EC) {
                    E.unk4 = (f32)((f64)E.unk4 + 0.2);
                    if ((f32)D_8004C6EC - E.unk4 > 10.0f) {
                        E.unk4 = (f32)(D_8004C6EC - 10);
                    }
                    if ((f32)D_8004C6EC < E.unk4) {
                        E.unk4 = (f32)D_8004C6EC;
                    }
                } else {
                    if ((f32)D_8004C6EC < E.unk4 &&
                        ((((s8)D_807ECDE8[3] >= 0x15) | (*(u16 *)D_807ECDE8 & 0x800)) != 0)) {
                        E.unkC = -0.5f;
                        D_8004BC80 += 2;
                    } else if (E.unk4 < (f32)D_8004C6E8 &&
                               ((((s8)D_807ECDE8[3] < -0x14) | (*(u16 *)D_807ECDE8 & 0x400)) != 0)) {
                        E.unkC = 0.5f;
                        D_8004BC80 += 2;
                    } else {
                        E.unkC = 0.0f;
                    }
                    E.unk4 = E.unkC + E.unk4;
                    E.unk10 = E.unkC + E.unk10;
                }
            }
            break;
        case 3:
            if ((f32)D_8004C6F4 < E.unk0) {
                E.unk0 = (f32)D_8004C6F4;
                if ((f64)E.unkC < 1.8) {
                    E.unk1A = E.unk1A & 1;
                    E.unk8 = -E.unk8;
                    E.unkC = -E.unkC;
                }
            } else if (E.unk0 < (f32)D_8004C6F0) {
                E.unk0 = (f32)D_8004C6F0;
                if ((f64)E.unkC < 1.8) {
                    E.unk1A = E.unk1A | 2;
                    E.unk8 = -E.unk8;
                    E.unkC = -E.unkC;
                }
            }
            E.unk4 = E.unkC + E.unk4;
            E.unkC = (f32)((f64)E.unkC + 0.06);
            if (0.0f <= E.unkC && (f64)E.unkC < 0.06) {
                n = 0;
                for (i = 0; i < 0x50; i++) {
                    if (D_8004BCD0[i].unk18 == 1 || D_8004BCD0[i].unk18 == 2) {
                        if (arcadeAbs((s32)(D_8004BCD0[i].unk0 - E.unk0)) < 0xD) {
                            if (D_8004BCD0[i].unk4 - E.unk4 < 24.0f && E.unk4 < D_8004BCD0[i].unk4) {
                                n++;
                            }
                        }
                    }
                }
                if (n != 0) {
                    i = func_800247F0();
                    D_8004BCD0[i] = D_8004A5F8;
                    D_8004BCD0[i].unk0 = E.unk0;
                    D_8004BCD0[i].unk4 = E.unk4 + 9.0f;
                    if (n == 1) {
                        arcadeAddScore(0x64);
                    } else if (n == 2) {
                        D_8004BCD0[i].unk14 = D_800383B8;
                        arcadeAddScore(0x12C);
                    } else {
                        D_8004BCD0[i].unk14 = D_800385C0;
                        arcadeAddScore(0x1F4);
                    }
                }
            }
            if (E.unk4 - (f32)(u32)E.unk1D > 15.0f) {
                n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk1D = 0xFF;
            }
            if ((f64)E.unkC > 2.5) {
                E.unkC = 2.5f;
            }
            if ((f32)coll < E.unk4 && E.unk4 - (f32)coll < 3.0f) {
                E.unk4 = (f32)coll;
                if (E.unk1D == 0xFF) {
                    arcadeKillPlayer();
                } else {
                    E.unk19 = 4;
                    E.unkC = 0.0f;
                    E.unk8 = 0.0f;
                    E.unk10 = 4.0f;
                }
            }
            break;
        case 4:
            E.unk4 = (f32)coll;
            E.unk10 = E.unk10 - 1.0f;
            if (E.unk10 == 0.0f) {
                E.unk19 = 2;
            }
            break;
        case 8:
            E.unk10 = (f32)((f64)E.unk10 + 0.125);
            if (E.unk10 == 8.0f) {
                n_alSndpPlay(D_8076D1F8, 0x54, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            break;
        }
        if (D_8004BC80 >= 0x24) {
            D_8004BC80 = 0;
            phase = D_8004BC84 + 1;
            if (phase == 7) {
                phase = 0;
            }
            D_8004BC84 = phase;
            if (phase & 1) {
                sp44 = 1.0f;
            } else {
                sp44 = 0.7071120143f;
            }
            n_alSndpPlay(D_8076D1F8, 0x40, 0x7FFF, 0x3F, 1.0f, 0, (s32)&D_80770DFC);
            n_alSndpPostEvent(D_80770DFC, 0x10, *(s32 *)&sp44);
        }
        coll = arcadeCheckPlayerCollision((s32)E.unk0, (s32)E.unk4);
        E.unk1C = D_8004C6F8;
        D_8004C704 = (s32)(E.unk4 - (f32)D_8004C6E4);
        if (D_8004C71E < 0 && E.unk19 != 8) {
            arcadeKillPlayer();
        }
        if (D_8004C6F8 == 0 && (f32)coll == E.unk4) {
            n_alSndpPlay(D_8076D1F8, 0x4C, 0x7FFF, 0x3F, 1.0f, 0, 0);
            arcadeStopSound(0);
            if (D_8004C722 == 1) {
                i = arcadeFindEntityByType(0x16);
            } else if (D_8004C722 == 3) {
                i = arcadeFindEntityByType(0x18);
            } else if (D_8004C722 == 4) {
                i = arcadeFindEntityByType(0x19);
            }
            D_8004BCD0[i].unk19 = 5;
            if (D_8004C722 != 4) {
                D_8004BCD0[i].unk18 = 0x16;
            }
            D_8004BCD0[i].unk10 = 0.0f;
            D_8004C71D = 3;
            E.unk14 = D_8003B180;
            E.unk1A = 0;
            return;
        }
        if (E.unk19 != 0) {
            func_8002B390(arg0);
        }
    }
}
#undef E
#undef P
