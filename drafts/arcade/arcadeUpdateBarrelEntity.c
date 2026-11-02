// arcadeUpdateBarrelEntity (src/arcade/0.c): stage 5, text diff 115 / full 117 (719 vs 723 lines; was 122/126): arm A stores reordered (unk1C,unk19,unk8=0.0f,unk4+=1.0f,unkC=1.0f,unk0) fixes arm A fp temp naming; named-array spelling D_8004BCD0[arg0].f (not e->) in case 2/3/5/7 bodies removes the C6F8 reload at arm A end (pointer stores kill the s32 C6F8 load; array stores keep it). Remaining: tail2 (L_tail2) block target hoists lbu C71F/sll/addu a1/lw a0 before the compare, ours does it after the branch (4 insns short); t-ring shifts downstream. Same 5 FAKE dead tests. Tried: 1024 group flips ptr/array, 3x deadsweep, 720 arm-A orders.
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
                    D_8004BCD0[arg0].unk1C = (4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand()) | 0x40;
                }
            L_tail2:
                if ((f32)sp3C - D_8004BCD0[arg0].unk4 < 3.0f) {
                    e->unk4 = (f32)sp3C;
                } else {
                    e->unk19 = 3;
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
                if (D_8004C6F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_8004BCD0[arg0].unk18 = 0;
                if (D_8004C6F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
        }
        if (D_8004C71F) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_8004C6F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (e->unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - e->unk0 < 8.0f) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(arg0);
    }
}
