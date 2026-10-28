// func_8002D6FC (src/arcade/0.c): stage 4, 48-byte frame, diff score 216 (harness). ArcNM1d sweeps: 'unk1A = unk1A == 0' x8 forms at both sites (no change); declaration permutations x 0-2 dummy locals (s32/s16/u8/f32/f64, 3126 variants: a dummy fixes the v1 slot to 28 but frame 56); local merges (sp20->a0 etc.); greedy dead-statement rounds (E/P/global compares, 14 forms x ~100 points): best 'if (D_8004A76C && D_8004A76C) {}' at the top of case 2 gives v1 slot 28 (score 208/204) but frame 56 (v0 temp 48 vs 32). uopt: the case-2 first arcadeMinFloat result is a 5th M-vreg (-20) saved across the second arcadeRand; target's evaluation order loads unk1A after the call (lbu t6,26(v1) after cvt.d.s) while ours loads it right after the jal; v1 slot 24 vs 28 and v0 slot 36 vs 32 are the temp-slot ordering (3 temp slots 24/28/32 in target, ours 24/36). Not matched.
extern u8 D_80035EF0[];
extern u8 D_80036138[];
extern u8 D_80036380[];
extern u8 D_800365C8[];
extern u8 D_80036810[];
extern u8 D_80036A58[];
extern u8 D_80036CA0[];
extern u8 D_80036EE8[];
void func_8002D6FC(s32 arg0) {
    s32 sp2C;
    s32 a0;
    s32 sp20;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.15);
        if (D_8004BCD0[arg0].unk10 >= 5.0f) {
            D_8004BCD0[arg0].unk10 = D_8004BCD0[arg0].unk10 - 5.0f;
        }
        if (D_8004C722 == 2) {
            if (D_8004C710 != 0) {
                if ((D_8004C6DC / 4) & 1) {
                    D_8004BCD0[arg0].unk14 = D_80036810;
                } else {
                    D_8004BCD0[arg0].unk14 = D_80036A58;
                }
            } else if ((D_8004C6DC / 4) & 1) {
                D_8004BCD0[arg0].unk14 = D_80036380;
            } else {
                D_8004BCD0[arg0].unk14 = D_800365C8;
            }
        } else if (D_8004C710 != 0) {
            if ((D_8004C6DC / 4) & 1) {
                D_8004BCD0[arg0].unk14 = D_80036CA0;
            } else {
                D_8004BCD0[arg0].unk14 = D_80036EE8;
            }
        } else if ((D_8004C6DC / 4) & 1) {
            D_8004BCD0[arg0].unk14 = D_80035EF0;
        } else {
            D_8004BCD0[arg0].unk14 = D_80036138;
        }
        sp2C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        arcadeCheckStageLadders((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        switch (D_8004BCD0[arg0].unk19) {
        case 2:
            sp20 = arcadeRand();
            if ((f32)sp20 < arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 60.0f + 256.0f) {
                a0 = D_8004BCD0[arg0].unk0 < D_8004BCD0[D_8004C71F].unk0;
                a0 += ((D_8004BCD0[D_8004C71F].unk1A & 2) * 3) / 2;
                D_8004BCD0[arg0].unk1A = (arcadeRand() + a0 * 0xFB8) - 0x1F70 >= 0x4001;
            }
            if ((f32)arcadeCheckPlayerCollision((s32)(D_8004BCD0[arg0].unk0 + D_8004BCD0[arg0].unk8 * 8.0f), (s32)D_8004BCD0[arg0].unk4) - D_8004BCD0[arg0].unk4 > 5.0f) {
                D_8004BCD0[arg0].unk1A = D_8004BCD0[arg0].unk1A == 0;
            } else {
                D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
            }
            D_8004BCD0[arg0].unk8 = (f32)((((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 15.0) + 1.0) * ((f64)(u32)D_8004BCD0[arg0].unk1A - 0.5));
            if (D_8004A76C && D_8004A76C) {}
            a0 = (s32)(arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4) * 3.0f);
            if (D_8004BCD0[arg0].unk4 < (f32)D_8004C6E8 && arcadeRand() < 0x400 - a0) {
                D_8004BCD0[arg0].unk19 = 5;
                D_8004BCD0[arg0].unk8 = 0.0f;
                D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + 1.0f;
                D_8004BCD0[arg0].unkC = (f32)(2.0 * (((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 30.0) + 0.2));
                D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
            } else if ((f32)D_8004C6E4 < D_8004BCD0[arg0].unk4 && arcadeRand() < a0 + 0x400) {
                D_8004BCD0[arg0].unk19 = 6;
                D_8004BCD0[arg0].unk8 = 0.0f;
                D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 - 1.0f;
                D_8004BCD0[arg0].unkC = (f32)-(((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 30.0) + 0.2);
                D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
            } else if ((f32)sp2C - D_8004BCD0[arg0].unk4 < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
            } else {
                if (D_8004C71F == 0) {}
                D_8004BCD0[arg0].unk1A = D_8004BCD0[arg0].unk1A == 0;
            }
            break;
        case 3:
            D_8004BCD0[arg0].unk0 = D_8004BCD0[arg0].unk0 + D_8004BCD0[arg0].unk8;
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)D_8004BCD0[arg0].unkC + 0.06);
            if ((f32)sp2C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp2C < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
                D_8004BCD0[arg0].unkC = -D_8004BCD0[arg0].unkC / 3.0f;
                if ((f64)D_8004BCD0[arg0].unkC > -0.2) {
                    D_8004BCD0[arg0].unk19 = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            if ((f32)(D_8004C6E8 - 1) < D_8004BCD0[arg0].unk4) {
                D_8004BCD0[arg0].unk1A = 1 - D_8004BCD0[arg0].unk1A;
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
            break;
        case 6:
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            if (D_8004BCD0[arg0].unk4 < (f32)(D_8004C6E4 + 1)) {
                D_8004BCD0[arg0].unk1A = 1 - D_8004BCD0[arg0].unk1A;
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
            break;
        }
        if (270.0f < D_8004BCD0[arg0].unk0) {
            D_8004BCD0[arg0].unk1A = 0;
            D_8004BCD0[arg0].unk8 = (f32)((f64)(u32)D_8004BCD0[arg0].unk1A - 0.5);
        } else if (D_8004BCD0[arg0].unk0 < 50.0f) {
            D_8004BCD0[arg0].unk1A = 1;
            D_8004BCD0[arg0].unk8 = (f32)((f64)(u32)D_8004BCD0[arg0].unk1A - 0.5);
        }
        if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - D_8004BCD0[arg0].unk0 < 8.0f) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}
