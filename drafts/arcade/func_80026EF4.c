// func_80026EF4 (src/arcade/0.c): stage 3 (frame 112 vs 104). m2c-faithful C compiles; mismatches: expected keeps &D_8004C708 in s3 (lw 0(s3) at entry and later), recomputes D_807444FC*0x18 with sll/subu/sll (use (x*3<<3)), no const-24 or &D_807444FC candidate; mine promotes &D_807444FC to s2 and the sp60 addr to s3, +8 slack. 4 loops use s1=7 / s3=0x14 as const regs for the j!=7&&j!=0x14 tests. Diff ~450 lines.
#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
extern u8 D_80032F18[];
extern u8 D_8004BC50[];
void func_80026EF4(Gfx **arg0) {
    Gfx *sp60;
    s32 i;
    s32 j;
    s32 x;

    sp60 = *arg0;
    if (D_8004C708 < 2) {
        D_8004C719 = 2;
        D_8004C71A = 8;
        D_8004C6D4 = 0x400;
        ArcA1_P6D0 = D_80032F18;
        func_80005A90(D_8004BC50 + (D_807444FC * 3 << 3), D_80032F18, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
        func_8070E8F0((s32 *)&sp60, D_8004BC50 + (D_807444FC * 3 << 3));
        func_8070F2C8(0x400, D_8004C6D6, 0, 0);
        i = 0;
        do {
            func_8070F2FC((s32 *)&sp60, 0x1DC, (s32)((f64)(s32)((f64)i + 51.625 + 8.0) * 4.0));
            i += 8;
        } while (i < 0x20);
        i = 0;
        do {
            func_8070F2FC((s32 *)&sp60, 0x31C, (s32)((f64)(s32)((f64)i + 51.625 + 8.0) * 4.0));
            i += 8;
        } while (i != 0x20);
    }
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    ArcA1_P6D0 = D_80032C20;
    func_80005A90(D_8004BB00 + (D_807444FC * 3 << 3), D_80032C20, 0, 8, 8, 8, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp60, D_8004BB00 + (D_807444FC * 3 << 3));
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0xC0;
    do {
        func_8070F2FC((s32 *)&sp60, x, 0x380);
        x += 0x20;
    } while (x < 0x440);
    j = 1;
    x = 0x1C0;
    if (D_8004C708 == 0) {
        do {
            if (j != 7 && j != 0x14) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x2F8);
            }
            j++;
        } while (j < 0x1B);
        j = 2;
        do {
            if (j != 7 && j != 0x14) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x270);
            }
            j++;
        } while (j < 0x1A);
        j = 3;
        do {
            if (j != 7 && j != 0x14) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x1EC);
            }
            j++;
        } while (j < 0x19);
        j = 4;
        do {
            if (j != 7 && j != 0x14) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x164);
            }
            j++;
        } while (j != 0x18);
    } else {
        do {
            func_8070F2FC((s32 *)&sp60, x, 0x360);
            func_8070F2FC((s32 *)&sp60, x, 0x340);
            func_8070F2FC((s32 *)&sp60, x, 0x320);
            func_8070F2FC((s32 *)&sp60, x, 0x300);
            x += 0x20;
        } while (x < 0x340);
        j = 1;
        do {
            if (j < 7 || j >= 0x15) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x2F8);
            }
            j++;
        } while (j < 0x1B);
        j = 2;
        do {
            if (j < 7 || j >= 0x15) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x270);
            }
            j++;
        } while (j < 0x1A);
        j = 3;
        do {
            if (j < 7 || j >= 0x15) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x1EC);
            }
            j++;
        } while (j < 0x19);
        j = 4;
        do {
            if (j < 7 || j >= 0x15 || D_8004C708 == 2) {
                func_8070F2FC((s32 *)&sp60, (j << 5) + 0xC0, 0x164);
            }
            j++;
        } while (j != 0x18);
    }
    x = 0x1A0;
    if (D_8004C708 < 2) {
        do {
            func_8070F2FC((s32 *)&sp60, x, 0xD8);
            x += 0x20;
        } while (x != 0x360);
    }
    func_8002628C(&sp60);
    *arg0 = sp60;
}
