// func_8002F82C (src/arcade/0.c): Stage 5: needs n_alSndpPlay declared non-void (e.g. s32 return) at all 3 decls in file (changes no other function) -> ptr in t0, const 2 in v1 as target. Remaining: (u8)cnt compare ok; D_800424D0 address temp gets v0 (target t3/t6, `andi v0` for (cnt&0x20)) and 3rd `% 3 == 2` compare operand order `bne v1,v0` vs target `bne v0,v1`. Permuter hint: dead `if(!D_800424D0 && !D_800424D0){}` before `== 2.0f` check lowers diff to 70.
extern u8 D_800424D0[];
extern u8 D_800473B8[];
extern u8 D_80048380[];
extern u8 D_80049348[];
extern u8 D_8003B180[];
extern s32 D_8004A75C;
extern ArcadeEntity D_8004A6F8;

void func_8002F82C(s32 arg0) {
    s32 cnt;

    switch (D_8004BCD0[arg0].unk19) {
    case 2:
        if (D_8004C71D == 0) {
            if (D_8004C6DC % 120 == 0) {
                D_8004C71E -= 1;
            }
            if (D_8004BCD0[D_8004C71F].unk4 < 95.0f && D_8004BCD0[D_8004C71F].unk4 > 76.0f) {
                if (D_8004BCD0[D_8004C71F].unk0 > 135.0f && D_8004BCD0[D_8004C71F].unk0 < 186.0f) {
                    arcadeKillPlayer();
                }
            }
            cnt = ++D_8004BCD0[arg0].unk1C;
            if ((u8)cnt < 0xA0) {
                D_8004BCD0[arg0].unk14 = D_80040540;
                return;
            }
            if (!(cnt & 0x1F)) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                cnt = D_8004BCD0[arg0].unk1C;
            }
            D_8004BCD0[arg0].unk14 = D_800424D0;
            D_8004BCD0[arg0].unk1A = ((cnt & 0x20) / 32) == 0;
        }
        break;
    case 8:
        if (D_8004BCD0[arg0].unk10++ == 720.0f) {
            D_8004C723 += 1;
            if (D_8004A740 != 0) {
                D_8004A770 = 1;
                if (D_8004A75C < D_8004A748) {
                    arcadeCheckGameOver();
                } else {
                    arcadeExit();
                }
            } else {
                func_800257D8();
            }
        } else {
            if (D_8004BCD0[arg0].unk10 > 480.0f) {
                break;
            }
            if (D_8004BCD0[arg0].unk10 == 400.0f) {
                if (D_8004C71E > 0) {
                    arcadeAddScore(D_8004C71E * 0x64);
                }
            } else if (D_8004BCD0[arg0].unk10 > 200.0f) {
                if (D_8004BCD0[arg0].unk4 < 178.0f) {
                    D_8004BCD0[arg0].unk1B = 1;
                    D_8004BCD0[arg0].unk4 += 1.0f;
                    if (D_8004BCD0[arg0].unk4 >= 178.0f) {
                        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A6F8;
                    }
                } else {
                    if (D_8004C708 != 2) {
                        D_8004C708 = 2;
                        n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    }
                    D_8004BCD0[arg0].unk4 = 178.0f;
                    D_8004BCD0[arg0].unk1A = 0;
                    if (((s32)(D_8004BCD0[arg0].unk10 / 6.0f) % 3) == 0) {
                        D_8004BCD0[arg0].unk14 = D_800473B8;
                    } else if (((s32)(D_8004BCD0[arg0].unk10 / 6.0f) % 3) == 1) {
                        D_8004BCD0[arg0].unk14 = D_80048380;
                    } else if (((s32)(D_8004BCD0[arg0].unk10 / 6.0f) % 3) == 2) {
                        D_8004BCD0[arg0].unk14 = D_80049348;
                    }
                    if (D_8004BCD0[arg0].unk10 == 350.0f) {
                        n_alSndpPlay(D_8076D1F8, 0x50, 0x7FFF, 0x3F, 1.0f, 0, 0);
                        D_8004BCD0[D_8004C71F].unk14 = D_8003B180;
                        D_8004BCD0[D_8004C71F].unk1A = 0;
                        D_8004BCD0[D_8004C71F].unk0 = 190.0f;
                        D_8004BCD0[D_8004C71F].unk4 = 93.0f;
                        D_8004C71D = 3;
                    }
                }
            } else if (D_8004BCD0[arg0].unk10 > 180.0f) {
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[arg0].unk14 = D_80040540;
            } else if (D_8004BCD0[arg0].unk10 > 30.0f) {
                D_8004BCD0[arg0].unk14 = D_800424D0;
                D_8004BCD0[arg0].unk1A = (s32)(D_8004BCD0[arg0].unk10 / 6.0f) & 1;
            }
        }
        if (D_8004BCD0[arg0].unk10 == 2.0f) {
            n_alSndpPlay(D_8076D1F8, 0x52, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        if (D_8004BCD0[arg0].unk10 == 200.0f) {
            n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        break;
    }
}
