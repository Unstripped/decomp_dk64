// func_8002FE28 (src/arcade/0.c): Stage 5: only regalloc: (s32)unk10 trunc temp should be a0 (mine v0; target looks like arg0 reused as cnt with pointer in v1; ptr local e gives move v0,v1), `li a1,0x42` delay-slot fill differs. Frame 0x30 right without user locals except f32 pos.
extern ArcadeEntity D_8004A418;

void func_8002FE28(s32 arg0) {
    f32 pos;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk10 += 1.0f;
        if ((u8)(s32)D_8004BCD0[arg0].unk10 < 0xA0) {
            D_8004BCD0[arg0].unk14 = D_80040540;
        } else {
            if (!((s32)D_8004BCD0[arg0].unk10 & 0x1F)) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            D_8004BCD0[arg0].unk14 = D_800424D0;
            D_8004BCD0[arg0].unk1A = (((s32)D_8004BCD0[arg0].unk10 & 0x20) / 32) == 0;
        }
        if ((s32)D_8004BCD0[arg0].unk10 % (0x72 - (s32)arcadeMinFloat((u32)D_8004A76C, 4.0f) * 0xC) == 0) {
            D_8004C71E -= 1;
            arg0 = arcadeFindFreeEntity();
            D_8004BCD0[arg0] = D_8004A418;
            pos = (arcadeRand() & 0xF) - 0x1C;
            D_8004BCD0[arg0].unk19 = 2;
            D_8004BCD0[arg0].unk0 = pos;
        }
    }
}
