// func_8002D6FC (src/arcade/0.c): stage 4 (SweepNM): E (D_8004BCD0[arg0]) now in v1 spilled to the stack like the target, frame 0x30 and callee-saved set (ra only) match, first ~280 insns identical. Fix: locals sp2C,a0,sp20 + dead 'if (D_8004C71F == 0) {}' in the last else arm of case 2 (found by exhaustive dead-stmt sweep on top of the non-flipped draft; inline 'if ((f32)arcadeRand() < ..' with locals sp2C,a0 also flips E to v1). Remaining: (1) first divergence at 'E.unk1A = E.unk1A == 0' (first if in case 2): target 'lbu a0,26(v1); sltiu t4,a0,1' (uopt candidate colored a0), ours ugen t4/t5, which shifts the whole t-ring after it; (2) v1 spill slot 24(sp) vs target 28(sp) (one hole slot above E in ours; 4 declared locals fix slot but give frame 56); (3) one extra 'sw v1' in the delay slot of the second arcadeMinFloat (a0 line); (4) mul.s operand order (minfloat*(E.unk4-P.unk4)) and lw v1 scheduling after cvt.d.s. Tried: exhaustive single dead-stmt sweep (globals + E/P fields), per-arm break replication, local pointer e, a0-as-temp forms, ! / ^1 / ?: forms of unk1A flip, decl order/pad locals (212+ variants), D_8004BCD4 form (collapses the arm-end P pointer hoist).
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
