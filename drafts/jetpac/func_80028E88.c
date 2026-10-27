// func_80028E88 (src/jetpac/3480.c): stage 6, parked NON_MATCHING: regs now right (s3 color, s8 color_fp via 'color_fp = D_8002EF90; color = color_fp'); remaining prologue order (lui t6 temp for EF90 vs v0, lui s5 first, addiu s7,s6,s5 order), a3 move before sw zero 0x10(sp), temps t8/t9 vs t9/t0.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 color[4];
    u8 pad14[8];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
} JetpacLedge;

typedef struct {
    u8 pad0[0x344];
    s32 unk344;
} JetpacGlobal;

extern JetpacGlobal D_8002EC30;

void func_80025700(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];
extern u8 D_8002F060[];
extern JetpacLedge D_8002EF80[];

void func_80028E88(void) {
    u8 *color_fp = D_8002EF90;
    u8 *color = color_fp;
    void *de80 = &D_8002DE80;
    u8 *base = (u8 *)&D_8002EC30;
    JetpacLedge *ledge = D_8002EF80;

    do {
        s32 x = (s32)*(f32 *)(base + 0x350);
        s32 y = (s32)*(f32 *)(base + 0x354);
        JetpacLedge *cur = ledge;
        s32 j;

        func_80025700(&D_8002DE68, x, y, color_fp, 0);
        j = 0;
        x += 8;
        if (cur->unk30 > 0) {
            do {
                func_80025700(de80, x, y, color, 0);
                j++;
                x += 8;
            } while (j < cur->unk30);
        }
        func_80025700(&D_8002DE98, x, y, color, 0);
        color += 0x34;
        base += 0x34;
        ledge++;
        color_fp += 0x34;
    } while (color != D_8002F060);
}
