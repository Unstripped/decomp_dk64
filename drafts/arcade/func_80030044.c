// func_80030044 (src/arcade/0.c): Stage 5: same size/structure; only regalloc: D_8004C6DC value (shared by `%120` and tail `&1`) must be in a0 and (s32)unk10 trunc in a1 (mine v0 / a0). Tried tick local (assign in case2+tail, in default arms, initialiser at top), arg0-as-tick with ptr local e (move v0,v1 + frame), none fixes it.
void func_80030044(s32 arg0) {
    switch (D_8004BCD0[arg0].unk19) {
    case 2:
        if (D_8004C71D != 0) {
            return;
        }
        if (D_8004C6DC % 120 == 0) {
            D_8004C71E -= 1;
        }
        if (D_8004BCD0[arg0].unk0 > 204.0f) {
            D_8004BCD0[arg0].unk8 = -1.0f;
        }
        if (D_8004BCD0[arg0].unk0 < 68.0f) {
            D_8004BCD0[arg0].unk8 = 1.0f;
        }
        D_8004BCD0[arg0].unk10 += 1.0f;
        if ((u8)(s32)D_8004BCD0[arg0].unk10 < 0xA0) {
            D_8004BCD0[arg0].unk14 = D_80040540;
        } else {
            D_8004BCD0[arg0].unk14 = D_800424D0;
            D_8004BCD0[arg0].unk1A = (((s32)D_8004BCD0[arg0].unk10 & 0x20) / 32) == 0;
        }
        break;
    case 5:
        if (D_8004BCD0[arg0].unk0 > 100.0f) {
            D_8004BCD0[arg0].unk8 = -1.0f;
        } else if (D_8004BCD0[arg0].unk0 < 100.0f) {
            D_8004BCD0[arg0].unk8 = 1.0f;
        } else {
            D_8004BCD0[arg0].unk18 = 0x16;
            D_8004BCD0[arg0].unk8 = 0.0f;
            D_8004BCD0[arg0].unk10 = 41.0f;
        }
        break;
    }
    if (!(D_8004C6DC & 1)) {
        D_8004A308[0] = (s32)D_8004BCD0[arg0].unk8;
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
    }
}
