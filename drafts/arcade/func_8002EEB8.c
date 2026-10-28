// func_8002EEB8 (src/arcade/0.c): stage 5: frame 48 + all stack offsets + case-by-case text match; 13 scheduler-only hunks left: (1) case 12: target hoists 'li at,20' before 'addiu t4,t3,-1' (v0=andi var reused for bne v0,at) and 'li t6,9' after sb; mine emits li at,20 at the else-if and li t6,9 early. (2) case 11 (e idx 290): 'lui t8,D_8004A76C' after the decrement block in target, before in mine. (3) case 10: target 'lui at,0x4f80' before lbu a0 + 'li at,40' hoisted before mul.s, then 'move v0,a0' copy in the bne delay; mine reorders (nop slot). Matching tricks: no cnt/r/t locals (any extra local = frame 56); idx,n only; r assigned inline via arcadeRand() in expressions; mult order '(.../200 + .../30000) * arcadeMinFloat(3.0f,(f32)D_8004A76C)'; '(51.0f - min*5.0f) + (f32)(rand&0xF)'; 'if (D.unk10++ > 60.0f)' for case 5; '/ 8' (int) to get div.s. Tried: u8/s32 cnt local, predec, n/idx reuse, switch(unk1C) (224 lines), case10 local c (frame 56), permuter 900s (never below baseline 570).
extern u8 D_8003E9F0[];
extern u8 D_80043498[];
extern u8 D_800463F0[];
extern ArcadeEntity D_8004A3B8;
void func_8002EEB8(s32 arg0) {
    s32 idx;
    s32 n;

    if (D_8004C71D == 0 || D_8004BCD0[arg0].unk19 == 5) {
        switch (D_8004BCD0[arg0].unk19) {
        case 12:
            D_8004BCD0[arg0].unk1C -= 1;
            if (D_8004BCD0[arg0].unk1C == 0) {
                D_8004BCD0[arg0].unk1C = 0x14;
                D_8004BCD0[arg0].unk19 = 9;
                D_8004BCD0[arg0].unk14 = D_8003E9F0;
                D_8004BCD0[arg0].unk1A = 0;
                idx = arcadeFindFreeEntity();
                D_8004BCD0[arg0].unk1D = idx;
                n = (s32)D_8004BCD0[arg0].unk10++;
                D_8004BCD0[idx] = D_8004A3B8;
                if (!(n & 7)) {
                    D_8004BCD0[idx].unk1D = 1;
                }
                if (n == 2 && D_8004C723 != 0) {
                    D_8004BCD0[idx].unk1C = 2;
                    return;
                }
                if (n == 1) {
                    if (D_8004C723 == 0) {
                        D_8004BCD0[idx].unk1C = 2;
                        return;
                    }
                    D_8004BCD0[idx].unk1C = 5;
                    return;
                }
                if (n != 0) {
                    if (!((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 2000.0f + 2048.0f)) {
                        return;
                    }
                }
                D_8004BCD0[idx].unk10 = 1.0f;
                if (n == 0) {
                    D_8004BCD0[idx].unk1D = 2;
                    if (D_8004A76C == 1) {
                        D_8004BCD0[idx].unk8 = 0.0f;
                        return;
                    }
                    if (D_8004A76C == 2) {
                        D_8004BCD0[idx].unk8 = 0.65f;
                        return;
                    }
                    D_8004BCD0[idx].unk8 = 0.77f;
                    return;
                }
                D_8004BCD0[idx].unk8 = (((f64)D_8004BCD0[D_8004C71F].unk0 - 92.0) / 200.0 + ((f64)arcadeRand() - 16384.0) / 30000.0) * arcadeMinFloat(3.0f, (f32)D_8004A76C);
                if ((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 2000.0f + 4096.0f) {
                    D_8004BCD0[idx].unk1C = 6;
                    return;
                }
            } else if (D_8004BCD0[arg0].unk1C == 0x14) {
                D_8004C71E -= 1;
                return;
            }
            break;
        case 9:
            D_8004BCD0[arg0].unk1C -= 1;
            if (D_8004BCD0[arg0].unk1C == 0) {
                idx = D_8004BCD0[arg0].unk1D;
                D_8004BCD0[idx].unk0 = 92.0f;
                if (D_8004BCD0[idx].unk10 != 0.0f) {
                    D_8004BCD0[arg0].unk1C = 0x1E;
                    D_8004BCD0[arg0].unk19 = 0xB;
                    D_8004BCD0[arg0].unk14 = D_80040540;
                    D_8004BCD0[arg0].unk1A = 0;
                    D_8004BCD0[idx].unk19 = 7;
                    D_8004BCD0[idx].unk1C = 2;
                    return;
                }
                D_8004BCD0[arg0].unk1C = 0x3C;
                D_8004BCD0[arg0].unk19 = 0xA;
                D_8004BCD0[arg0].unk14 = D_80043498;
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[idx].unk19 = 1;
                return;
            }
            break;
        case 11:
            D_8004BCD0[arg0].unk1C -= 1;
            if (D_8004BCD0[arg0].unk1C == 0) {
                D_8004BCD0[arg0].unk1C = (u8)(u32)((51.0f - arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 5.0f) + (f32)(arcadeRand() & 0xF));
                D_8004BCD0[arg0].unk19 = 0xC;
                D_8004BCD0[arg0].unk14 = D_800424D0;
                D_8004BCD0[arg0].unk1A = 0;
                return;
            }
            break;
        case 10:
            idx = D_8004BCD0[arg0].unk1D;
            D_8004BCD0[arg0].unk1C -= 1;
            if ((f32)(u32)D_8004BCD0[arg0].unk1C == arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 3.0f) {
                D_8004BCD0[arg0].unk1C = (u8)(u32)((51.0f - arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 5.0f) + (f32)(arcadeRand() & 0xF));
                D_8004BCD0[arg0].unk19 = 0xC;
                D_8004BCD0[arg0].unk14 = D_80040540;
                D_8004BCD0[arg0].unk1A = 0;
                return;
            }
            if (D_8004BCD0[arg0].unk1C == 0x28) {
                D_8004BCD0[arg0].unk14 = D_8003E9F0;
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[idx].unk19 = 0;
                D_8004BCD0[idx].unk0 = 122.0f;
                D_8004BCD0[idx].unk4 = 83.0f;
                return;
            }
            if (D_8004BCD0[arg0].unk1C == 0x14) {
                D_8004BCE9[idx << 5] = 2;
                return;
            }
            break;
        case 5:
            if (D_8004BCD0[arg0].unk10++ > 60.0f) {
                if (D_8004C721 != 0) {
                    D_8004BCD0[arg0].unk14 = D_800463F0;
                    D_8004BCD0[arg0].unk1A = (s32)(D_8004BCD0[arg0].unk10 / 8) & 1;
                } else {
                    D_8004BCD0[arg0].unk1A = 0;
                    if ((s32)(D_8004BCD0[arg0].unk10 / 8) & 1) {
                        D_8004BCD0[arg0].unk14 = D_80045428;
                    } else {
                        D_8004BCD0[arg0].unk14 = D_80044460;
                    }
                }
                if (D_8004C722 != 4) {
                    D_8004BCD0[arg0].unk0 = 100.0f;
                }
                D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 - 0.4;
                if (D_8004BCD0[arg0].unk4 < 23.0f) {
                    D_8004C721 = 0;
                }
                if (D_8004BCD0[arg0].unk10 > 280.0f) {
                    D_8004C723 += 1;
                    func_800257D8();
                    return;
                }
                if (D_8004BCD0[arg0].unk10 == 200.0f && D_8004C71E > 0) {
                    arcadeAddScore(D_8004C71E * 0x64);
                    return;
                }
            } else {
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[arg0].unk14 = D_8003E9F0;
            }
            break;
        }
    }
}
