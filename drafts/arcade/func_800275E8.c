// func_800275E8 (src/arcade/0.c): stage 5: 14 diff lines, all regalloc. frame 160, sp90 at 144 OK (decl order i,j,n,sp90,pt,bar). Matches via: sp90=*arg0 first; ArcA1_P6D0 read back as a1 arg; block1 loops 'for (j=5;j<0x14;j++) (f64)(j*8)'; bar loop 'for (j=0;j<2;j++) (f32)(j*8)'; pt loop 'n=21; pt=D_8004A7C8; for(i=0;i<n;i++) f(pt[i]..)' gives sltu + addiu s,s0,84 like target. Remaining: bound web gets s2 (target s1) because local n takes s1, and addiu order s1,s4,s6,s7 vs s4,s6,s7,s1 for later bar setup. Without n the bound constant-folds to lui+addiu D_8004A7C8+84. In matched form need ArcA4_Bar typedef+extern D_8004BC88 above this func (drop later ArcA4 dup).
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
extern ArcA1_Bar D_8004BC88[];
extern u8 D_80032F40[];
extern ArcA1_Pt D_8004A7C8[];
extern u8 D_8004BC50[];
void func_800275E8(Gfx **arg0) {
    s32 i;
    s32 j;
    s32 n;
    Gfx *sp90;
    ArcA1_Pt *pt;
    ArcA1_Bar *bar;

    sp90 = *arg0;
    D_8004C719 = 2;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    ArcA1_P6D0 = D_80032F40;
    func_80005A90(D_8004BC50 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp90, D_8004BC50 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    for (j = 5; j < 0x14; j++) {
        func_8070F2FC((s32 *)&sp90, 0x15C, (s32)((f64)(s32)((f64)(j * 8) + 51.625 + 8.0) * 4.0));
    }
    for (j = 5; j < 0x14; j++) {
        func_8070F2FC((s32 *)&sp90, 0x25C, (s32)((f64)(s32)((f64)(j * 8) + 51.625 + 8.0) * 4.0));
    }
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4 = 0x492;
    ArcA1_P6D0 = D_80034568;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp90, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    n = 21;
    pt = D_8004A7C8;
    for (i = 0; i < n; i++) {
        func_800274E0(&sp90, pt[i].x, pt[i].y, pt[i].z);
    }
    bar = D_8004BC88;
    do {
        if (D_8004C71D == 0 && D_8004C724 == 5) {
            bar->y = bar->y + bar->vy;
            if (bar->y < 99.0f) {
                bar->y = bar->y + 144.0f;
            }
            if (bar->y > 243.0f) {
                bar->y = bar->y - 144.0f;
            }
        }
        for (j = 0; j < 2; j++) {
            func_8070F2FC((s32 *)&sp90, (s32)((bar->x + 40.0f + (f32)(j * 8)) * 4.0f), (s32)(((f64)bar->y * 0.875 + 8.0) * 4.0));
        }
        bar++;
    } while (bar != (ArcA1_Bar *)D_8004BCD0);
    func_800263EC(&sp90);
    *arg0 = sp90;
}
