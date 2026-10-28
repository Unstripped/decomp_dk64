// func_800275E8 (src/arcade/0.c): stage 4-5: frame 160 matches with an 8-byte pad[2] declared first (sp90 still at 148 vs 144), s0-s7+f20/22/24 same set. Reg assignment differs: expected s2=&D_8004C719 s4=&D_8004C71A s6=&D_807444FC s7=24 s5=&D_8004C6D0 (held for both stores) s0=&D_8004BC50 s3=&sp90; mine gets s5=&D_807444FC s6=24 s7=8 and stores D_8004C6D0 through lui at. Statement order sp90=*arg0 first helps (166 diff lines).
#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
typedef struct ArcA1_Pt {
    u8 x;
    u8 y;
    s16 z;
} ArcA1_Pt;
typedef struct ArcA1_Bar {
    f32 x;
    f32 y;
    f32 vy;
} ArcA1_Bar;
extern u8 D_80032F40[];
extern u8 D_80034568[];
extern ArcA1_Pt D_8004A7C8[];
extern u8 D_8004BC50[];
extern ArcA1_Bar D_8004BC88[];
extern u8 D_8004C724;
void func_800275E8(Gfx **arg0) {
    s32 pad[2];
    Gfx *sp90;
    s32 i;
    s32 j;
    ArcA1_Pt *pt;
    ArcA1_Bar *bar;

    D_8004C719 = 2;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    ArcA1_P6D0 = D_80032F40;
    sp90 = *arg0;
    func_80005A90(D_8004BC50 + D_807444FC * 0x18, D_80032F40, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp90, D_8004BC50 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    i = 0x28;
    do {
        func_8070F2FC((s32 *)&sp90, 0x15C, (s32)((f64)(s32)((f64)i + 51.625 + 8.0) * 4.0));
        i += 8;
    } while (i < 0xA0);
    i = 0x28;
    do {
        func_8070F2FC((s32 *)&sp90, 0x25C, (s32)((f64)(s32)((f64)i + 51.625 + 8.0) * 4.0));
        i += 8;
    } while (i != 0xA0);
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4 = 0x492;
    ArcA1_P6D0 = D_80034568;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, D_80034568, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp90, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    pt = D_8004A7C8;
    do {
        func_800274E0(&sp90, pt->x, pt->y, pt->z);
        pt++;
    } while (pt < D_8004A7C8 + 21);
    bar = D_8004BC88;
    do {
        j = 0;
        if (D_8004C71D == 0 && D_8004C724 == 5) {
            bar->y = bar->y + bar->vy;
            if (bar->y < 99.0f) {
                bar->y = bar->y + 144.0f;
            }
            if (bar->y > 243.0f) {
                bar->y = bar->y - 144.0f;
            }
        }
        do {
            func_8070F2FC((s32 *)&sp90, (s32)((bar->x + 40.0f + (f32)j) * 4.0f), (s32)(((f64)bar->y * 0.875 + 8.0) * 4.0));
            j += 8;
        } while (j != 0x10);
        bar++;
    } while (bar != (ArcA1_Bar *)D_8004BCD0);
    func_800263EC(&sp90);
    *arg0 = sp90;
}
