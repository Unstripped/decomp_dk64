// func_80030A04 (src/arcade/0.c): from .scratch/ArcA5b/func_80030A04_best.c
void func_80030A04(u8 arg0) {
    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk10 -= 1.0f;
        if (D_8004BCD0[arg0].unk10 < 0.0f) {
            D_8004BCD0[arg0].unk10 = (arcadeRand() & 0x7F) + 0x1C2;
        }
        D_8004BCD0[arg0].unk4 += D_8004BCD0[arg0].unk10 < 200.0f ? 0.2f : -0.2f;
        if (D_8004BCD0[arg0].unk4 < 97.0f) {
            D_8004BCD0[arg0].unk4 = 97.0f;
        }
        if (D_8004BCD0[arg0].unk4 > 110.0f) {
            D_8004BCD0[arg0].unk4 = 110.0f;
        }
    }
}
