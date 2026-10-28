// func_800303B8 (src/arcade/0.c): from .scratch/ArcA5b/func_800303B8_best.c
extern u8 D_800393F8[];
extern u8 D_80039640[];
extern u8 D_80039888[];
extern u8 D_80039AD0[];
extern ArcadeEntity D_8004A618;

void func_800303B8(u8 arg0) {
    s32 i;
    s32 idx;

    if (D_8004C71D == 0) {
        switch (D_8004BCD0[arg0].unk19) {
        case 0:
            if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 > -8.0f) {
                if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 8.0f && D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 > -8.0f) {
                    arcadeStopSound(0x49);
                    D_8004C710 = 0x258;
                    D_8004BCD0[arg0].unk19 = 2;
                    return;
                }
            }
            break;
        case 2:
            i = 0;
            D_8004BCD0[arg0].unk1A = D_8004BCD0[D_8004C71F].unk1A;
            if ((D_8004C710 & 8) || D_8004BCD0[D_8004C71F].unk19 != 2) {
                if (D_8004C710 >= 0xF1 || (D_8004C710 & 4)) {
                    D_8004BCD0[arg0].unk14 = D_800393F8;
                } else {
                    D_8004BCD0[arg0].unk14 = D_80039888;
                }
                D_8004BCD0[arg0].unk0 = D_8004BCD0[D_8004C71F].unk0;
                D_8004BCD0[arg0].unk4 = D_8004BCD0[D_8004C71F].unk4 - 16.0f;
            } else {
                if (D_8004C710 >= 0xF1 || (D_8004C710 & 4)) {
                    D_8004BCD0[arg0].unk14 = D_80039640;
                } else {
                    D_8004BCD0[arg0].unk14 = D_80039AD0;
                }
                if (D_8004BCD0[arg0].unk1A != 0) {
                    D_8004BCD0[arg0].unk0 = D_8004BCD0[D_8004C71F].unk0 + 15.0f;
                } else {
                    D_8004BCD0[arg0].unk0 = D_8004BCD0[D_8004C71F].unk0 - 15.0f;
                }
                D_8004BCD0[arg0].unk4 = D_8004BCD0[D_8004C71F].unk4;
            }
            do {
                if (D_8004BCD0[i].unk18 == 1 || D_8004BCD0[i].unk18 == 4 || D_8004BCD0[i].unk18 == 2) {
                    if (arcadeAbs(D_8004BCD0[i].unk0 - D_8004BCD0[arg0].unk0) < 0xD) {
                        if (arcadeAbs(D_8004BCD0[i].unk4 - D_8004BCD0[arg0].unk4) < 8) {
                            n_alSndpPlay(D_8076D1F8, 0x4B, 0x7FFF, 0x3F, 1.0f, 0, 0);
                            idx = (u8)func_800247F0();
                            D_8004BCD0[idx] = D_8004A618;
                            D_8004BCD0[idx].unk18 = 7;
                            D_8004BCD0[idx].unk1D = D_8004BCD0[i].unk18;
                            D_8004BCD0[idx].unk0 = D_8004BCD0[arg0].unk0;
                            D_8004BCD0[idx].unk4 = D_8004BCD0[arg0].unk4;
                            D_8004BCD0[i].unk18 = 0;
                            D_8004C71D = 1;
                        }
                    }
                }
                i = (u8)(i + 1);
            } while (i < 0x50);
            if (D_8004C710-- == 1) {
                D_8004BCD0[arg0].unk18 = 0;
                arcadeStopSound(0);
                arcadeSetStageMusic();
            }
            break;
        }
    }
}
