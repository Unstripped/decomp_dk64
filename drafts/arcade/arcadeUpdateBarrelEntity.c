// arcadeUpdateBarrelEntity (src/arcade/0.c): Leftovers6 Arcade: stage 4 (count 614 insns exact, tail2 PRE hoist matches) but full diff 241 with 9 FAKE dead tests; previous best (117 diff, 610 insns = 4 short, 5 fakes) kept in .scratch/Arcade/arcadeUpdateBarrelEntity_best.c. FINDING: the 4-insn shortfall is ONE structural difference: in the target the PRE insertion of the post-switch loads (lbu C71F; sll 5; addu a1=&BCD0[C71F]; lw a0=C6F8) sits at the HEAD of the L_tail2 block (before sub.s/c.lt.s), so the tail2 if/else arms have no merge block and the 1.0f const (lui at,0x3f80; mtc1 f2) is duplicated into both arms (+2 insns); ours puts the loads in the merge block after the arms. Metric used: idx of 5th 'R LO16 C71F' minus idx of 3rd c.lt.s == -14 and 614 insns. Bit-flip SA over 106 e->/D_8004BCD0[arg0]. spellings (20k evals x3), brk in arms, no-goto restructure, tail2-head dead tests (single/pairs) did NOT reach it; a dead-test hill climb (C71F / D_8004BCD0[D_8004C71F].unk1C / C6FC in tail2 head, else-arm, call block) does, but perturbs earlier colouring (a2 for C6F8 hi at the switch dispatch). Real source likely has natural occurrences of D_8004BCD0[D_8004C71F] / D_8004C6F8 inside case 2 tail.
extern s32 D_8004C6FC;
extern s32 D_8004C704;
extern s32 D_8004C6FC;
extern s32 D_8004C704;
void arcadeUpdateBarrelEntity(s32 arg0) {
    s32 sp3C;
    ArcadeEntity *e;

    if (D_8004C71D == 0) {
        if (D_8004BCD0[arg0].unk19 == 0 || D_8004BCD0[arg0].unk19 == 1) {
            arcadeUpdateEntitySprite(arg0);
            return;
        }
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
        sp3C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        arcadeCheckStageLadders((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        e = &D_8004BCD0[arg0];
        switch (e->unk19) {
        case 2:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            if (e->unk4 < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCD0[D_8004C71F].unk19 != 5)))) {
                if (e->unk1C & 0x80) {
                    break;
                } else {
                    if (sp3C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C & 0xF;
                    if (D_8004BCD0[arg0].unk1C > 0) {
                        D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C - 1;
                        D_8004BCD0[arg0].unk19 = 5;
                        D_8004BCD0[arg0].unk8 = 0.0f;
                        D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + 1.0f;
                        D_8004BCD0[arg0].unkC = 1.0f;
                        D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
                        break;
                    } else {
                        D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C | 0x80;
                        goto L_tail2;
                    }
                }
            } else {
                if (!(D_8004BCD0[arg0].unk1C & 0x47)) {
                    if (D_8004BCD0[D_8004C71F].unk1C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_8004BCD0[arg0].unk1C = (4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand()) | 0x40;
                }
            L_tail2:
                if (D_8004C6FC != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (D_8004C71F) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if ((f32)sp3C - D_8004BCD0[arg0].unk4 < 3.0f) {
                    e->unk4 = (f32)sp3C;
                } else {
                    if (e->unk4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (D_8004BCD0[D_8004C71F].unk1C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    e->unk19 = 3;
                    if (D_8004C6FC && D_8004C71F) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_8004BCD0[arg0].unkC = 0.0f;
                    D_8004BCD0[arg0].unk8 = D_8004BCD0[arg0].unk8 / 2;
                }
            }
            break;
        case 3:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            e->unk4 = e->unk4 + e->unkC;
            e->unkC = (f32)((f64)e->unkC + 0.06);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp3C < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = -D_8004BCD0[arg0].unkC / 3.0f;
                if ((f64)D_8004BCD0[arg0].unkC > -0.2) {
                    e->unk19 = 2;
                }
            }
            break;
        case 5:
            e->unk10 = (f32)((f64)e->unk10 + 0.3);
            e->unk4 = e->unk4 + e->unkC;
            if ((f32)(D_8004C6E8 - 1) < e->unk4) {
                e->unk1A = 1 - e->unk1A;
                D_8004BCD0[arg0].unk19 = 2;
                e->unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
            break;
        case 7:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            e->unk4 = e->unk4 + e->unkC;
            e->unkC = (f32)((f64)e->unkC + 0.06);
            sp3C = arcadeCheckPlayerCollision((s32)e->unk0, (s32)e->unk4);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp3C < 8.0f && D_8004BCD0[arg0].unk1C < D_8004C6F8) {
                D_8004BCD0[arg0].unk1C = D_8004C6F8;
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = 0.0f;
                if (e->unk1D != 2) {
                    e->unk8 = (f32)((((f64)arcadeRand() - 16384.0) * arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C)) / 40000.0 + (f64)(-e->unk8) * 0.2);
                }
                if (D_8004BCD0[arg0].unk4 > 230.0f) {
                    D_8004BCD0[arg0].unk19 = 3;
                    D_8004BCD0[arg0].unk1A = 1;
                    D_8004BCD0[arg0].unk8 = -1.0f;
                    e->unkC = -0.7f;
                }
            }
            break;
        }
        if (D_8004BCD0[D_8004C71F].unk1C >= D_8004C6F8 || e->unk1D != 0) {
            if (270.0f < D_8004BCD0[arg0].unk0) {
                D_8004BCD0[arg0].unk1A = 1;
                if (D_8004C71F && D_8004C71F) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                e->unk8 = (f32)(1 - e->unk1A * 2);
            } else if (e->unk0 < 50.0f) {
                e->unk1A = 0;
                e->unk8 = (f32)(1 - e->unk1A * 2);
            }
        }
        if (278.0f < e->unk0 || e->unk0 < 2.0f) {
            e->unk18 = 0;
        }
        if ((e->unk4 > 242.0f) & (e->unk0 < 74.0f)) {
            if (D_8004BCD0[arg0].unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                sp3C = arcadeFindEntityByType(0x13);
                if (sp3C < 0) {
                    sp3C = arcadeFindFreeEntity();
                    D_8004BCD0[sp3C] = D_8004A3F8;
                }
                D_8004BCE9[sp3C << 5] = 3;
                e->unk18 = 0;
            } else {
                D_8004BCD0[arg0].unk18 = 0;
            }
            if (D_8004C6FC && D_8004C704) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (e->unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - e->unk0 < 8.0f) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(arg0);
    }
}
