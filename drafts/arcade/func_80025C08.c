// func_80025C08 (src/arcade/0.c): stage 6: 4 diff lines. Only t8/t9 temp numbering in the tail (lw t9,0x70(sp)/sll t8 vs lw t8/sll t9). Single-line if/else chain for D_8004C6D0 fixed the addiu order of branches 1/2. D_8004C6D0 is a pointer var in this function but the file declares it ArcadeEntity: macro cast used (ArcA1_D6D0).
#define ArcA1_D6D0 (*(void **)&D_8004C6D0)
void func_80025C08(arg0, arg1, arg2, arg3)
s32 *arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    s32 i;
    s32 sp60;

    D_8004C719 = 8;
    D_8004C71A = 4;
    D_8004C6D4 = 0x400;
    if (D_8004C722 == 2) ArcA1_D6D0 = D_80032B90;
    else if (D_8004C722 == 4) ArcA1_D6D0 = D_80032BD8;
    else ArcA1_D6D0 = D_80032B48;
    func_80005A90(D_8004BB30 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_80005A90(D_8004BB60 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, 1, 0, 2, 0, 0);
    func_80005A90(D_8004BB90 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, 2, 0, 2, 0, 0);
    func_80005A90(D_8004BBC0 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, 3, 0, 2, 0, 0);
    sp60 = *arg0;
    func_8070E8F0(&sp60, D_8004BB30 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    for (i = 0; i < arg3 / 4; i++) {
        func_8070F2FC(&sp60, arg1 * 4, (s32)((f64)(arg2 + 8 + i * 4) * 4.0));
    }
    D_8004C71A = arg3 % 4;
    if (D_8004C71A != 0) {
        switch (D_8004C71A) {
        case 1:
            func_8070E8F0(&sp60, D_8004BB60 + D_807444FC * 0x18);
            break;
        case 2:
            func_8070E8F0(&sp60, D_8004BB90 + D_807444FC * 0x18);
            break;
        case 3:
            func_8070E8F0(&sp60, D_8004BBC0 + D_807444FC * 0x18);
            break;
        }
        func_8070F2C8(0x400, D_8004C6D6, 0, 0);
        func_8070F2FC(&sp60, arg1 * 4, (s32)((f64)(i * 4 + arg2 + 8) * 4.0));
    }
    *arg0 = sp60;
}
