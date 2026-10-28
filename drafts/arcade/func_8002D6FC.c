// func_8002D6FC (src/arcade/0.c): stage 3: 650/664 insns. Applied: a0 += ((P.unk1A&2)*3)/2 (addu a0,a0,t7), unk0 += unk8 (case 2 else), unk0 + unk8*8.0f operand order in collision arg. Remaining: E (D_8004BCD0[arg0]) gets s0 instead of v1 spilled 0x1C. Threshold study: with 13 jal (12 crossing E) uopt picks s0; deleting ANY one call from case 2 flips E to v1 (adjsave 5.0, 9 sw/10 lw v1 spills vs target 9/11), so the target's E range must cost less than mine by about one call; named-local order/remove sp28 had no effect. With a call removed the head (sprite pick, case 3/5/6) matches except lbu a0,26(v1) temp taking t4.
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
    s32 sp28;
    s32 sp20;
    s32 a0;

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
