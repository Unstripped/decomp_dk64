// func_8002CD64 (src/arcade/0.c): stage 4, unchanged body from previous pass (score 292, 710 vs 723 lines). New diagnosis: target emits 'addu a1' (player ptr) at 8 sites 77,157,190,253,343,402,543,681; ours 7 (77,154,236,326,385,526,668). Missing site = end of case-2 'unk1C>0' arm (target 190, a1 + 1.0f f2 reload there); in ours a1 is computed once in the delay slot of 'bnez (unk1C&0x80)' shared by arms A and B, because the dead P-compare sits before that branch. Swept: all subsets of arm-end (break) positions x 4 dead forms, positions P1..P4 inside the case-2 block (end of arm B, else of the 0x80 test, arm B start) x 4 forms: none improves. 24-way void->s32 toggles of arcadeKillPlayer/arcadeUpdateEntitySprite no effect.
extern s32 D_8004C6FC;
extern s32 D_8004C704;
void func_8002CD64(s32 arg0) {
    s32 sp3C;
    s32 v;

    if (D_8004C71D == 0) {
        if (D_8004BCD0[arg0].unk19 == 0 || D_8004BCD0[arg0].unk19 == 1) {
            arcadeUpdateEntitySprite(arg0);
            return;
        }
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
        sp3C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        arcadeCheckStageLadders((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        switch (D_8004BCD0[arg0].unk19) {
        case 2:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            if (D_8004BCD0[arg0].unk4 < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCE9[D_8004C71F << 5] != 5)))) {
                     if (D_8004BCD0[D_8004C71F].unk0 < 1.0f) {}
                if (!(D_8004BCD0[arg0].unk1C & 0x80)) {
                    D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C & 0xF;
                    if (D_8004BCD0[arg0].unk1C > 0) {
                        D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C - 1;
                        D_8004BCD0[arg0].unk19 = 5;
                        D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + 1.0f;
                        D_8004BCD0[arg0].unkC = 1.0f;
                        D_8004BCD0[arg0].unk8 = 0.0f;
                        D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
                    } else {
                        D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C | 0x80;
                        goto L_tail2;
                    }
                }
            } else {
                if (D_8004BCD0[arg0].unk1C == 0) {}
                if (!(D_8004BCD0[arg0].unk1C & 0x47)) {
                    v = 4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand();
                    if (D_8004BCD0[D_8004C71F].unk0 < 1.0f) {}
                    D_8004BCD0[arg0].unk1C = v | 0x40;
                }
            L_tail2:
                if ((f32)sp3C - D_8004BCD0[arg0].unk4 < 3.0f) {
                    D_8004BCD0[arg0].unk4 = (f32)sp3C;
                } else {
                    D_8004BCD0[arg0].unk19 = 3;
                    D_8004BCD0[arg0].unkC = 0.0f;
                    D_8004BCD0[arg0].unk8 = D_8004BCD0[arg0].unk8 / 2;
                }
            }
            break;
        case 3:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)D_8004BCD0[arg0].unkC + 0.06);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp3C < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = -D_8004BCD0[arg0].unkC / 3.0f;
                if ((f64)D_8004BCD0[arg0].unkC > -0.2) {
                    D_8004BCD0[arg0].unk19 = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            if ((f32)(D_8004C6E8 - 1) < D_8004BCD0[arg0].unk4) {
                v = 1 - D_8004BCD0[arg0].unk1A;
                D_8004BCD0[arg0].unk1A = v;
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - (u8)v * 2);
            }
            break;
        case 7:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)D_8004BCD0[arg0].unkC + 0.06);
            sp3C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp3C < 8.0f && D_8004BCD0[arg0].unk1C < D_8004C6F8) {
                D_8004BCD0[arg0].unk1C = D_8004C6F8;
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = 0.0f;
                if (D_8004BCD0[arg0].unk1D != 2) {
                    D_8004BCD0[arg0].unk8 = (f32)((arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C) * ((f64)arcadeRand() - 16384.0)) / 40000.0 + (f64)(-D_8004BCD0[arg0].unk8) * 0.2);
                }
                if (D_8004BCD0[arg0].unk4 > 230.0f) {
                    D_8004BCD0[arg0].unk19 = 3;
                    D_8004BCD0[arg0].unk1A = 1;
                    D_8004BCD0[arg0].unk8 = -1.0f;
                    D_8004BCD0[arg0].unkC = -0.7f;
                }
            }
            break;
        }
        if (D_8004BCD0[D_8004C71F].unk1C >= D_8004C6F8 || D_8004BCD0[arg0].unk1D != 0) {
            if (270.0f < D_8004BCD0[arg0].unk0) {
                if (D_8004BCD0[D_8004C71F].unk0 < 1.0f) {}
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            } else if (D_8004BCD0[arg0].unk0 < 50.0f) {
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
        }
        if (278.0f < D_8004BCD0[arg0].unk0 || D_8004BCD0[arg0].unk0 < 2.0f) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if ((D_8004BCD0[arg0].unk4 > 242.0f) & (D_8004BCD0[arg0].unk0 < 74.0f)) {
            if (D_8004BCD0[arg0].unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                v = arcadeFindEntityByType(0x13);
                if (v < 0) {
                    v = arcadeFindFreeEntity();
                    D_8004BCD0[v] = D_8004A3F8;
                }
                D_8004BCE9[v << 5] = 3;
                D_8004BCD0[arg0].unk18 = 0;
            } else {
                D_8004BCD0[arg0].unk18 = 0;
            }
        }
        if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - D_8004BCD0[arg0].unk0 < 8.0f) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(arg0);
    }
}
