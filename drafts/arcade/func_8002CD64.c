// func_8002CD64 (src/arcade/0.c): stage 3 (frame 0x48 vs 0x40, ~588/616 insns): control flow+constants+callee order right; E[D_8004C71F].unk19 (not D_8004BCE9[..<<5]) in case-2 cond makes uopt hoist the player ixa into every switch arm (as target); remaining: f32 1.0f not one shared candidate (target keeps it in f2 across arms into n_alSndpPlay, a 'one' local spills), frame +8, arg0/a2 vs const-1 candidate taking a2, ixa in a3 not a1, tail dir code 1-(unk1A*2) needs unfolded 'andi 0xFF' (forward of stored u8 field: write E.unk1A=K; E.unk8=(f32)(1-E.unk1A*2))
extern s32 D_8004C6FC;
extern s32 D_8004C704;
void func_8002CD64(s32 arg0) {
    f32 one;
    s32 sp3C;
    f32 sp30;
    s32 r;
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
            D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            if (D_8004BCD0[arg0].unk4 < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCD0[D_8004C71F].unk19 != 5)))) {
                if (!(D_8004BCD0[arg0].unk1C & 0x80)) {
                    v = D_8004BCD0[arg0].unk1C & 0xF;
                    D_8004BCD0[arg0].unk1C = v;
                    if (v > 0) {
                        D_8004BCD0[arg0].unk1C = v - 1;
                        D_8004BCD0[arg0].unk19 = 5;
                        one = 1.0f;
                        D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + one;
                        D_8004BCD0[arg0].unkC = one;
                        D_8004BCD0[arg0].unk8 = 0.0f;
                        D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
                    } else {
                        D_8004BCD0[arg0].unk1C = v | 0x80;
                        goto L_tail2;
                    }
                }
            } else {
                if (!(D_8004BCD0[arg0].unk1C & 0x47)) {
                    sp30 = arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f);
                    v = (f32)arcadeRand() < 4096.0f + sp30 * 1512.0f;
                    D_8004BCD0[arg0].unk1C = v | 0x40;
                }
            L_tail2:
                if ((f32)sp3C - D_8004BCD0[arg0].unk4 < 3.0f) {
                    D_8004BCD0[arg0].unk4 = (f32)sp3C;
                } else {
                    D_8004BCD0[arg0].unk19 = 3;
                    D_8004BCD0[arg0].unkC = 0.0f;
                    D_8004BCD0[arg0].unk8 = D_8004BCD0[arg0].unk8 / 2.0f;
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
                    r = arcadeRand();
                    D_8004BCD0[arg0].unk8 = (f32)((arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C) * ((f64)r - 16384.0)) / 40000.0 + (f64)(-D_8004BCD0[arg0].unk8) * 0.2);
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
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[arg0].unk8 = (f32)(1 - ((u8)1) * 2);
            } else if (D_8004BCD0[arg0].unk0 < 50.0f) {
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[arg0].unk8 = (f32)(1 - ((u8)0) * 2);
            }
        }
        if (278.0f < D_8004BCD0[arg0].unk0 || D_8004BCD0[arg0].unk0 < 2.0f) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if ((D_8004BCD0[arg0].unk4 > 242.0f) & (D_8004BCD0[arg0].unk0 < 74.0f)) {
            if (D_8004BCD0[arg0].unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, one, 0, 0);
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
