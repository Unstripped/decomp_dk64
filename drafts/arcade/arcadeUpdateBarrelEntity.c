// arcadeUpdateBarrelEntity (src/arcade/0.c): Leftovers7 Arcade: stage 4 PARKED NON_MATCHING in the copy: deadsweep full=70 text=70 reloc=0 shape=8 (was 241 with 9 FAKEs), count exact (723 lines), frame/callee-saved same, 2 FAKE dead tests. KEY (Leftovers7): the old draft's 241 diff was a structural artefact of 'goto L_tail2' + e-> stores in the tail2 arms. Write case 2 as plain if / else-if / COMMON TAIL (no goto; the 'unk1C |= 0x80' arm just falls out of the if) and spell the two tail2 arm stores through the NAMED ARRAY (D_8004BCD0[arg0].unk4 = (f32)sp3C; D_8004BCD0[arg0].unk19 = 3;): named-array stores do not kill the D_8004C71F/D_8004C6F8 loads (e-> stores do), so uopt's PRE puts the post-switch loads at the HEAD of the tail2 block (target shape: metric idx(5th LO16 C71F)-idx(3rd c.lt.s) == -14, 614 insns) with ZERO fakes: 241 -> 152. An e->/D_8004BCD0[arg0]. spelling-bit annealer over all 106 field sites (+dead tests; .scratch/Arcade/bv/sa.py, ~30 evals/s) then took it 152 -> 70 (2 FAKEs). Remaining 70 lines are pure t-ring phase + one as1 order block in case 5: the dest-register sequence matches the target for the first 89 dests, then case 5/3 'li t6,1' vs ours t5 (ours 1 step behind) and the join 'lbu t5,0x1C(a1)' vs ours t6 (1 ahead). Tried with no gain from 70: 160k annealing evals (spelling bits, dead tests incl. self-assigns sp3C=sp3C/e=e, (u8)/(s32)/(u32) no-code wrappers on every integer field read, prefix-weighted objective).
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
        switch (D_8004BCD0[arg0].unk19) {
        case 2:
            D_8004BCD0[arg0].unk10 = (f32)((f64)e->unk10 + 0.2);
            e->unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            if (e->unk4 < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCD0[D_8004C71F].unk19 != 5)))) {
                if (e->unk1C & 0x80) {
                    break;
                }
                D_8004BCD0[arg0].unk1C = e->unk1C & 0xF;
                if (e->unk1C > 0) {
                    D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C - 1;
                    D_8004BCD0[arg0].unk19 = 5;
                    D_8004BCD0[arg0].unk8 = 0.0f;
                    D_8004BCD0[arg0].unk4 = e->unk4 + 1.0f;
                    D_8004BCD0[arg0].unkC = 1.0f;
                    D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
                    break;
                }
                e->unk1C = D_8004BCD0[arg0].unk1C | 0x80;
            } else if (!(e->unk1C & 0x47)) {
                e->unk1C = (4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand()) | 0x40;
            }
            if ((f32)sp3C - e->unk4 < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
            } else {
                D_8004BCD0[arg0].unk19 = 3;
                D_8004BCD0[arg0].unkC = 0.0f;
                D_8004BCD0[arg0].unk8 = D_8004BCD0[arg0].unk8 / 2;
            }
            break;
        case 3:
            e->unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            e->unk4 = D_8004BCD0[arg0].unk4 + e->unkC;
            e->unkC = (f32)((f64)e->unkC + 0.06);
            if ((f32)sp3C < e->unk4 && e->unk4 - (f32)sp3C < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = -D_8004BCD0[arg0].unkC / 3.0f;
                if ((f64)e->unkC > -0.2) {
                    D_8004BCD0[arg0].unk19 = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            e->unk4 = D_8004BCD0[arg0].unk4 + e->unkC;
            if ((f32)(D_8004C6E8 - 1) < e->unk4) {
                e->unk1A = 1 - e->unk1A;
                e->unk19 = 2;
                e->unk4 = (f32)sp3C;
                e->unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
            break;
        case 7:
            e->unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            e->unk4 = D_8004BCD0[arg0].unk4 + e->unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)e->unkC + 0.06);
            sp3C = arcadeCheckPlayerCollision((s32)e->unk0, (s32)e->unk4);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && e->unk4 - (f32)sp3C < 8.0f && D_8004BCD0[arg0].unk1C < D_8004C6F8) {
                D_8004BCD0[arg0].unk1C = D_8004C6F8;
                e->unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = 0.0f;
                if (D_8004BCD0[arg0].unk1D != 2) {
                    e->unk8 = (f32)((((f64)arcadeRand() - 16384.0) * arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C)) / 40000.0 + (f64)(-e->unk8) * 0.2);
                }
                if (D_8004BCD0[arg0].unk4 > 230.0f) {
                    D_8004BCD0[arg0].unk19 = 3;
                    e->unk1A = 1;
                    e->unk8 = -1.0f;
                    D_8004BCD0[arg0].unkC = -0.7f;
                }
            }
            break;
        }
        if (D_8004BCD0[D_8004C71F].unk1C >= D_8004C6F8 || D_8004BCD0[arg0].unk1D != 0) {
            if (270.0f < e->unk0) {
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            } else if (D_8004BCD0[arg0].unk0 < 50.0f) {
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[arg0].unk8 = (f32)(1 - e->unk1A * 2);
            }
        }
        if (278.0f < D_8004BCD0[arg0].unk0 || D_8004BCD0[arg0].unk0 < 2.0f) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if ((e->unk4 > 242.0f) & (D_8004BCD0[arg0].unk0 < 74.0f)) {
            if (e->unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                sp3C = arcadeFindEntityByType(0x13);
                if (sp3C < 0) {
                    sp3C = arcadeFindFreeEntity();
                    D_8004BCD0[sp3C] = D_8004A3F8;
                }
                if (D_8004C71F == 0) {}  // FAKE: dead test (steers uopt)
                if (D_8004BCD0[D_8004C71F].unk1C && D_8004BCD0[D_8004C71F].unk1C) {}  // FAKE: dead test (steers uopt)
                D_8004BCE9[sp3C << 5] = 3;
                e->unk18 = 0;
            } else {
                D_8004BCD0[arg0].unk18 = 0;
            }
        }
        if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - D_8004BCD0[arg0].unk0 < 8.0f) {
            if (e->unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(arg0);
    }
