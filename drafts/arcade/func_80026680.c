// func_80026680 (src/arcade/0.c): stage 5: instruction stream identical incl. regs/frame 160 (s0-s7); only stack offsets differ: sp64/sp94 at 0x6C/0x9C vs expected 0x64/0x94 (mine has 8 bytes of slack below the locals, expected has it above sp94). Needs: statement order sp94=*arg0 first, single-line if/else for D_8004C6D0, row cached in local, D_8004C6D6 as ((s16*)&D_8004C6D4)[1].
#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
void func_80026680(Gfx **arg0) {
    Gfx *sp94;
    ArcR2_Struct48 sp64;
    s32 i;
    s32 j;
    s32 row;

    sp64 = D_8004A798;
    sp94 = *arg0;
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    if (D_8004C6DC & 0x182) ArcA1_P6D0 = D_80032C20;
    else ArcA1_P6D0 = D_80032DF8;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp94, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, ((s16 *)&D_8004C6D4)[1], 0, 0);
    for (i = 0; i < 12; i++) {
        row = sp64.words[i];
        for (j = 0; j < 25; j++) {
            if ((1 << j) & row) {
                func_8070F2FC((s32 *)&sp94, 0x3E0 - (j << 5), (s32)((f64)(i * 8 + 0x3F) * 4.0));
            }
        }
    }
    *arg0 = sp94;
}
