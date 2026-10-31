// func_8002CD64 (src/arcade/0.c): stage 5, text diff 122 (723 vs 723 lines) with 5 FAKE dead stmts (C6F8/A76C/C71F compares; c1 = same without them is text 166, a0/a1 swapped). Structure now matches target (local ptr e, P-struct cond, if(unk1C&0x80){break;}else{...} layout, break at end of unk1C>0 arm, rand-first case 7, v merged into sp3C). Remaining: arm A fp temp naming (f8/f16/f10 vs f10/f8/f16), C6F8 reloaded at A-end/tail sites (target keeps it in a0 from the cond: pointer f32 stores kill the s32 C6F8 load in ours).
extern s32 D_8004C6FC;
extern s32 D_8004C704;
void func_8002CD64(s32 arg0) {
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
            e->unk10 = (f32)((f64)e->unk10 + 0.2);
            e->unk8 = (f32)(1 - e->unk1A * 2);
            if (e->unk4 < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCD0[D_8004C71F].unk19 != 5)))) {
                if (e->unk1C & 0x80) {
                    break;
                } else {
                    e->unk1C = e->unk1C & 0xF;
                    if (e->unk1C > 0) {
                        e->unk1C = e->unk1C - 1;
                        e->unk19 = 5;
                        e->unk4 = e->unk4 + 1.0f;
                        e->unkC = 1.0f;
                        e->unk8 = 0.0f;
                        e->unk0 = (f32)D_8004C6E0;
                        break;
                    } else {
                        e->unk1C = e->unk1C | 0x80;
                        goto L_tail2;
                    }
                }
            } else {
                if (!(e->unk1C & 0x47)) {
                    e->unk1C = (4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand()) | 0x40;
                }
            L_tail2:
                if ((f32)sp3C - e->unk4 < 3.0f) {
                    e->unk4 = (f32)sp3C;
                } else {
                    e->unk19 = 3;
                    e->unkC = 0.0f;
                    e->unk8 = e->unk8 / 2;
                }
            }
            break;
        case 3:
            e->unk10 = (f32)((f64)e->unk10 + 0.2);
            e->unk4 = e->unk4 + e->unkC;
            e->unkC = (f32)((f64)e->unkC + 0.06);
            if ((f32)sp3C < e->unk4 && e->unk4 - (f32)sp3C < 3.0f) {
                e->unk4 = (f32)sp3C;
                e->unkC = -e->unkC / 3.0f;
                if ((f64)e->unkC > -0.2) {
                    e->unk19 = 2;
                }
            }
            break;
        case 5:
            e->unk10 = (f32)((f64)e->unk10 + 0.3);
            e->unk4 = e->unk4 + e->unkC;
            if ((f32)(D_8004C6E8 - 1) < e->unk4) {
                e->unk1A = 1 - e->unk1A;
                e->unk19 = 2;
                e->unk4 = (f32)sp3C;
                e->unk8 = (f32)(1 - e->unk1A * 2);
            }
            break;
        case 7:
            e->unk10 = (f32)((f64)e->unk10 + 0.3);
            e->unk4 = e->unk4 + e->unkC;
            e->unkC = (f32)((f64)e->unkC + 0.06);
            sp3C = arcadeCheckPlayerCollision((s32)e->unk0, (s32)e->unk4);
            if ((f32)sp3C < e->unk4 && e->unk4 - (f32)sp3C < 8.0f && e->unk1C < D_8004C6F8) {
                e->unk1C = D_8004C6F8;
                e->unk4 = (f32)sp3C;
                e->unkC = 0.0f;
                if (e->unk1D != 2) {
                    e->unk8 = (f32)((((f64)arcadeRand() - 16384.0) * arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C)) / 40000.0 + (f64)(-e->unk8) * 0.2);
                }
                if (e->unk4 > 230.0f) {
                    e->unk19 = 3;
                    e->unk1A = 1;
                    e->unk8 = -1.0f;
                    e->unkC = -0.7f;
                }
            }
            break;
        }
        if (D_8004BCD0[D_8004C71F].unk1C >= D_8004C6F8 || e->unk1D != 0) {
            if (270.0f < e->unk0) {
                e->unk1A = 1;
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
            if (D_8004A76C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (e->unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                sp3C = arcadeFindEntityByType(0x13);
                if (sp3C < 0) {
                    sp3C = arcadeFindFreeEntity();
                    D_8004BCD0[sp3C] = D_8004A3F8;
                }
                D_8004BCE9[sp3C << 5] = 3;
                e->unk18 = 0;
            } else {
                if (D_8004C6F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                e->unk18 = 0;
                if (D_8004C6F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
        }
        if (D_8004C71F) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_8004C6F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (e->unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - e->unk0 < 8.0f) {
            if (e->unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - e->unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(arg0);
    }
}
