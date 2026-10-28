// func_8002E158 (src/arcade/0.c): from .scratch/ArcA5/func_8002E158_best.c
extern u8 D_80037788[];
extern u8 D_80037990[];

void func_8002E158(s32 arg0) {
    s32 sw;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
        D_8004BCD0[arg0].unk10 += 0.1;
        sw = (s32)D_8004BCD0[arg0].unk10;
        switch (sw & 1) {
        case 0:
            D_8004BCD0[arg0].unk14 = D_80037788;
            break;
        case 1:
            D_8004BCD0[arg0].unk14 = D_80037990;
            break;
        }
        D_8004BCD0[arg0].unk4 += D_8004BCD0[arg0].unkC;
        if (D_8004BCD0[arg0].unkC < 5.0f) {
            D_8004BCD0[arg0].unkC += 0.3;
        }
        if (D_8004BCD0[arg0].unk4 > 81.0f) {
            if (D_8004BCD0[arg0].unk0 < 220.0f) {
                D_8004BCD0[arg0].unk4 = 81.0f;
                D_8004BCD0[arg0].unkC = -3.5f;
                if (D_8004BCD0[arg0].unk0 > 40.0f) {
                    n_alSndpPlay(D_8076D1F8, 0x43, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
            } else if (D_8004BCD0[arg0].unk8 != 0.0f) {
                D_8004BCD0[arg0].unk8 = 0.0f;
                n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
        }
        if (D_8004BCD0[arg0].unk4 > 271.0f) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if (arcadeAbs(D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0) < 7) {
            if (D_8004BCD0[arg0].unk4 - *(f32 *)((u8 *)&D_8004BCD4 + (D_8004C71F << 5)) < 4.0f && D_8004BCD0[arg0].unk4 - *(f32 *)((u8 *)&D_8004BCD4 + (D_8004C71F << 5)) > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}
